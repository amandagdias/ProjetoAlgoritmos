/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 06/05/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//ler o arquivo de metadados pegando o nome do arquivo e os tipos de cada arquivo, salvar a ordem dos tipos num vetor. Calcular também o offset baseando-se nos tipos
//esperar por comandos 
//se receber um comando "insert": 
	//inserir o registro no arquivo ex: "registros.reg" (binario)
	//Se o tipo for double ou float, adiciona em uma lista de precisao as precisoes digitadas 
	//Salvar em uma lista ordenada os valores de chave e offset para cada registro
//comando index
	//Ordenar as chaves 
	//criar um arquivo binário com extensao idx com os valores da lista ordenada 
//comando search
	//verificar se já foi feito um index ou não. Se não foi, faça.
	//Vai até o offset correspondente a chave no arquivo registros.reg e lê de acordo com cada tipo	
union u{
	unsigned char bytes[100];
	int integer;
	double d;
	char c;
	float f;
	char s[100];
	
}u;
struct precision{
	int p;
	int key;
	int used;
	struct precision* next;
}precision;
struct reg{
	int type;
	int size;
	int key;
	struct precision* precision_list;
	int offset;
};	
struct node{
	int key;
	int offset;
	struct node *next;
};
typedef struct reg registros;
typedef struct node idx;
void cleanPrecisionList(struct precision** head)
{
	struct precision* p;
	p = (*head);
	while(p!=NULL)
	{
		p->used = 0;
		p=p->next;
	}
}
int getFromPrecisionList(struct precision** head, int key)
{
	struct precision* p;
	int precision;
	if ((*head) == NULL)
		return -1;
	p = (*head);
	if ((p->key == key)&&(p->used==0))
	{
		precision = p->p;
		p->used = 1;	
		return precision;
	}
	while (p->next!=NULL)
	{

		if ((p->next->key == key)&&(p->next->used==0))
		{
			precision = p->next->p;
			p->next->used = 1;
			return precision;
		}
		p=p->next;		
	}
	
	return -1;
}
void AddToPrecisionList(int prec, int key, struct precision** head)
{
	struct precision* p;
	struct precision* q;
	if ((*head) == NULL)
	{
		p = (struct precision*) malloc (sizeof(struct precision));
		p->p = prec;
		p->key = key;
		p->used = 0;
		p->next = NULL;
		(*head) = p;
	}
	else{
		p = *head;	
		while (p->next!=NULL)
		{
			p = p->next;		
		}	
		q = (struct precision*) malloc (sizeof(struct precision));	
		q->p = prec;
		q->key = key;
		q->used = 0;
		q->next = NULL;
		p->next = q;	
	}
}
void writeAfile(char* info, char* filename, registros** reg, int k)
{
	FILE *file;
	char* s;
	int ival;
	double dval;
	float fval;
	file = fopen(filename, "ab");
	int j = 0, p;

	if (file != NULL)
	{
		if ((*reg)[k].type == 0)
		{
			ival =  (atoi(info));
			fwrite(&ival, sizeof(int),1,file);
		}
		else{
			if ((*reg)[k].type==1)
			{			
				dval = (double)atof(info);
				j=0;		
				while ((info[j]!='.')&&(info[j]!='\0'))
				{				
					j++;
				}
				p=0;
				if (info[j]=='.')
				{
					j++;
					while (info[j]!='\0')
					{
						p++;
						j++;
					}
				}
				AddToPrecisionList(p, (*reg)[0].key, &((*reg)[k].precision_list));
				fwrite(&dval, sizeof(double),1,file);
			}
			else
				if ((*reg)[k].type==2){			
					fwrite(&info[0], sizeof(char),1,file);
				}
			
				else
					if ((*reg)[k].type==3){	
						j=0;		
						while ((info[j]!='.')&&(info[j]!='\0'))
						{					
							j++;
						}
						p=0;
						if (info[j]=='.')
						{
							j++;
							while (info[j]!='\0')
							{
								p++;
								j++;
							}
						}
						AddToPrecisionList(p, (*reg)[0].key, &((*reg)[k].precision_list));
						fval = (float)atof(info);				
			
						fwrite(&fval, sizeof(float),1,file);
						
					}
					
					else
						if((*reg)[k].type==4)
						{
							s = (char*) malloc(sizeof(char)*(*reg)[k].size);
							strcpy(s, info);						
							fwrite(info, (*reg)[k].size,1,file);					
						}
		}
	}
	fclose(file);
}
void SaveIdx(idx* head, char* filename)
{
	FILE *file;
	int i =0;
	idx* p;

	while (filename[i]!='.')
	{
		i++;
	}
	filename[i] = '\0';
	strcat(filename,".idx");

	file = fopen(filename, "ab");	
	
	if (file != NULL)
	{
		p = head;
		while (p!=NULL)
		{
			fwrite(&(p->key), sizeof(int),1,file);
			fwrite(&(p->offset), sizeof(int),1, file);
			p = p->next;
		}

	}
	
	fclose(file);
}
int BinarySearch(int key, idx* v, int size, int start, int end)
{
	int middle;
	if (start>end)
		return -1;
	middle =(int) trunc((start+end)/2.0);
	if ((v[middle].key)==key)
		return v[middle].offset;
	if (v[middle].key > key)
	{
		return BinarySearch(key, v, size, start, middle-1);
	}
	if (v[middle].key < key)
	{
		return BinarySearch(key, v, size, middle+1, end);
	}

	return -1;
}
int Search(idx** v, int key, char* filename, int* vsize)
{
	int i =0;
	FILE *file;
	if (*v==NULL)
	{
		
		while (filename[i]!='.')
		{
			i++;
		}
		filename[i] = '\0';
		strcat(filename,".idx");
	
		file = fopen(filename, "rb");	
		i = 0;
		if (file != NULL)
		{
				
			fseek(file, 0, SEEK_END);
			int fsize = (int)ftell(file);	
			fseek(file, 0, SEEK_SET);
			*vsize = fsize/(2*sizeof(int));
			*v = malloc(sizeof(idx)*(*vsize));
			while (i < fsize/(2*sizeof(int)))
			{
				fread(&((*v)[i].key), sizeof(int), 1, file);
				fread(&((*v)[i].offset), sizeof(int), 1, file);		
				i++;
			}
		
		}
		fclose(file);
	}	
	
	
	return BinarySearch(key, *v, *vsize, 0,  *vsize-1);
}
void InsertCommand(char* insert, registros** r, char* filename, int* metsize){
	int i = 7, j =0;
	char* info;
	int k=0;
	info = (char*) malloc(sizeof(char)*50);
	while(i<strlen(insert))
	{
	
		while ((insert[i] !=',')&&(insert[i]!=' ')&&(i<strlen(insert)))
		{
			if ((insert[i]==34))
			{
				i++;
				while (insert[i]!=34){
					info[j] = insert[i];
					i++;
					j++;
				}	
				i++;			
			}
			else{
				info[j] = insert[i];
				i++;
				j++;
			}
				
		}
		if(j>0)
		{
			info[j]='\0';	
	    	if (k == 0 )
	    		(*r)[k].key = atoi(info);
			writeAfile(info, filename, &(*r), k);
			(*metsize)++;	
			k++;
		}
	
		i++;
		j=0;	
	
	}
		
		
}


