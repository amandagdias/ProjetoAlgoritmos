/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 15/05/2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Compactar(int** original, int m, int n, int max)
{
	int i, j, value, count, k;
	i = 0; j =0, count = 0;	
	printf("P8\n");
	printf("%d %d\n", m, n);
	printf("%d\n", max);
	while (i < n)
	{
		count = 0;
		value = original[i][j];
		while ((original[i][j] == value)&&(j < m))
		{
			count++;			
			j++;			
		}	
		if (count > 3)
		{
			printf("@ ");
			printf("%d ", value);
			if (j==m)
				printf("%d", count);	
			else
				printf("%d ", count);			
		}
		else{
			for (k=0; k < count; k++)
			{
				if ((j==m)&&(k == (count-1)))
					printf("%d", value);
				else
					printf("%d ", value);	
			}
		}
		if (j == m)
		{
			j = 0;
			i++;
			printf("\n");
		}	
	}	
}
int** readPGM(char* tipo, int m, int n, int max)
{	
   	int i, j, value, rep, k, count;
	int** original;
	char* temp;
	char** s;
	temp = (char*) malloc(sizeof(char)*5);
	s = (char**) malloc(sizeof(char*)*n);
	for (i=0; i < n; i++ )
		s[i] = (char*) malloc(sizeof(char)*4*m);
	if (strcmp(tipo, "P2")==0)	
	{
		original = (int**) malloc(sizeof(int*)*n);
		for (i = 0 ; i < n; i++)
		{
			original[i] = (int*) malloc(sizeof(int)*m);
		}
		for (i = 0; i < n; i++)
		{
			for (j=0; j < m; j++)
			{
				scanf("%d", &value);
				original[i][j] = value;
			}
		}	
	}
	else{	
	
		i=0;
		count = 0;		
		while (i < n)
		{
			scanf(" %[^\n]", s[i]);
			i++;
		}
		printf("P2\n");
		printf("%d %d\n", m, n);
		printf("%d\n", max);
		for (i = 0; i < n; i++)
		{
			j=0;
	
			while((s[i][j]!='\0')&&(s[i][j]!='t')&&(s[i][j]!='e'))
			{
				if ((s[i][j]=='@')&&(s[i][j]!='\0'))
				{					
					j+=2;
					k=0;
					while((s[i][j]!=' ')&&(s[i][j]!='\0'))
					{
						temp[k] = s[i][j];
						k++;
						j++;
					}					
					temp[k] = '\0';
					value = atoi(temp);					
					j++;
					k=0;							
					while((s[i][j]!=' ')&&(s[i][j]!='\0')&&(s[i][j]!='t')&&(s[i][j]!='e'))
					{
						temp[k] = s[i][j];
						k++;
						j++;
					}	
					temp[k] = '\0';
					rep = atoi(temp);							
					j++;
					count+=rep;				
					for (k=0; k < rep; k++)
					{
						if (count == (m-1))
							printf("%d", value);
						else
							printf("%d ", value);
					}			
				}	
				if ((s[i][j]!=' ')&&(s[i][j]!='\0')&&(s[i][j]!='@')&&(s[i][j]!='t')&&(s[i][j]!='e'))
				{
					k=0;
					count++;
					while((s[i][j]!=' ')&&(s[i][j]!='\0')&&(s[i][j]!='t')&&(s[i][j]!=EOF))
					{
						temp[k] = s[i][j];
						k++;
						j++;						
					}
					temp[k] = '\0';
					if (count == (m-1))
						printf("%d", atoi(temp));
					else
						printf("%d ", atoi(temp));
					if (s[i][j]==' ')
						j++;			
				}				
			}	
			printf("\n");
		
		}	
	}
	
	return original;
}
int main(){
	int** original;	
	int m, n, max;
	char* tipo;
	
	tipo = (char*) malloc(sizeof(char)*5);
	scanf("%s", tipo);
	scanf("%d %d", &m, &n);
	scanf("%d", &max);	
	
	if (strcmp(tipo, "P2") == 0)
	{
		original = readPGM(tipo, m, n, max);
		Compactar(original, m, n, max);
	}
	else{
		original = readPGM(tipo, m, n, max);
	}

}
