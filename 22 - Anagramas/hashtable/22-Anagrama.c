/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 02/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct hashnode {
	int collisions;
  double key;
	char **word;
} HASH_NODE;

typedef struct hashtable {
	int m;
	HASH_NODE *table;
	int (*hfunction)(double key, int m);
} HASHTABLE;

int myCompare(const void *string1, const void *string2) {
    const char *aux1 = *(const char**) string1;
    const char *aux2 = *(const char**) string2;
    return strcmp(aux1, aux2);
}

int myCompare2(const void *string1, const void *string2) {
    const char **aux1 = (const char**)*(const char**) string1;
    const char **aux2 = (const char**)*(const char**) string2;
    return strcmp(aux1[0], aux2[0]);
}

int hash_function(double key, int m) {
  key = fmod(key, m);
  return (int) key;
}

void hashtable_create(HASHTABLE **hashtable, int m, int (*hfunction)(double, int)) {
	*hashtable = malloc(sizeof(HASHTABLE));
	(*hashtable)->m = m;
	(*hashtable)->table = calloc(m, sizeof(HASH_NODE));
	(*hashtable)->hfunction = hfunction;
}

void hashtable_destroy(HASHTABLE *hashtable, int m) {
	if (hashtable != NULL) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < hashtable->table[i].collisions; j++) {
        free(hashtable->table[i].word[j]);
      }
    }
		free(hashtable->table);
		free(hashtable);
	}
}

int *primeNumbers (int n) {
  int *prime, count, flag;

  prime = malloc(n * sizeof(int));

  count = 2;
  flag = 1;

  for (int i = 0; i < n; ) {
    for (int j = (count - 1); j >= 2; j--) {
      if ((count % j) == 0) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      prime[i] = count;
      i++;
    }
    count++;
    flag = 1;
  }

  return prime;
}

long double getKey(char *word, int *prime) {
  long double key = 1;

  for (int i = 0; i < strlen(word); i++) {
    key *= prime[(word[i] - 'a')];
  }

  return key;
}

void hashtable_put(HASHTABLE **hashtable, char *word, int *prime) {
  int pos;
  double key;

  key = getKey(word, prime);

  pos = (*hashtable)->hfunction(key, (*hashtable)->m);

  (*hashtable)->table[pos].key = key;
  (*hashtable)->table[pos].collisions++;

  (*hashtable)->table[pos].word = realloc((*hashtable)->table[pos].word, (*hashtable)->table[pos].collisions * sizeof(char*));
  (*hashtable)->table[pos].word[(*hashtable)->table[pos].collisions - 1] = malloc((strlen(word) + 1) * sizeof(char));
  strcpy((*hashtable)->table[pos].word[(*hashtable)->table[pos].collisions - 1], word);
}

int main(int argc, char *argv[]) {
  FILE *dictionary;
  HASHTABLE *hashtable;
  char file_name[20], word[50], ***words;
  int greater, *prime, *index = NULL, m = 300007, count;

  scanf("%s", file_name);
  getchar();

  hashtable_create(&hashtable, m, &hash_function);

  prime = primeNumbers(26);

  dictionary = fopen(file_name, "r");

  while (fscanf(dictionary, "%s", word) > 0) {
    hashtable_put(&hashtable, word, prime);
  }

  fclose(dictionary);

  greater = 0;
  for (int i = 0; i < m; i++) {
    if (hashtable->table[i].collisions > greater) {
      greater = hashtable->table[i].collisions;
    }
  }

  count = 0;
  for (int i = 0; i < m; i++) {
    if (hashtable->table[i].collisions == greater) {
      index = realloc(index, (count + 1) * sizeof(int));
      index[count] = i;
      count++;
    }
  }

  words = malloc(count * sizeof(char*));

  printf("%d\n", count);

  for (int i = 0; i < count; i++) {
    words[i] = malloc(greater * sizeof(char*));
    for (int j = 0; j < greater; j++) {
      words[i][j] = malloc(50 * sizeof(char));
      strcpy(words[i][j], hashtable->table[index[i]].word[j]);
    }
  }

  for (int i = 0; i < count; i++) {
    qsort(words[i], greater, sizeof(char*), &myCompare);
  }

  for (int i = 0; i < greater; i++) {
    qsort(words, count, sizeof(char*), &myCompare2);
  }

  for (int i = 0; i < count; i++) {
    for (int j = 0; j < (greater - 1); j++) {
      printf("%s, ", words[i][j]);
    }
    printf("%s", words[i][greater - 1]);
    printf("\n");
  }

  hashtable_destroy(hashtable, m);

  return 0;
}
