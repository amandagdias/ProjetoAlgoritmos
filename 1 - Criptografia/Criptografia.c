/*
Nome: Amanda Gonçalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 27/03/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
//PSEUDOCODIGO

// Pegar o texto do arquivo 
// Descobrir o valor de k com base no tamanho do texto (k = raiz do num de caracteres)
// Pedir a matriz M com base em k 
// Gerar matriz Y com base na tabela de conversão e em k 
// Inverter M - Aplicar Gauss
// Multiplicar Y por M inversa
// Converter a matriz gerada utilizando a tabela 

void criar_tabela(char **t)
{

	
	(*t)[0] = 32;
	(*t)[1] = 'a';
	(*t)[2] = 'b';
	(*t)[3] = 'c';
	(*t)[4] = 'd';
	(*t)[5] = 'e';
	(*t)[6] = 'f';
	(*t)[7] = 'g';
	(*t)[8] = 'h';
	(*t)[9] = 'i';
	(*t)[10] = 'j';
	(*t)[11] = 'k';
	(*t)[12] = 'l';
	(*t)[13] = 'm';
	(*t)[14] = 'n';
	(*t)[15] = 'o';
	(*t)[16] = 'p';
	(*t)[17] = 'q';
	(*t)[18] = 'r';
	(*t)[19] = 's';
	(*t)[20] = 't';
	(*t)[21] = 'u';
	(*t)[22] = 'v';
	(*t)[23] = 'w';
	(*t)[24] = 'x';
	(*t)[25] = 'y';
	(*t)[26] = 'z';
	(*t)[27] = 'A';
	(*t)[28] = 'B';
	(*t)[29] = 'C';
	(*t)[30] = 'D';
	(*t)[31] = 'E';
	(*t)[32] = 'F';
	(*t)[33] = 'G';
	(*t)[34] = 'H';
	(*t)[35] = 'I';
	(*t)[36] = 'J';
	(*t)[37] = 'K';
	(*t)[38] = 'L';
	(*t)[39] = 'M';
	(*t)[40] = 'N';
	(*t)[41] = 'O';
	(*t)[42] = 'P';
	(*t)[43] = 'Q';
	(*t)[44] = 'R';
	(*t)[45] = 'S';
	(*t)[46] = 'T';
	(*t)[47] = 'U';
	(*t)[48] = 'V';
	(*t)[49] = 'W';
	(*t)[50] = 'X';
	(*t)[51] = 'Y';
	(*t)[52] = 'Z';
	(*t)[53] = '0';
	(*t)[54] = '1';
	(*t)[55] = '2';
	(*t)[56] = '3';
	(*t)[57] = '4';
	(*t)[58] = '5';
	(*t)[59] = '6';
	(*t)[60] = '7';
	(*t)[61] = '8';
	(*t)[62] = '9';
	(*t)[63] = ':';
	(*t)[64] = ';';
	(*t)[65] = '<';
	(*t)[66] = '=';
	(*t)[67] = '>';
	(*t)[68] = '?';
	(*t)[69] = '@';
	(*t)[70] = '!';
	(*t)[71] = 34;
	(*t)[72] = '#';
	(*t)[73] = '$';
	(*t)[74] = '%';
	(*t)[75] = '&';
	(*t)[76] = 39;
	(*t)[77] = '(';
	(*t)[78] = ')';
	(*t)[79] = '*';
	(*t)[80] = '+';
	(*t)[81] = ',';
	(*t)[82] = '-';
	(*t)[83] = '.';
	(*t)[84] = '/';
	(*t)[85] = '[';
	(*t)[86] =  92;
	(*t)[87] = ']';
	(*t)[88] = '_';
	(*t)[89] = '{';
	(*t)[90] = '|';
	(*t)[91] = '}';

}
int procurar_valor(char * t, char c)
{
	int i ;
	for (i = 0; i < 92 ; i++)
	{

		if (t[i] == c)
		{	
		
			return i;
		}	
			
	}

	return -1;
}
void procurar_chave(char* t, int v)
{
	printf ("%c",(char) t[v] );

}
void trocar_linhas(int **A, int linhaVelha, int linhaNova, int kA, int kB)
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


int** GaussJordan(int** M, int kA)
{		
	int i,j,k, c, kB = kA;		
	int pivo;
	int isId;
	int elementoAZerar;
	int** x = (int**) malloc(sizeof (int*) * kA);
	int** A = (int**) malloc (sizeof (int*) * (kA + kB));
	isId = 1;
	for (i = 0 ; i < kA; i++)
	{
		x[i] = malloc(sizeof(int) * kA);
	}
	for (i = 0; i < (kA+kB); i++)
	{
		A[i] = malloc (sizeof(int) * (kA+kB));		
	}
	//Copiar a matriz M para A
	for (i = 0; i < kA; i++)
	{
		for (j=0; j < kA; j++)
		{
			A[i][j] = M[i][j];

		}	
		
	}
	
	//Copiar a matriz identidade para A
	for (i = 0; i < kA ; i++)
	{		
		for (j = kA; j< (kA+kB); j++)
		{
		 	if (j == (i+kA))
		 		A[i][j] = 1;
		 	else
			 	A[i][j] = 0;		 		
		}		
	}
	for (i = 0; i < kA; i++)
	{
		pivo = A[i][i];
		
		if (pivo == 0)
		{
			for (j=i; j < kA; j++)
			{
				if (j!=i)
				{
					if (A[j][i] != 0) //trocar linhas
					{
						trocar_linhas(A, i, j, kA, kB);
						j = kA;
						pivo = A[i][i];
					}
				}
			}
			
		}
		if (pivo != 1)  //fazer pivô igual a 1
		{
			for (j=0; j < (kA + kB); j++)
			{
				A[i][j] = (A[i][j] / pivo);  
			}		
			pivo = A[i][i];
		}
		if (pivo == 1) //zerar elementos da coluna
		{
			for (c=0; c < kA; c++)
			{
				if (c != i) // i = linha do pivo
				{
					elementoAZerar = A[c][i];				
					if (elementoAZerar != 0)
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
		
		for (i=0; i < kA; i++)
		{
			k = 0;
			for (j= kA; j < (kA+kB); j++)
			{
				if (k<kA)
				{
					x[i][k] = A[i][j];	
					
					k++;
				}							
			}
			
			
		}	
	}
	free(A);
	return x;
}
int** readfromfile(char *t, char* str, int* k)
{	
	char c;
	FILE *file;
	int i, j;
	int** Y;
	int v;
	file = fopen(str, "rt");
	if (file != NULL) {
		*k = 0;
    	while ((c = fgetc(file)) != EOF)
		{				
			(*k)++;			
		}
		fclose(file);
	}	
	Y = malloc (*k * sizeof(int*) );
	for (i = 0 ; i<*k; i++)
	{
		Y[i] = malloc(*k * sizeof(int) );
	}
	*k = sqrt(*k);

	file = fopen(str, "rt");	
	if (file != NULL) {
		i = 0;
		j = 0;
    	while ((c = fgetc(file)) != EOF)
		{	
		
			if (j < *k){	
				v = procurar_valor(t,c);
				if (v != -1){
					Y[j][i]	= v;	
					j++;	
				}
				 
					
			}								
			if ((j >= *k)&&(i < *k))
			{
				i++;
		
				j = 0;
			}				
			
		}
		fclose(file);
	}
	return Y;	
}
int main (void)
{
	int** Y;
	int k,i,j, temp;
	char *str;
	int **M, **M_In;
	int **X;
	int cy;
	str = malloc(sizeof(char) * 50);
	scanf("%s", str);
	//scanf("%[^\n]s",str);
	char *t;
	t = malloc (sizeof (char) * 92);
	criar_tabela(&t);

	Y = readfromfile(t, str,&k);
	M = (int**)malloc (sizeof(int*)*k);
	M_In = (int**)malloc (sizeof(int*)*k);
	X = (int**)malloc (sizeof(int*)*k);
	for (i = 0; i < k; i++)
	{
		M[i] = malloc(sizeof(int)*k);
		M_In[i] = malloc(sizeof(int)*k);
		X[i] = malloc(sizeof(int)*k);
		for (j = 0; j< k; j++)
		{
			scanf("%d",&M[i][j]);
		
		}
	}
	M_In = GaussJordan(M, k);
	
	//Multiplicar Matriz

	for (i = 0; i < k; i++)
	{
		cy = 0;
		while(cy < k)
		{
			temp = 0 ;
			for(j = 0; j < k; j++)
			{			 	
				temp += M_In[i][j] * Y[j][cy];	
			}
			
			X[cy][i] = temp;	
			cy++;		
		}
			
	}
	for (i=0; i< k; i++)
	{
		for (j=0; j<k; j++)
		{
			procurar_chave(t, X[i][j]);
	
		}		
	}
	free(t);
	t = NULL;
	free(Y);
	Y = NULL;
	free(M);
	M = NULL;
	free(M_In);
	M_In = NULL;
	free(X);
	X = NULL;
	free(str);
	str = NULL;
		
}
