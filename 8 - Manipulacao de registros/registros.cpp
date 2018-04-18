#include<stdio.h>
#include<stdlib.h>
//ler o arquivo de metadados pegando o nome do arquivo e os tipos de cada arquivo, salvar a ordem dos tipos num vetor. 
//esperar por comandos 
//se receber um comando "insert": 
	//inserir o registro no arquivo ex: "registros.reg" (binario)
//comando index
	//criar um arquivo binário com extensao idx que conterá para cada registro em registros.reg os valores de chave e o offset. 
	//Ordenar primeiro as chaves e depois calcular os offsets de cada
void readfromfile(char* str)
{	
//	char c;
	FILE *file;
//	int i;
//	int* original;
	file = fopen(str, "rt");
	if (file != NULL) {
		while(!feof(file))
		{
			printf("%c", fgetc(file));
		}
	}
	fclose(file);
	
//		*k = 0;
//	
//    	while (!feof(file))
//		{	
//			c = fgetc(file);				
//				(*k)++;			
//		}
//		fclose(file);
//	}
//
//	(*k)--;
//
//	original = malloc (*k * sizeof(int) );
//	
//	file = fopen(str, "rt");	
//	if (file != NULL) {
//		i = 0;	
//    	while (!feof(file))
//		{	
//			c = fgetc(file);
//			if (i < (*k))	{
//				original[i] = (int)c;				
//				i++;
//			}
//					
//		}
//		fclose(file);
	

}	
int main(){
	char* arquivo;
	
	arquivo = (char*) malloc (sizeof(char)*20);
	scanf("%s", arquivo); 
	
	readfromfile(arquivo);
	
	free(arquivo);
	 
	 
}

	
	
	

