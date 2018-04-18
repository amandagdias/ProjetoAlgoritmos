/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 13/04/2017
*/


#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define PI 3.14159265358979323846

void TransformadaCos(int* original,double **cosseno, int N)
{
	int i, j;

	for (j = 0; j < N; j++)
	{
	
		for (i=0; i<N;i++)
		{
			(*cosseno)[j] += (double) (original[i] * cos((PI/N)*(i*1.0 + 1.0/2.0)*j));
		}
	}		
}

int* readfromfile(char* str, int* k)
{	
	unsigned char c;
	FILE *file;
	int i;
	int* original;
	file = fopen(str, "rt");
	if (file != NULL) {
		*k = 0;
	
    	while (!feof(file))
		{	
			c = fgetc(file);				
				(*k)++;			
		}
		fclose(file);
	}

	(*k)--;

	original = malloc (*k * sizeof(int) );
	
	file = fopen(str, "rt");	
	if (file != NULL) {
		i = 0;	
    	while (!feof(file))
		{	
			c = fgetc(file);
			if (i < (*k))	{
				original[i] = (int)c;				
				i++;
			}
					
		}
		fclose(file);
	}
	return original;	
}
void swap(double **vector, int i, int j)
{
	double aux;
	aux = (*vector)[i];
	(*vector)[i] = (*vector)[j];
	(*vector)[j] = aux;
}
int partition(double *vector, int left, int right) {
	int i, j;

	i = left;
	for (j = i+1; j <= right; j++) {
		if (vector[j] < vector[left]) {
			++i;
			swap(&vector, i, j);
		}
	}
	swap(&vector, i, left);

	return i;
}

void quicksort(double **vector, int left, int right) {
	int r;

	if (left < right) {
		r = partition((*vector), left, right);
		quicksort(vector, left, r-1);
		quicksort(vector, r+1, right);
	}
}
int main()
{
	int* original;
	double* cosseno;
	char* str;
	int i, amp_size, k;

	str = malloc(sizeof(char) * 20);
	
	scanf("%s",str);

	
	scanf("%d", &k);
	
	original = readfromfile(str, &amp_size);

	cosseno = (double*) malloc(sizeof(double) * amp_size);
	
	for (i = 0; i < amp_size; i++)
		cosseno[i] = 0.0;
		
	TransformadaCos(original, &cosseno, amp_size);
	
	quicksort(&cosseno, 0, (amp_size-1));
	
	for (i = (amp_size - 1); i >= (amp_size - k); i--)
	{
		printf("%.2f\n", cosseno[i]);
	}
	
	free(original);
	original = NULL;
	free(cosseno);
	cosseno = NULL;


}
