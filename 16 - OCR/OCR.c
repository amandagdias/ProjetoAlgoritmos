/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 14/06/2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct reg{
	char nome[30];
	char tipo[10];
	int tam;
}REG;
void mem_dist(){
	int l, c, i;
	int dist = 0;
	char* A;
	char* buffer;
	char* dists;
	dists = malloc(sizeof(char)*10);
	buffer = malloc(sizeof(char)*20);
	FILE *file;
	char* B;
	scanf("%d %d", &l, &c);
	
	A = malloc(sizeof(char)*l*c);
	B = malloc(sizeof(char)*l*c);
	scanf("%s", A);
	scanf("%s", B);
	for (i=0; i < (l*c); i++)
	{
		if (A[i]^B[i])
			dist++;
	}
	file = fopen("out", "a");
	if (file)
	{
		strcpy(buffer, "dist = ");
		sprintf(dists, "%d", dist);
		strcat(buffer, dists);
		strcat(buffer, "\n");
		fprintf(file, "%s", buffer);
	}	
	fclose(file);
	free(buffer);
	free(dists);
	
}
void SaveToFile(int** AI, int** EI, int** S, int il, int ic, int el, int ec)
{
	int size;
	int i, j;
	size = ((2*il*ic+(ec*el))+(2*il + el))*10;
	char* buffer = malloc(sizeof(char)*size);
	char* dists;
	FILE *file;
	file = fopen("out", "a");
	if (file)
	{
		strcpy(buffer, "im:\n");
		dists = malloc(sizeof(char)*(il*ic));
		for (i=0; i < il; i++)
		{
			for (j=0; j < ic; j++)
			{
				sprintf(dists, "%d ", AI[i][j]);
				strcat(buffer, dists);
			}
			strcat(buffer,"\n");
		}		
		strcat(buffer, "el:\n");
		free(dists);
		dists = malloc(sizeof(char)*(el*ec));
		for (i=0; i < el; i++)
		{
			for (j=0; j < ec; j++)
			{
				sprintf(dists, "%d ", EI[i][j]);
				strcat(buffer, dists);
			}
			strcat(buffer,"\n");
		}
		strcat(buffer, "out:\n");
		free(dists);
		dists = malloc(sizeof(char)*(il*ic));
		for (i=0; i < il; i++)
		{
			for (j=0; j < ic; j++)
			{			
				sprintf(dists, "%d ", S[i][j]);			
				strcat(buffer, dists);
			}		
			strcat(buffer,"\n");
		}	
		fprintf(file, "%s", buffer);
	}	
	fclose(file);
	free(buffer);
}

void SaveIntMatrix(int** AI, int** EI, char* A, char* E, int il, int ic, int el, int ec)
{
	int i, j, k;
	k=0;
	for (i=0; i < il; i++)
	{
		for (j=0; j < ic; j++)
		{
			AI[i][j] = A[k] - '0';		
			k++;
		}
	}
	k=0;

	for (i=0; i < el; i++)
	{
		for (j=0; j < ec; j++)
		{
			EI[i][j] = E[k]-'0';		
			k++;
		}	
	}
}
void erode(int** AI, int** EI, int**S, int il, int ic, int el, int ec)
{	
	int i, j, Center;
	Center = el/2;
	int m=0,n=0;
	int iaux, jaux;
	int copy = 1;
	for (i=Center; i <(il-Center);i++)
	{
		for (j=Center; j < (ic-Center); j++)
		{
				iaux = i - Center;
				jaux = j - Center;
				copy = 1;
				for (m = 0; m < el; m++)
				{
					jaux = j - Center;
					for (n=0; n < ec; n++)
					{
						if (EI[m][n]==1)
						{
							if (AI[iaux][jaux]!=EI[m][n])
							{
								copy = 0;
								break;
							}		
						}								
						jaux++;
					}
					iaux++;
				}
				if (copy)
				{
					S[i][j] = 1;
				}	
		}
	}
}

