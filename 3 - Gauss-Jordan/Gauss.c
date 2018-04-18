/*
Nome: Amanda Gonçalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 25/03/2017
*/

#include<stdio.h>
#include<stdlib.h>


//PSEUDOCODIGO
//Montar a matriz aumentada com base na matriz A e vetor B recebidos


//Fazer até transformar a matriz A em identidade
//Pegar o elemento da coluna x linha x
	//Se for 0, procurar um elemento não nulo da coluna para trocar 
	//Se for diferente de 1
			//Multiplicar a linha por 1/elemento 
	//Se for igual a 1		
		//Zerar elementos das outras linhas. 
			//Para as outras linhas: elemento - elementoAZerar * linha do pivô
	//Verificar se a matriz A se tornou a matriz identidade	
	
	
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
					for (j=0; j < (kA + kB); j++)
					{
					   
						A[c][j] = A[c][j] - elementoAZerar * A[i][j];
						
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
void readfromfile(double** A, double* B, int kA)
{	
	char c;
	char* str = malloc (sizeof(char) * 20);
	FILE *file;
	int k, i, j, mA ;
	file = fopen("case2.txt", "r");
	i = 0;
	j=0;
	mA = 1;
	if (file) {
		k = 0;
    	while ((c = fgetc(file)) != EOF)
		{			
			if (c != '\n')
			{				
				str[k] = c;
				k++;
			}else
			{
				str[k]	 = '\0';
		
				if (mA == 1)
				{
					A[i][j] = atof(str);							
					if ((j+1) < kA)
					{									
						j++;
					}
				    else
				    {				    
				    	if ((i+1)<kA){										
				    		j = 0;
				    		i++;				    	
						}		
						else{						
							mA=0;
							i = 0;
						}
																		    		
					}					
				}
				else if (mA == 0){											
					if (i < kA)
					{
						B[i] = atof(str);
						i++;
							
					}
				}
			    
			    k =0;
			    free(str);
			    str = malloc(sizeof(char) * 20);
			}
		   
		}    	
    	fclose(file);
	}
}
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
	
//	readfromfile(A, B, kA);
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

	X = GaussJordan(A, B, kA);

	for (i=0; i < kA; i++)
	{
		printf("%.6f\n", X[i]);		
	}
	free(A);
	free(B);
	free(X);	
}
