/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 27/04/2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
// Ler a matriz coluna por coluna. Na primeira coluna contar qtas linhas tem. 
// Ao encontrar um número diferente de 0
// Se for a primeira vez, percorre a matriz até encontrar uma coluna de 0s e salva o tamanho da matriz. 
// Salvar o valor em uma matriz auxiliar na posição corresponte
//Para saber a posicao correspondente irá precisar  de duas variáveis auxiliares indicando o inicio do número (linha coluna) - inicia ao encontrar um valor diferente de 0
//Comparar a matriz com as máscaras, até encontrar um fit
//repetir
int** readfromfile(char* str, int* m, int* n)
{	
    char c;
	FILE *file;
	int i, j, k ;
	file = fopen(str, "rt");
	int countN;	
	char* mchar;
	char* nchar;
	int** original;
	mchar = (char*) malloc(sizeof(char)*5);
	nchar = (char*) malloc(sizeof(char)*5);
	i = 0; j = 0;
	if (file != NULL) {
	
		countN = 0;
    	while (!feof(file))
		{	
			c = fgetc(file);		
			
			if (c=='\n'){
				countN++;			
			}
			if (countN == 1)	
			{
				k = 0;
				while ((c = fgetc(file))!=' ')
				{
					mchar[k] = c;
					k++;
				}
				mchar[k]='\0';				
				*m = (int)atoi(mchar);
				
				k = 0;
				c = fgetc(file);			
				while ((c!=' ')&&(c!='\n'))
				{
					nchar[k] = c;
					k++;
					c = fgetc(file);
				}
				nchar[k] = '\0';				
				*n = (int)atoi(nchar);	
				c = fgetc(file);
				while(c == ' ')
					c = fgetc(file);
				c = fgetc(file); //quebra de linha
				countN++;
				
				original = (int**) malloc((*n) * sizeof(int*));
				for (i = 0 ; i < *n; i++)
					original[i] = (int*) malloc(*m * sizeof(int));
				i=0;
			}
			else if (countN > 1){
					while(c == ' ')
						c = fgetc(file);					
			 	
					if ((c != '\n')&&(c!=EOF))	
					{
						original[i][j] = (int) (c-'0');						
						if (j+1 == *m)
						{
							if (i+1 < *n)
							{
								i++;
								j=0;
							}
						}
						else
							j++;
					}		
				}
		}
		fclose(file);
	}
	else{
		printf("nope");
	}
	return original;	
}
int FindNumber(int** aux, int size_l,int size_c)
{
	int m, n, i, j;
	int countZero = 0;
	int l=0, c=0;
	int number = 0;
	char* filename;
	int start;
	while (number <= 9)
	{
		countZero = 0;
		l=0;
		c=0;
		filename = (char*) malloc(sizeof(char)*10);
		filename[0]	 = (number+'0');
		filename[1] = '\0';
		strcat(filename,".pgm");			
		
		int** mascara = readfromfile(filename, &m, &n);
		if (size_c < m)
			start = size_c;
		else
			start = 0;
		for (i = 0; i < n; i++)
		{
			for (j=start; j < (start + size_c) ; j++)
			{				
			
					if (mascara[i][j] != aux[l][c])		
					{
						countZero++;	
					}					
		
				c++;
			}		
	
			if ((l+1)< size_l)
			{
				l++;
				c=0;
			}
		
		}

			if ((double) countZero/(size_c*n) < 0.065)
				return number;
			number++;
			free(filename);
	}
	number=0;
	return -1;
	
}
void identifynumber(int** original, int m, int n)
{
	int lines = 0, columns = 0;
	int i, j;
	int allZero = 1;
	int countZeros=0;
	int columnstart = -1, linestart = -1, columnstart_aux;
	int columnend, lineend;
	int **aux;
	int number;
	int end = 0;
	int begin_column = 0;
	int pixel_counter=0;
	int numblocks;
	int countPixel;

	while((m - end) >= 30)
	{
		columnstart = -1;
		linestart = -1;
		countZeros=0;
		allZero = 1;
		lines = 0;
		columns = 0;
		
		for (i = begin_column; (i < m) && (allZero); i++)
		{	
			
			countZeros = 0;	
			countPixel = 0;
			numblocks=0;
			pixel_counter = 0;			
			for (j = 0 ; j < n; j++)
			{			
				
				pixel_counter++;
	
				if (original[j][i] == 0){
					countZeros++;
					countPixel++;
				}

				if (pixel_counter == 10){
			
					if ((double)countPixel/10.0 <= 0.50)					
						numblocks++;
			
					pixel_counter = 0;	
					countPixel=0;			
				}	
						
			}

			if (((double)countZeros/n < 0.895)&&(columnstart== -1)&&(numblocks >= 1 ))//começo do numero
			{ 		
			
				columnstart = i;
							
			} else if (((double)countZeros/n >= 0.89)&&(columnstart!=-1)&&(numblocks < 1 )){ //fim do numero 			
				allZero = 0;
				columnend = i;
			}
		}
		columns = columnend - columnstart;

		allZero = 1;
		numblocks = 0;
	
	
		for (i=0; i < n && (allZero); i++)
		{
			countZeros = 0;	
			countPixel = 0;
			numblocks=0;
			pixel_counter = 0;	
			for (j = columnstart; j < columnend; j++)
			{
		
				pixel_counter++;
			
				if (original[i][j] == 0){
					countZeros++;
					countPixel++;
				}
					
				
				if (pixel_counter == 10){
			
					if (((double)(countPixel/10.0)>= 0.90))
						numblocks++;
			
					pixel_counter = 0;	
					countPixel=0;			
				}
					
			}
	
			if ((numblocks < (double)(columns/10.0))&&(linestart== -1)&&((double)countZeros/columns < 0.50))//começo do numero
			{ 			
						
				linestart = i;		
			} else if ((numblocks >= (double)(columns/10.0))&&(linestart!=-1)&&(((double)countZeros/columns > 0.20))){//fim do numero 			
				allZero = 0;
				lineend = i;
			}	
			
		}
		lines = lineend - linestart;
		columnstart_aux = columnstart;
		aux = (int**) calloc (lines, sizeof(int*));
		for (i = 0; i < lines; i++)
		{
			aux[i] = (int*) calloc (columns, sizeof(int));
			for (j=0; j < columns; j++)
			{
	
				aux[i][j] = original[linestart][columnstart];			
				columnstart++;
			}		
			columnstart = columnstart_aux;
			linestart++;
		}	

		number = FindNumber(aux, lines, columns);
		if (number != -1)
			printf("%d", number);
		begin_column = columnend	;
		end = begin_column;
	
		free(aux);
	}	
}

int main(){
	int** original;
	int m, n;
	char* filename;
	filename = (char*) malloc(sizeof(char)*20);
	scanf("%s", filename);
	original = readfromfile(filename, &m, &n);

	identifynumber(original, m, n);
}





