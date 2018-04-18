/*
Nome: Amanda Gonçalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 24/03/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include "Gauss-Jordan.h"

int main(void)
{
	int kA, i, j;
	double** A;
	double* B;
	double* X; 
	scanf("%d",&kA);
	
	A = malloc(sizeof (double*) * kA);
	for (i = 0; i < kA; i++)
      A[i] = malloc (sizeof (double) * kA);
	B = malloc(sizeof (double) * kA);
	X = malloc(sizeof(double) * kA);
	
	//Lê os valores da matriz A
	for (i = 0; i < kA; i++)
	{
		for (j = 0; j < kA; j++)
		{			
			scanf("%lf", &A[i][j]);
		}		
	}
	//Lê os valores da matriz B
	for (i=0; i < kA; i++)
	{
		scanf("%lf", &B[i]);		
	} 

	//readfromfile(A, B, kA);
	X = GaussJordan(A, B, kA);

	for (i=0; i < kA; i++)
	{
		printf("%.6f\n", X[i]);		
	}
	free(A);
	free(B);
	free(X);
}