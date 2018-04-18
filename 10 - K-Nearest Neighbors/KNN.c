/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 16/05/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct d{
	int id;
	double dist;
}D;
typedef struct reg{
	char nome[30];
	char tipo[10];
	int tam;
}REG;
union u{
	unsigned char s[50];
	double d;
	int i;
}u;
int FindSize(char atr[30])
{
	int i =0 , k =0;	
	char number[4];

	if (strcmp(atr, "double") == 0)
		return 8;
	if (strcmp(atr, "int") == 0)
		return 4;
	while (atr[i]!='[')
	{
		i++;
	}
	i++;
	while (atr[i]!=']')
	{
		number[k] = atr[i];
		k++;
		i++;		
	}	
	number[k] = '\0';
	return atoi(number);
}
REG* readfromfile(char str[30], char** table, int* index, int* size)
{
	FILE *file;
	REG* vector; 
	vector = (REG*) malloc (sizeof(REG)*20);
	char atrr[30];
	char c;
	int k=0;	
	file = fopen(str, "r");

	if (file != NULL)
	{
		
		while (!feof(file))
		{
			//Lê o nome da tabela
			c= fgetc(file);
			while (c != ' ')//lê até espaço -> table					
				c = fgetc(file);
			c = fgetc(file);
			while ((c!=EOF)&&(c!=' ')&&(c!='\n')) 
			{								
				(*table)[k] = c;				
				c = fgetc(file);			
				k++;
			}
			(*table)[k] = '\0';	
			//adiciona o campo ID no vetor
			strcpy(vector[(*index)].nome, "id");
			strcpy(vector[(*index)].tipo, "int");
			vector[(*index)].tam = 4;
			*size+= 4;
			(*index)++;
			//começa a ler os registros						
			while((c = fgetc(file))!= EOF)
			{
				k=0;
				while(c != ' ') //nome do atributo
				{
					atrr[k] = c;
					c = fgetc(file);
					k++;
				}
				atrr[k] = '\0';
				strcpy(vector[(*index)].nome, atrr);					
				k = 0;
				c = fgetc(file);
				while((c != '\n')&&(c!=EOF)&&(c!='\r')) //tipo do atributo
				{					
					atrr[k] = c;					
					c = fgetc(file);
					k++;
				}
				
				atrr[k] ='\0';
				strcpy (vector[(*index)].tipo, atrr);			
				vector[(*index)].tam = FindSize(atrr);
				*size+= vector[(*index)].tam;
				(*index)++;
			}					
		}
	}
	else{
		printf("no file");
	}
	fclose(file);
	strcpy(vector[(*index)].nome, "dist");
	strcpy(vector[(*index)].tipo, "double");
	vector[(*index)].tam = 8;
	*size+= 8;
	(*index)++;
	return vector;	
}
void ReadData(char* table, REG* vector, int index)
{
	FILE *file;
	char* bytes;
	double dvalue;
	int ivalue;
	int i, j;

	file = fopen(table, "rb");	
	i = 0;
	if (file != NULL)
	{
			
		fseek(file, 0, SEEK_END);
		int fsize = (int)ftell(file);	
		bytes = (char*) malloc(sizeof(char)*100);
		fseek(file, 0, SEEK_SET);
		while (i < fsize)
		{
			for (j = 0; j < index; j++)
			{	
				printf("%s = ", vector[j].nome);
				if (strcmp(vector[j].tipo, "double") == 0)
				{
					fread(&(dvalue), vector[j].tam, 1, file);
					printf("%.2lf\n", dvalue);
				}
					
				else if (strcmp(vector[j].tipo,"int") == 0)
				{
					fread(&(ivalue), vector[j].tam, 1, file);
					printf("%d\n", ivalue);
				}				
				else
				{
					fread((bytes), vector[j].tam, 1, file);
					printf("%s\n", bytes);
				}
				
				i+=vector[j].tam;
			//	printf("i: %d\n", i);
			}
			
		}
	}
	fclose(file);
}
void OrdenaVetor(D* v, int size)
{
	int i, j;
	double aux;
	for (i = 0 ; i < size; i++)
	{
		for (j = i+1 ; j < size; j++)
		{
			if (v[i].dist < v[j].dist)
			{
				aux = v[i].dist;
				v[i].dist = v[j].dist;
				v[j].dist = aux;
			}
		}
	}

}
int SearchId(D* v, int id, int k)
{
	int i;
	for (i = 0 ; i < k ; i++)
	{
		if (v[i].id == id)
			return 1;
	}
	return 0;
}
void CalcDist(char** data, char* table, REG* vector, int index, int k, int size)
{
	int i, j, ivalue, m, id, l;
	FILE *file; 
	D* v;
	char* bytes;
	double dvalue;
	double dist = 0.0;
	file = fopen(table, "rb");	
	v = (D*) malloc(sizeof(D)*size);
	i = 0;
	m = 1;
	l=0;
	
	if (file != NULL)
	{
			
		fseek(file, 0, SEEK_END);
		int fsize = (int)ftell(file);	
		bytes = (char*) malloc(sizeof(char)*100);
		fseek(file, 0, SEEK_SET);	
	
		while (i < fsize)
		{
			for (j = 0; j < index; j++)
			{	
				if ((strcmp(vector[j].tipo, "double")==0)&&(j != (index-1)))
				{
					fread(&dvalue, vector[j].tam, 1, file);	
					if (m < index-2)
					{
						dist+= (double) pow((dvalue - atof(data[m])), 2);
					}			
					m++;
				}
				else if (strcmp(vector[j].tipo, "int")==0)
				{
					fread(&ivalue, vector[j].tam, 1, file);	
					if (j!=0)
					{
					//	printf("int: %d\n", ivalue);
						if (m < index-2)
							dist+= (double )pow((ivalue - atoi(data[m])),2);
						m++;
					}else{
						id = ivalue;
				//		printf("id: %d\n", id);
					}
						
				
				}else
					fread(bytes, vector[j].tam, 1, file);	
				if (j == (index-1)) //dist
				{					
					fread(&dvalue, vector[j].tam, 1, file);	
					dist = sqrt(dist);
				//	printf("dist: %.2lf\n", dist);
					v[l].dist = dist;
					v[l].id = id; 
					l++;
					fwrite(&dist, vector[j].tam, 1, file);								
				}
							
				i+=vector[j].tam;		
			}
			
		}
		OrdenaVetor(v, l);
		fseek(file, 0, SEEK_SET);
		i=0;
	
		while (i < fsize){			
				fread(&(ivalue), vector[0].tam, 1, file); //id
				if (SearchId(v, ivalue, k))
				{
					for (j=0; j < index; j++)
					{			
						if (vector[j].nome)
						printf("%s = ", vector[j].nome);
						if (strcmp(vector[j].tipo, "double") == 0)
						{
							fread(&(dvalue), vector[j].tam, 1, file);
							printf("%.2lf\n", dvalue);
						}
							
						else if (strcmp(vector[j].tipo,"int") == 0)
						{
							fread(&(ivalue), vector[j].tam, 1, file);
							printf("%d\n", ivalue);
						}				
						else
						{
							fread((bytes), vector[j].tam, 1, file);
							printf("%s\n", bytes);
						}	
						
					}
				}
				else
					fread((bytes), size, 1, file);
				i+=size;
			}
			
			
		}	
	
	fclose(file);
}
void SaveToFile (char* table, int id, char** data, REG* vector, int index)
{
	FILE *file;
	int i, ivalue;
	double dvalue;
	
	file = fopen(table, "ab");
	
	if (file != NULL)
	{	
		fwrite(&id, sizeof(int),1,file);
		for (i = 0; i < (index-2); i++)
		{				
			if (strcmp(vector[i+1].tipo, "double")==0)
			{
				dvalue = atof(data[i]);
				fwrite(&dvalue, sizeof(double),1,file);
			}						
			else if (strcmp(vector[i+1].tipo, "int")==0)
			{
				ivalue = atoi(data[i]);
				fwrite(&ivalue, sizeof(int),1,file);
			}	
			else {
				fwrite(data[i], sizeof(char),vector[i+1].tam,file);
			}
		}
		dvalue = 0.0;
		fwrite(&dvalue, sizeof(double),1,file);
	}
	
	fclose(file);
}
int main(){
	char filename[30];
	char* table, *tableraw;
	char** data;
	char command[30];
	int index = 0, i, size = 0, k, id = 0;
	REG* vector;
	strcpy(command," ");
	table = (char*) malloc (sizeof(char)*30);
	tableraw = (char*) malloc (sizeof(char)*30);
	data = (char**) malloc(sizeof(char*) * 100);
	//Ler nome do arquivo
	scanf("%[^\n]", filename);	
	vector = readfromfile(filename, &table, &index, &size);	

	strcpy(tableraw, table);
	for (i = 0; i < 100; i++)
		data[i] = (char*) malloc(sizeof(char)*index);
	k = 0;
	strcat(table,".data");
	while (id!=-1)
	{	
		scanf("%d", &id);	
		k = 0;	
		while((k < (index-2))&&(id!= -1))
		{
			scanf("%s", data[k]);		
			k++;
		}
		//Save to binary file
		if (id!=-1)
			SaveToFile(table, id, data, vector, index);
	}
	while(strcmp(command, "exit")!=0)
	{
		scanf("%s", command);
		if (strcmp(command, "dump_schema") == 0)
		{
			printf("table %s(%d bytes)\n", tableraw, size);	
			for (i = 0; i< index; i++)
			{
				printf("%s %s(%d bytes)\n", vector[i].nome, vector[i].tipo, vector[i].tam);
			}
		}else if (strcmp(command,"dump_data")==0)	
		{
			ReadData(table, vector, index);
		}
		else if (strcmp(command, "dump_nn")==0)
		{
			scanf("%d", &k);
			for (i = 0 ; i < (index-2); i++)
			{
				scanf("%s", data[i]);
			}
		
			CalcDist(data,table, vector, index, k, size);
		}
	}

	free(table);
	free(data);
	free(tableraw);
	free(vector);

}
