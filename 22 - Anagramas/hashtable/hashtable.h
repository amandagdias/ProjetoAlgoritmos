#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

enum {
	FALSE,
	TRUE
};

struct hashnode {
	int key;
	// 0: empty; 1: busy
	unsigned char flag:1; 
	void *data;
};

typedef struct hashnode HASH_NODE;

struct hashtable {
	int m;
	HASH_NODE *table;
	int (*hfunction)(int key, int m);
};

typedef struct hashtable HASHTABLE;

HASHTABLE *hashtable_create(int, int (*)(int, int));
void hashtable_destroy(HASHTABLE *);
int hashtable_put(HASHTABLE *, int, void *);

// hashing functions
int hash_division(int, int);
int hash_multiplication(int, int);

#endif
