#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "hashtable.h"

/////////////hash functions////////////
int hash_division(int key, int m) {
	return key % m;
}

int hash_multiplication(int key, int m) {
	double A = (1.0 + sqrt(5.0)) / 2.0;
	double fraction = (A * key) - floor(A * key);
	return floor(fraction * m);
}
///////////////////////////////////////

HASHTABLE *hashtable_create(int m, int (*hfunction)(int, int)) {
	HASHTABLE *hashtable;
	hashtable = (HASHTABLE *) malloc(sizeof(HASHTABLE));
	hashtable->m = m;
	hashtable->table = (HASH_NODE *) calloc(m, sizeof(HASH_NODE));
	hashtable->hfunction = hfunction;
	return hashtable;
}

void hashtable_destroy(HASHTABLE *hashtable) {
	if (hashtable != NULL) {
		free(hashtable->table);
		free(hashtable);
	}
}

int hashtable_put(HASHTABLE *hashtable, int key, void *data) {
	int pos, counter = 0;

	do {
		//pos = (key+counter) % hashtable->m;
		pos = hashtable->hfunction(key + counter, hashtable->m);		
		counter++;
	} while (hashtable->table[pos].flag && counter < hashtable->m);
	
	if (!hashtable->table[pos].flag) {
		hashtable->table[pos].key = key;
		hashtable->table[pos].data = data;
		hashtable->table[pos].flag = TRUE;
	}
	
	return (counter - 1);
}



