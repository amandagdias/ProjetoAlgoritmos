/*
Nome: Amanda Gonçalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 25/03/2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void trocar_linhas(double **A, int linhaVelha, int linhaNova, int kA, int kB)
{
	int j;
	int aux;
	for (j=0; j< (kA + kB); j++)
	{
		aux = A[linhaVelha][j];
		A[linhaVelha][j] = A[linhaNova][j];
		A[linhaNova][j] = aux;
		
	}	
}

double* GaussJordan(double** M, double* B, int kA)
{		
	int i,j,k, c, i2, kB = 1;		
	double pivo;
	int isId = 1;
	double elementoAZerar;
	double* x = malloc(sizeof (double) * kA);
	double** A = malloc (sizeof (double*) * (kA + kB));//
	
	for (i = 0; i < (kA + kB); i++)
	{
		A[i] = malloc (sizeof(double) * (kA + kB));		
	}
	//Copiar a matriz M para A
	for (i = 0; i < kA; i++)
	{
		for (j=0; j < kA; j++)
		{
			A[i][j] = M[i][j];
		
		}	
	
	}

	i2 = 0;
	//Copiar a matriz B para A
	for (i = 0; i < kA ; i++)
	{		
		for (j = kA; j< (kA+kB); j++)
		{
			A[i][j] = B[i2];
			i2++;
		}		
	}
	for (i = 0; i < kA; i++)
	{
		pivo = A[i][i];
		
		if (pivo == 0.0)
		{
			for (j=i; j < kA; j++)
			{
				if (j!=i)
				{
					if (A[j][i] != 0.0) //trocar linhas
					{
						trocar_linhas(A, i, j, kA, kB);
						j = kA;
						pivo = A[i][i];
					}
				}
			}
			
		}
		if (pivo != 1.0)  //fazer pivô igual a 1
		{
			for (j=0; j < (kA + kB); j++)
			{
				A[i][j] = (A[i][j] / pivo);  
			}		
			pivo = A[i][i];
		}
		if (pivo == 1.0) //zerar elementos da coluna
		{
			for (c=0; c < kA; c++)
			{
				if (c != i) // i = linha do pivo
				{
					elementoAZerar = A[c][i];					
					if (elementoAZerar != 0.0)
					{
						for (j=0; j < (kA + kB); j++)
						{					   
							A[c][j] = A[c][j] - elementoAZerar * A[i][j];
							
						}
						
					}
				
				}
			}
		}
	}
	//Verificar se a matriz correspondente a parte da matriz A é identidade
	for (i=0; i < kA; i++)
	{		
			for (j=0; j < kA; j++)
			{
			
				if ((A[i][j] != 0)&&(i!=j)){
					isId = 0;
					j= kA;
				}
			}	
		if (isId)
		{		
			A[i][kA] = A[i][kA] / A[i][i];
			
		}			
				
	}

	//Se for identidade, copia os valores da matriz (correspondente a parte B) para X e retorna.
	if (isId)
	{		
		k=0;
		for (i=0; i < kA; i++)
		{
			for (j= kA; j < (kA+kB); j++)
			{
				if (k<kA)
				{
					x[k] = A[i][j];				
					k++;
				}							
			}
		}	
	}
	free(A);
	return x;
}
int main(void){

	int k, i ,j,v ; 
	double** M;
	double* P;
	double* Y;
	double* X;
	scanf ("%d",&k);
	P = malloc (sizeof(double) * k);
	Y = malloc (sizeof(double) * k);
	X = malloc (sizeof(double) * k);
	M = malloc (sizeof(double*) * k);
	
	for (i = 0; i < k ; i++)
	{		
		scanf("%lf", &P[i]);		
		scanf("%lf", &Y[i]);
		M[i] = malloc (sizeof(double) * k);
	}
	for (i = 0; i < k; i++)
	{
	
		for (j = 0; j < k; j++)
		{
			v = (int)(k - (j+1));
			M[i][j] = (double) pow(P[i], v);		
		}	
	}	
	X = GaussJordan(M, Y, k);
	
	for (i = 0 ; i < k ; i++)
		printf ("%.6f\n", X[i]);
	free(X);
	X = NULL;
	free(Y);
	Y = NULL;
	free(P);
	P = NULL;
	free(M);
	M = NULL;
}