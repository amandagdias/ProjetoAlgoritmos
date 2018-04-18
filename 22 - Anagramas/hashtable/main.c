#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "hashtable.h"
typedef struct words{
	int sum;
	char palavra[100];
}WORDS;
WORDS *create_vector(int *n, char* str) {
	int i, j, colisions;
	int sum;
	char palavra[100];
	WORDS *vector = (WORDS *) malloc(sizeof(WORDS) * (*n));
	FILE *file;
	file = fopen(str, "r");
	sum = 0;	
	if (file)
	{
		j = 0;
		while(!feof(file))
		{
			fscanf(file, "%s", palavra);			
			if (palavra[0]!=EOF)
			{
				sum = 0;
				for (i =0; i < strlen(palavra);i++)
				{
					sum += (int) palavra[i];
				}				
				vector[j].sum = sum;
				strcpy(vector[j].palavra, palavra);					
			
				j++;
			}
		
		}
	}
	fclose(file);
	
	*n = j;
	return vector;
}
int main(int argc, char *argv[]) {
	int i, colisions;
	int max = -10;
	WORDS* v, *vector;		
	int index;
	int n = 300000;
	char* str;
	str = (char*) malloc(sizeof(char)*50);
	v = (WORDS*) malloc(sizeof(WORDS)*n);
//	scanf("%s", str);
   
	vector = create_vector(&n, "01.txt");
	printf("n: %d\n", n);
	HASHTABLE *hashtable = hashtable_create(n, &hash_division);
	//HASHTABLE *hashtable = hashtable_create(n, &hash_multiplication);
	index = 0;
	for (i = 0; i < n; i++) {
		colisions = hashtable_put(hashtable, vector[i].sum, NULL);
		if (colisions > max)
		{			
			max = colisions;
			free(v);
			index = 0;
			v = (WORDS*) malloc(sizeof(WORDS)*n);
			v[index].sum = vector[i].sum;
			strcpy(v[index].palavra, vector[i].palavra);	
			index++;	
		}else if (colisions == max)
		{
			v[index].sum = vector[i].sum;
			strcpy(v[index].palavra, vector[i].palavra);	
			index++;	
		}
	}
	printf("max: %d\n", max);
	for (i=0; i < index; i++)
	{
		printf("%s %d\n",v[i].palavra, v[i].sum);
	}
	hashtable_destroy(hashtable);

	return 0;
}
