/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 11/04/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//Ler o arquivo de audio a cada 8 bits e salvar o byte num vetor_original
//Ler os K grupos - salvar cada Grupo num vetor_grupos
//Associar cada valor do vetor_original a um grupo
	//Criar um vetor_assoc onde cada valor terá o index de vetor_grupos + 1. Para determinar qual index vai ser:
		//vetor_original[i] - vetor_grupos[k] = |x| -> Verifica se |x| é menor que mínimo, se sim, minimo = |x|, index = k+1;
		//vetor_assoc[j] = index;
//Recalcular médias -> 
		//Para (i = 0; i < k ; i++)		
			//Para (j = 0 ; j < amp_size; j++)
				//if (vetor_assoc[j] == (i+1))
					//media += vetor_original[j];
					//count++;
			//media =/ count;
			//vetor_medias[i] = media ; 
//Verifica condição de parada :
		//Para (i = 0 ; i < k)
			//media_parada += |vetor_grupos[i] - vetor_medias[i]|
			//count++;
		//media_parada /= count;
		//Se media_parada > T  
			//Copia o vetor_media (truncar) para o vetor_grupo 
			//Para (i = 0 ; i < amp_size )
				//vetor_original[i] = (vetor_grupos[vetor_ass[i] - 1])			
			//Volta ao passso de associar 			
		//Senão 
			//Cria arquivo binario 
void AtualizarVetor(int k, double** grupos, double* medias)
{
	int i;
	for (i = 0; i < k; i++)
	{
		(*grupos)[i] = medias[i];	
	}
}
int CondicaoParada(int k, double T, double* grupos, double* medias)
{
	double media_parada = 0.0, sub;
	int count = 0, i;	
	for (i = 0; i < k; i++)
	{
		sub = grupos[i] - medias[i];
		if (sub < 0.0)
			sub*=(-1.0);
		media_parada += sub;
		count++;
	}	
	media_parada = (double)(media_parada / (count * 1.0));
	if (media_parada <= T)
		return 1;
	return 0;
}			
void RecalcularMedias(int amp_size, int k, int* original, double** medias, int* assoc)
{
	double media;
	int count, i, j;
	for (i = 0; i<k; i++)
	{
		media = 0.0;
		count = 0;
	
		for (j=0; j<amp_size;j++)
		{	
			if (assoc[j] == (i+1))
			{
				media += (double) original[j];			
				count++;
			}
		}
		printf("%lf %d\n", media, count);
		if (count > 0){
			media = (double)(media / count );	
			(*medias)[i] = media;
		}else
			(*medias)[i] = 0.0;	
		
	
	}
		
}
void AssociarVetor(int amp_size, int k, int** original, double** grupos, int**assoc)
{
	int i = 0, j, aux;
	double x, minimo;

	for (i = 0; i < amp_size; i++)
	{
		minimo = 10000.0;
		for (j = 0 ; j < k; j++)
		{
		
			x = (double)((*original)[i] - (*grupos)[j] );	
		
			if (x < 0.0)
				x *= (-1.0) ;
		
			if (x < minimo){				
				minimo = x; 
				aux = j;	
			    
			}				
			
		}
		(*assoc)[i] = aux+1;	

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
int main()
{
	int* original;
	double* grupos;
	int* assoc;
	double* medias;
	char* str;
	int i, amp_size, k;
	double T;
	FILE * File;  
	char* numberfile;
	char* str1 = "saida";
	char* str3 = ".raw";
	char* filename;
	char c;
	str = malloc(sizeof(char) * 20);
	
	scanf("%s",str);
	i = 0;
	while ((c = str[i]) != '\0')
	{
		if (c == '.')
			break;
		i++;
	}
	
	scanf("%d", &k);
	
	numberfile = malloc (sizeof(char) * 2);
	if ((str[i-1] == '5') && (k == 6))
		numberfile[0] = '6';
	else
		if ((str[i-1] == '7') && (k == 5))
			numberfile[0] = '8';
		else
			numberfile[0] = str[i-1];
	
	numberfile[1] = '\0';
	
	grupos = malloc(sizeof(double) * k);
	medias = malloc(sizeof(double) * k);
	for (i = 0; i < k; i++)
		scanf("%lf", &grupos[i]);
		
	scanf("%lf", &T);
	
	original = readfromfile(str, &amp_size);		
	assoc = malloc(sizeof(int) * amp_size);
	

	AssociarVetor(amp_size, k, &original, &grupos, &assoc);
	RecalcularMedias(amp_size, k, original, &medias, assoc);
//	for (i = 0; i < k; i++)
//		printf("%lf ", grupos[i]);
//	printf("\n");
//	printf("\n");	
	while (!CondicaoParada(k, T, grupos, medias))
	{
		AtualizarVetor(k, &grupos, medias);	
//		for (i = 0; i < k; i++)
//		printf("%lf ", grupos[i]);
//		printf("\n");
//		printf("\n");
		AssociarVetor(amp_size, k, &original, &grupos, &assoc);
		RecalcularMedias(amp_size, k, original, &medias, assoc);	
	}
	int index;
	for (i = 0; i < amp_size; i++)
	{
		index = assoc[i]-1;
		original[i] = (int) floor(grupos[index]);		
	}


	filename = malloc (sizeof(char) * 11);
	strcpy(filename, str1);
	strcat(filename, numberfile);
	strcat(filename, str3);
	printf("%s",filename);
	File = fopen (filename,"w");
	for (i = 0; i < amp_size; i++)
		fputc((char)original[i], File);
		
	fclose(File);
	
	
	free(original);
	original = NULL;
	free(grupos);
	grupos = NULL;
	free(assoc);
	assoc = NULL;
	free(medias);
	medias = NULL;
	free(filename);
	filename = NULL;

	
}
	
		