void AddListIdx(int key, idx** head, int offset)
{
	idx* p;
	idx* q;

	q = (idx*) malloc (sizeof(idx));
	
	if ((*head) == NULL)
	{
		p = (idx*) malloc (sizeof(idx));
		p->key = key;
		p->offset = offset;
		p->next = NULL;
		(*head) = p;
	}
	else{
		p = *head;	
		while ((p->next!=NULL)&&(key > (p->next)->key))
		{
			p = p->next;		
		}
		if ((p == *head)&&(p->key > key)) //insert at begining
		{		
		
			q->key = key;
			q->offset = offset;
			q->next = *head;		
			*head = q;  		
		}
		else if(p->key < key){//insert at end or middle
			q->key = key;
			q->offset = offset;
			q->next = p->next;
			p->next = q;	
		}
	}
}
int getoffset(char* type, int size)
{

	if (strcmp(type,"int")==0)
		return sizeof(int);
	if (strcmp(type, "double")==0)
		return sizeof(double);
	if (strcmp(type, "char")==0)
		return sizeof(char);
	if (strcmp(type, "float")==0)
		return sizeof(float);
	else
		return sizeof(char)*size;
}

int gettype(char* type)
{

	if (strcmp(type,"int")==0)
		return 0;
	if (strcmp(type, "double")==0)
		return 1;
	if (strcmp(type, "char")==0)
		return 2;
	if (strcmp(type, "float")==0)
		return 3;
	else
		return 4;
}
void readfromfile(char* str, registros** types, char** filename, int *tam)
{	
	char c;
	char *info;
	FILE *file;
	char*size;
	int i =0, j = 0, m, k;
	int count = 0 ;

	file = fopen(str, "rt");
	size = (char*) malloc(sizeof(char)*10);
	*filename = (char*) malloc(sizeof(char)*20);
	info = (char*) malloc(sizeof(char)*50);

	if (file != NULL) {
		while(!feof(file))
		{
			c = fgetc(file);
	
			if (c!=EOF)
			{
			
				if (c==' ')
				{
				
					c = fgetc(file);
					while((c!='\n')&&(c!=EOF))
					{
						info[i]	= c;
						i++;
						c = fgetc(file);
						
					}						
					info[i] = '\0';
					
					if (count == 0)
						strcpy(*filename, info);
					else
					if ((count % 2)==0)
					{						
						(*types)[j].type = gettype(info);					
					
						if ((*types)[j].type == 4)
						{
							m = 5;  
							k=0;							
							while(info[m]!=']'){
								size[k] = info[m];
								k++;
								m++;
							}
							(*types)[j].size = atoi(size);				
						}
						else
							(*types)[j].size = 1;
						(*types)[j].offset = getoffset(info, (*types)[j].size);
						
						if ((*types)[j].type == 3)
						{
							(*types)[j].precision_list = NULL;
						}
						j++;
					}					
					
					count++;		
					i=0;
				}	
			}		
		}
		*tam = j;
	}
	else{
		printf("af");
	}
	fclose(file);
}	
void ShowRegister(int start, int size, char* filename, registros* types)
{
	int i =0, count = 0;
	int code;
	FILE *file;
	int precision;
	char result[100];
	while (filename[i]!='.')
	{
		i++;
	}
	filename[i] = '\0';
	strcat(filename,".reg");
	file = fopen(filename, "rb");
	if (file != NULL)
	{
				
		fseek(file, start, SEEK_SET);			
		i = 0;		

		count = 0;
		while (count < size)
		{
		
			fread(result,  types[i].offset, 1, file);
			memcpy(u.bytes, result,types[i].offset);		
			if (types[i].type == 0)
			{				
				printf("%d\n", u.integer);
				if (count == 0)
				{
					code = u.integer;
				}
			}
			else if (types[i].type==1)
			{
				precision = getFromPrecisionList(&(types[i].precision_list), code);
				printf("%.*lf\n", precision, u.d);
			}
			else if (types[i].type==2)
			{
				printf("%c\n", u.c);
			}
			else if (types[i].type==3){		
				precision = getFromPrecisionList(&(types[i].precision_list), code);	
				printf("%.*f\n", precision, u.f);
				
			}
			else if (types[i].type == 4)
			{	
				printf("%s\n", u.bytes);				
			}		
			count+=types[i].offset;
			i++;
		
		}
	}
	
	fclose(file);
}
int main(){
	char* arquivo;
	char* command;
	char* action;
	char* key;
	int i, k ;
	char* filename;
	int size;
	int offset = 0;
	int offset_count = 0 ;
	int vsize;
	int offset_search;
	idx* head = NULL;	
	registros* types = NULL;

	int metsize = 0;
	idx* v = NULL;
	int index = 0;
	types = (registros*) malloc(sizeof(registros)*50);
	arquivo = (char*) malloc (sizeof(char)*20);
	command = (char*) malloc (sizeof(char)*100);
	action = (char*) malloc (sizeof(char)*10);
	key= (char*) malloc (sizeof(char)*10);


	scanf("%s", arquivo); 
	readfromfile(arquivo, &types, &filename, &size);
	

		
	for (i = 0; i < size; i++)
		offset += types[i].offset;	

	scanf(" %[^\n]", command);
	i = 0;
	while ((command[i]!=' ')&&(command[i]!=EOF)&&(command[i]!='\n')){
		action[i] = command[i];
		i++;
	}		
	action[i] = '\0' ;	
	while (strcmp(action, "exit")!=0){

		if (strcmp(action, "insert")==0)
		{
			InsertCommand(command, &types, filename, &metsize);
	
			AddListIdx(types[0].key, &head, offset_count);

			offset_count+=offset;
		}
		else if (strcmp(action,"search")==0)
		{		
			if (index == 0)
			{
				SaveIdx(head, filename);
				head = NULL;
				index = 1;
			}
			k=0;
			i++;
			while ((command[i]!=' ')&&(command[i]!=EOF)&&(command[i]!='\n')){
				key[k] = command[i];
				i++;
				k++;			
			}
			key[k] = '\0';
					
			offset_search = Search(&v, atoi(key), filename, &vsize);
			if (offset_search!=-1)
			{	
							;
				for (i= 0; i < metsize; i++)
				{
					
					if ((types[i].type == 3)||(types[i].type==1))
						cleanPrecisionList(&(types[i].precision_list));
				}							
				ShowRegister(offset_search, offset, filename, types);
			}
		
		}
		else if (strcmp(action,"index")==0){
			index = 1;
			SaveIdx(head, filename);
			head = NULL;
		}
		scanf(" %[^\n]", command);
		i = 0;
		while ((command[i]!=' ')&&(command[i]!=EOF)&&(command[i]!='\n')){
			action[i] = command[i];
			i++;
		}		
		action[i] = '\0' ;	
		
	
	}
	free(arquivo);
	free(types);
	free(command);
	free(action);
	free(key);
	 
	 
}

	
	
	

