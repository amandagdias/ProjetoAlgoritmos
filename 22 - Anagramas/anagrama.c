/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 03/07/2017
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
typedef struct words{
	int sum;
	char palavra[100];
}WORDS;

typedef struct grupos{
	int pos;
	int sum;
	struct grupos *next;
}GRUPOS;
typedef struct node{
	char palavra[100];
	int sum;
	struct node * next;	
}NODE;
typedef struct sol{
	int usado;
	NODE* head;
}SOLUTION;
struct hashnode {
	int key;
	NODE* head;
	int numelements;
	
};
typedef struct hashnode HASH_NODE;

struct hashtable {
	int m;
	HASH_NODE *table;
	int (*hfunction)(double key, int m);
};

typedef struct hashtable HASHTABLE;

int hash_division(double key, int m) {
	key = fmod(key, m);
	return (int)key;
}
HASHTABLE *hashtable_create(int m, int (*hfunction)(double, int)) {
	int i;
	HASHTABLE *hashtable;
	hashtable = (HASHTABLE *) malloc(sizeof(HASHTABLE));
	hashtable->m = m;
	hashtable->table = (HASH_NODE *) calloc(m, sizeof(HASH_NODE));
	for (i=0; i < m; i++)
		hashtable->table[i].head = NULL;
	hashtable->hfunction = hfunction;	
	return hashtable;
}
int AddToList(NODE** head, char palavra[100], int sum)
{
	NODE* p, *q;
	p = (NODE*) malloc(sizeof(NODE));
	q = (NODE*) malloc(sizeof(NODE));
	strcpy(p->palavra, palavra);
	p->sum = sum;
	p->next = NULL;
	if (*head == NULL)
	{
		*head = p;
		return 1;
	}	
	if ((*head)->sum == sum)
	{
		q = *head;
		while (q->next)
		{
			q = q->next;
		}
		q->next = p;
		return 1;
	}
	return 0;

}
void AddToListG(GRUPOS** head, int sum, int pos)
{
	GRUPOS* p, *q;
	p = (GRUPOS*) malloc(sizeof(GRUPOS));
	q = (GRUPOS*) malloc(sizeof(GRUPOS));
	p->sum = sum;
	p->pos = pos;
	p->next = NULL;
	if (*head == NULL)
	{
		*head = p;
		return;
	}
	q = *head;
	while (q->next)
	{
		q = q->next;
	}
	q->next = p;
}
int* generatePrimes()
{
	int n = 26; //a-z
	int* primes;
	int div;
	int i, j, index;
	primes = (int*) malloc(sizeof(int)*n);
	index = 0;
	for(i = 0; index < n; i++) {
        div = 0;       
        for(j = 1; j <= i; j++) {
            if(i % j == 0) {
                div++;
            }
        }       
        if(div == 2) {
        	primes[index] = i;
        	index++;   
        }
    }
	return primes;
	
}
long double produceKey(char palavra[100], int* prime)
{
	int n = strlen(palavra);
	int i;
	int c;
	double key = 1;
	for (i=0; i < n; i++)
	{	
		c = (int)(palavra[i]-'a');		
		key = (key * (prime[c]));		
	}
	
	return key;
}
NODE* getWordHash(HASHTABLE *hashtable, int pos)
{
	return hashtable->table[pos].head;		
}
int getElemHash(HASHTABLE *hashtable, int pos)
{
	return hashtable->table[pos].numelements;
}
void hashtable_put(HASHTABLE **hashtable, WORDS* word, GRUPOS** grupos, int* prime, int* max) {
	int pos;
	double key;		
	key = produceKey(word->palavra, prime);
	pos = (*hashtable)->hfunction(key, (*hashtable)->m);	
	if (AddToList(&((*hashtable)->table[pos].head), word->palavra, word->sum))
	{
		if ((*hashtable)->table[pos].numelements == 0)
		{		
			//new word in that position
		//	AddToListG(grupos, word->sum, pos);	
			(*hashtable)->table[pos].numelements++;
			(*hashtable)->table[pos].key = word->sum;			
		}else{
			if ((*hashtable)->table[pos].key == word->sum)
			{
				(*hashtable)->table[pos].numelements++;
				(*hashtable)->table[pos].key = word->sum;
			}
		}
		if ((*hashtable)->table[pos].numelements > *max)
			*max = (*hashtable)->table[pos].numelements;
	
	}
}