void dilate(int** AI, int** EI, int**S, int il, int ic, int el, int ec)
{

	int i, j, Center;	
	Center = el/2;
	int m=0,n=0;
	int iaux, jaux;
	for (i=Center; i <(il-Center);i++)
	{
		for (j=Center; j < (ic-Center); j++)
		{
			if (AI[i][j]==1)
			{
				iaux = i - Center;
				jaux = j - Center;
				for (m = 0; m < el; m++)
				{
					jaux = j - Center;
					for (n=0; n < ec; n++)
					{
						if (EI[m][n]==1)
						{
							S[iaux][jaux] = 1;
						}
						jaux++;
					}
					iaux++;
				}
				
			}
		}
	}
}
void mem_op()
{
	int il, ic, el, ec, i, j;
	char* A;
	char* E;
	int** AI, **EI, **Copy;
	int** S;
	char* command; 
	command = malloc(sizeof(char)*10);
	scanf("%d %d", &il, &ic);
	A = malloc(sizeof(char)*(il*ic));
	Copy = malloc(sizeof(char)*(il*ic));
	S = (int**) calloc(il, sizeof(int*));
	for (i=0; i < il; i++)
	{
		S[i] = (int*)calloc(ic, sizeof(int));
		Copy[i] = (int*)malloc(sizeof(int)*ic);
	}
	scanf("%s", A);
	scanf("%d %d", &el, &ec);
	E = malloc(sizeof(char)*(el*ec));
	scanf("%s", E);
	AI = (int**) malloc(sizeof(int*)*il);
	for (i=0; i < il; i++)
	{	
		AI[i] = (int*)malloc(sizeof(int)*ic);
	}
	EI = (int**) malloc(sizeof(int*)*el);
	for (i=0; i < el; i++)
	{
		EI[i] = (int*) malloc(sizeof(int)*ec);
	}
	SaveIntMatrix(AI, EI, A, E, il, ic, el, ec);
	scanf("%s", command);
	if (strcmp(command, "dilate")==0){
		dilate(AI, EI, S, il, ic, el, ec);
		SaveToFile(AI, EI, S, il, ic, el, ec);
	}	
	else{
		if (strcmp(command,"erode")==0){
			erode(AI, EI, S, il, ic, el, ec);
			SaveToFile(AI, EI, S, il, ic, el, ec);	
		}else{
			if(strcmp(command,"open")==0)
			{
				erode(AI, EI, S, il, ic, el, ec);			
				for (i = 0; i < il; i++)
				{
					for (j=0; j < ic; j++)
					{
						Copy[i][j] = S[i][j];
						S[i][j] = 0;						
					}				
				}
				dilate(Copy, EI, S, il, ic, el, ec);
				SaveToFile(AI, EI, S, il, ic, el, ec);					
			}else{
				if (strcmp(command, "close")==0)
				{
					dilate(AI, EI, S, il, ic, el, ec);			
					for (i = 0; i < il; i++)
					{
						for (j=0; j < ic; j++)
						{
							Copy[i][j] = S[i][j];						
							S[i][j] = 0;						
						}							
					}
					erode(Copy, EI, S, il, ic, el, ec);
					SaveToFile(AI, EI, S, il, ic, el, ec);
				}
			}
		}
	}
		
		
}
void readFile()
{
	FILE *file;
	file = fopen("out", "r");
	char c;
	if (file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
			if (c!=EOF)
				printf("%c", c);
		}
	}	
	fclose(file);


}
void SaveSchemaToFile(int index, char* tableraw, int size, REG* vector) 
{
	FILE *file;
	int i;
	char* buffer = malloc(sizeof(char)*200);
	char* sizes = malloc(sizeof(char)*10);
	file = fopen("out", "w");
	if (file)
	{
		strcpy(buffer,"table " );
		strcat(buffer, tableraw);
		strcat(buffer, "(");
		sprintf(sizes, "%d", size);
		strcat(buffer, sizes);
		strcat(buffer, " bytes)\n");
		for (i = 0; i< index; i++)
		{
			strcat(buffer,vector[i].nome);
			strcat(buffer," ");
			strcat(buffer, vector[i].tipo);
			strcat(buffer,"(");
			free(sizes);
			sizes = malloc(sizeof(char)*10);
			sprintf(sizes, "%d", vector[i].tam);
			strcat(buffer,sizes);
			strcat(buffer," bytes)\n");		
		}
		fprintf(file, "%s", buffer);
	}
	fclose(file);
	free(buffer);

}
void ReadData(char* table, REG* vector, int index)
{
	FILE *file;
	char* bytes;
	double dvalue;
	int ivalue;
	int i, j, k;
	char tipo[10];
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
					k = 0;
					while (vector[j].tipo[k]!='[')
					{
						tipo[k] = vector[j].tipo[k];
						k++;
					}
					if (strcmp(tipo, "char"))
					{
						fread((bytes), vector[j].tam, 1, file);
						printf("%s\n", bytes);
					}else{
						fread(&(ivalue), sizeof(int), 1, file);
						printf("%d\n", ivalue);
					}			
				}
				
				i+=vector[j].tam;		
			}
			
		}
	}
	fclose(file);
}
int ConvertToInt(char* data)
{
	int r=0, count = 0, i;
	for (i=strlen(data); i>=0; i--)
	{
		r+= (data[i]-'0') * pow(2,count);
		count++;
	}
	return r;
}
void SaveToFileSchema (char* table, int id, char** data, REG* vector, int index)
{
	FILE *file;
	int i, ivalue, k;
	char tipo[10];
	double dvalue;
//	char tipo[10];
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
			else{
				k=0;			
				while(vector[i+1].tipo[k]!='[')
				{	
					tipo[k] = vector[i+1].tipo[k];
					k++;
				}
				tipo[k]='\0';				
			    if (strcmp(tipo, "char")==0){
			    	
			    	fwrite(data[i], sizeof(char), vector[i+1].tam,file);
				
				}else{	
					fwrite(data[i], sizeof(char), vector[i+1].tam,file);
				}
			} 
		}
		dvalue = 0.0;
		fwrite(&dvalue, sizeof(double),1,file);
	}
	
	fclose(file);
}
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
int main(){
	char* str;
	char* table, *tableraw;
	char** data;
	str = malloc(sizeof(char)*10);
	FILE *file;
	REG* vector;
	file = fopen("out", "w");
	fclose(file);
	int index=0, id =0, size=0, i, k;
	table = (char*) malloc (sizeof(char)*30);
	tableraw = (char*) malloc (sizeof(char)*30);
	data = (char**) malloc(sizeof(char*) * 100);
	while (strcmp(str, "exit")!=0)
	{
		scanf("%s", str);
		if (strcmp(str, "none")==0)
		{
			scanf("%s", str);
			
			while (strcmp(str, "mem_dist")==0){				
				mem_dist();			
				scanf("%s", str);
			}
			while (strcmp(str,"mem_op")==0)
			{
				mem_op();
				scanf("%s", str);				
			}	
		}else{
			//Read file.schema
			vector = readfromfile(str, &table, &index, &size);	
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
					SaveToFileSchema(table, id, data, vector, index);
			}
			scanf("%s", str);
			while(strcmp(str, "exit")!=0)
			{
				if (strcmp(str, "dump_schema") == 0)
				{
					SaveSchemaToFile(index, tableraw, size, vector);			
					scanf("%s", str);
				}
				if (strcmp(str,"dump_data")==0)
				{
			//		ReadData(table, vector, index);
					scanf("%s", str);
				}
			}
		
			
		}
			
		
	}
	readFile();

}
