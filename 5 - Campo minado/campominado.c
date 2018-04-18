/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 12/04/2017
*/

#include<stdio.h>
#include<stdlib.h>
//Para Imprimir as dicas:
	//Percorra a matriz procurando bombas, adicionando 0s na matriz de contagem. Quando encontrar uma bomba adicione -1 (indica bomba) na matriz:
		//Adicione 1 a matriz de contagem para as casas vizinhas
			//-> verificar se é uma borda e se for uma bomba, pule. 
			
		//Para imprimir: 
			//Percorrer a matriz e imprimir "." quando 0, "*" quando -1 quando !=, imprimir o próprio valor
//Para opcao 3: Funcao de recorrencia chamando os quadrados em volta (esquerda, direita, cima, baixo e diagonais)
	//Matriz auxiliar iniciada tudo com -1
	//Se encontrar um numero, retorna e salva na matriz auxiliar o numero
	//Se encontrar borda, volta
	//Se encontrar outro em branco, salva 0 na matriz auxiliar
	//Imprime utilizando a matriz do campo e a auxiliar
			
			
#define esquerda j - 1
#define direita j + 1
#define cima i - 1
#define baixo i + 1

void ImprimirCampo(char* str)
{
	char c;
	FILE *file;
	file = fopen(str, "rt");
	if (file != NULL) {
	   	while (!feof(file))
		{	
			c = fgetc(file);
			if (!feof(file))
				printf ("%c", c);				
		}
		fclose(file);
	}	
}
void ImprimirDicas(int** campo, int size_x, int size_y)
{
	int i, j;
	for (i = 0; i < size_y; i++)
	{
		for (j=0; j < size_x; j++)
		{
			if (campo[i][j] == -1)
			{
				printf("*")	;
			}
			else if (campo[i][j] == 0)
			{
				printf(".");				
			}
			else 
				printf("%d", campo[i][j]);
		}
		printf ("\n");
	}
}
void SalvarDicas(int** campo, int size_x, int size_y)
{
	int i, j;
	for (i = 0; i < size_y; i++)
	{
		for (j=0; j < size_x; j++)
		{
			if (campo[i][j] == -1)
			{
				if ((cima >= 0)&&(campo[cima][j] != -1))
					campo[cima][j]++;
				if ((baixo < size_y)&&(campo[baixo][j] != -1))
					campo[baixo][j]++;
				if ((esquerda >= 0)&&(campo[i][esquerda] != -1))
					campo[i][esquerda]++;
				if ((direita < size_x)&&(campo[i][direita] != -1))
					campo[i][direita]++;
				if ((cima >=0)&&(esquerda >= 0)&&(campo[cima][esquerda] != -1))
					campo[cima][esquerda]++;
				if ((cima >= 0)&&(direita < size_x)&&(campo[cima][direita] != -1))
					campo[cima][direita]++;
				if ((baixo < size_y)&&(esquerda >=0)&&(campo[baixo][esquerda] != -1))
					campo[baixo][esquerda]++;
				if ((baixo < size_y)&&(direita < size_x)&&(campo[baixo][direita] != -1))
					campo[baixo][direita]++;				
			}
		}
	}
}
void RevelaEmBranco(int** campo,int** aux,int size_x,int size_y,int i,int j)
{
	if ((i < 0)||(i >= size_y)) //borda
		return;
	if ((j < 0)||(j >= size_x)) //borda
		return;
	if (campo[i][j] != 0) //valor encontrado
	{
		aux[i][j] = campo[i][j];
		return;		
	}
	if (aux[i][j] != -1) //campo ja visitado
		return;
	else
	{
		aux[i][j] = 0;
		RevelaEmBranco(campo, aux, size_x, size_y, cima, j);
		RevelaEmBranco(campo, aux, size_x, size_y, baixo, j);
		RevelaEmBranco(campo, aux, size_x, size_y, i, esquerda);
		RevelaEmBranco(campo, aux, size_x, size_y, i, direita);
		RevelaEmBranco(campo, aux, size_x, size_y, cima, esquerda);
		RevelaEmBranco(campo, aux, size_x, size_y, cima, direita);
		RevelaEmBranco(campo, aux, size_x, size_y, baixo, esquerda);
		RevelaEmBranco(campo, aux, size_x, size_y, baixo, direita);	
	}
}
void Mostrar(int** campo, int size_x, int size_y, int x, int y)
{
	int i, j ;
	int** aux;
	
	aux = (int**) malloc(sizeof(int*) * size_y);
	for (i = 0; i < size_y; i++){		
		aux[i] = (int*) malloc(sizeof(int) * size_x);
		for (j = 0; j < size_x; j++)
			aux[i][j] = -1;
	}
	if ((x < size_y)&&(y < size_x))
	{
		if (campo[x][y] == -1)
			ImprimirDicas(campo, size_x, size_y);
		else
		{			
			if (campo[x][y] != 0)
			{
				for (i = 0 ; i < size_y; i++)
				{
					for (j = 0; j < size_x; j++)
					{
						if ((i==x)&&(j==y))
							printf("%d", campo[i][j]);
						else
							printf("X");
					}
					printf("\n");
				}
			}
			else if (campo[x][y] == 0)
			{
				
				RevelaEmBranco(campo, aux, size_x, size_y, x, y);
				for (i = 0 ; i < size_y; i++)
				{
					for (j = 0; j < size_x; j++)
					{
						if (aux[i][j] == 0)
							printf(".");
						else if (aux[i][j] == -1)
							printf("X");
						else
							printf ("%d", campo[i][j]);
					}
					printf("\n");
				}
			}
		}
		
	}
	
}
int** readfromfile(char* str, int* size_x, int* size_y)
{	
	char c;
	FILE *file;
	int i, j;
	int** campo;
	file = fopen(str, "rt");
	if (file != NULL) {
		*size_x = 0;
		*size_y = 0;
    	while ((c = fgetc(file)) != '\n')
		{				
			(*size_x)++;				
		}
		(*size_y)++;	
		while (!feof(file))
		{	
			c = fgetc(file);			
			if (c == '\n')
				(*size_y)++;			
		}
		fclose(file);
	}	

	campo = (int**) malloc (sizeof(int*) * (*size_y));
	for (i = 0 ; i< *size_y; i++)
	{
		campo[i] = (int*) malloc(*size_x * sizeof(int) );
	}
	file = fopen(str, "rt");	
	if (file != NULL) {
		i = 0;
		j = 0;
    	while (!feof(file))
		{	
			c = fgetc(file);
			if (j < *size_x){	
				if (c == '.')
					campo[i][j] = 0;
				else if (c == '*')
					campo[i][j] = -1;
				if ((c == '.')||(c == '*'))
					j++;					
			}								
			if ((j >= *size_x)&&(i < *size_y))
			{
				i++;		
				j = 0;
			}					
		}
		fclose(file);
	}
	
	return campo;	
}
int main(){
	int** campo;
	int size_x, size_y, x, y;
	int option;

	char* str = (char*) malloc (sizeof(char)*20);
	
	scanf("%d", &option);
	scanf("%s", str);
	
	if (option == 3)
	{
		scanf("%d %d", &x, &y);
		campo = readfromfile(str, &size_x, &size_y);
		SalvarDicas(campo, size_x, size_y);
		Mostrar(campo, size_x, size_y, x, y);
	}
	else if (option == 1)
	{
		ImprimirCampo(str);		
	}
	else if (option == 2)
	{
		campo = readfromfile(str, &size_x, &size_y);
		SalvarDicas(campo, size_x, size_y);
		ImprimirDicas(campo, size_x, size_y);
	}
	
}

 		