void create_vector(int n, char* str, HASHTABLE* hashtable, GRUPOS ** grupos, int *max) {
	int i, j;
	int sum;
	char palavra[100];
	int *prime;
	WORDS* word = (WORDS*)malloc(sizeof(WORDS));
	FILE *file;
	file = fopen(str, "r");
	sum = 0;	
	prime = generatePrimes(); 
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
						
				word->sum = sum;
				strcpy(word->palavra, palavra);	
				hashtable_put(&hashtable, word, grupos, prime, max);				
				j++;
			}
		
		}
	}
	else{
		printf("file not found\n");
	}
	fclose(file);

}
int getNextPrime(int n)
{
	int div, j;
	while(1)
	{
		div = 0;		
		for (j=1; j <= n;j++)
		{
			if (n%j == 0)
				div++;
			if (div > 2)
				continue;
		}
		if (div == 2)
			return n;
		n++;
	}
}
void AddToSolution(SOLUTION** solution, int index, NODE* headhash)
{
	printf("index: %d\n", index);
	(*solution) = realloc((*solution), index+1);
	(*solution)[index].usado = 0;
	NODE *p, *q;
	p = (NODE*) malloc(sizeof(NODE));
	q = (NODE*) malloc(sizeof(NODE));
	p->next = headhash->next;
	p->sum = headhash->sum;
	strcpy(p->palavra, headhash->palavra);
	if ((*solution)[index].head == NULL)
	{
		(*solution)[index].head	= p;
		return;
	}	
	q = (*solution)[index].head; 
	if (strcmp(q->palavra, p->palavra) > 0)
	{
		headhash->next = (*solution)[index].head;
		(*solution)[index].head = headhash;
		return;
	}
	while(q->next)
	{
		if (strcmp(q->palavra, p->palavra) > 0)
		{
			p->next = q->next;
			q->next = p;
			return;			
		}
		q = q->next;	
	}
	q->next = p;
 	q->next->next = NULL;
	
}
void OrdenaSolution(SOLUTION* solution, int n){
	int i, j;
	NODE* p, *q;
	SOLUTION* auxNode;
	NODE *auxHead;
	p = (NODE*) malloc(sizeof(NODE));
	q = (NODE*) malloc(sizeof(NODE));
	auxNode= (SOLUTION*) malloc(sizeof(SOLUTION));
	auxNode->head = (NODE*) malloc(sizeof(NODE));
	for (i=0;i < n; i++)
	{
		for (j=0; j < i; j++)
		{			
			p = solution[i].head;
			q = solution[j].head;	
			if (strcmp(q->palavra, p->palavra)>0)
			{	
				auxHead = (NODE*) malloc(sizeof(NODE));
			    auxNode->head = p;
				p = p->next;
				auxHead = auxNode->head;
				auxHead = auxHead->next;																
				while(p)				
				{							
					auxHead = (NODE*) malloc(sizeof(NODE));
					strcpy(auxHead->palavra, p->palavra);
					auxHead->sum = p->sum;
					auxHead->next = p->next;					
					p = p->next;
					auxHead = auxHead->next; 
				}				
				solution[i] = solution[j];				
				solution[j] = *auxNode;					
			}
		}
	}
}
int main() {
	int i;
	int max = -10;	
	int n = 300000;
	int count;
	char* str;
	GRUPOS *grupos = NULL;

	SOLUTION* solution;
	NODE* aux;
	NODE* headhash;
	aux = (NODE*) malloc(sizeof(NODE));
	solution = (SOLUTION*) malloc(sizeof(SOLUTION));

	str = (char*) malloc(sizeof(char)*50);
	scanf("%s", str);
   	n = getNextPrime(n);
	HASHTABLE *hashtable = hashtable_create(n, &hash_division);
	create_vector(n, str, hashtable, &grupos, &max);	
   
	count = 0;

	for (i=0; i < n; i++)
	{		
		if (hashtable->table[i].numelements == max)
		{			
			headhash = hashtable->table[i].head;
			solution[count].head = NULL;
		
			while(headhash)
			{						
				strcpy(aux->palavra, headhash->palavra);
				aux->sum = headhash->sum;
				aux->next = NULL;			
				AddToSolution(&solution, count, aux);		    	
				headhash = headhash->next;
			}	
			count++;
		}
	}
	printf("%d\n", count);
	aux = (NODE*) malloc(sizeof(NODE));
	OrdenaSolution(solution, count);	

	for (i=0; i < count; i++)
	{
		aux = solution[i].head;
		while (aux->next)
		{
			printf("%s, ", aux->palavra);
			aux = aux->next;
		}
		printf("%s\n", aux->palavra);
		
	}
}

