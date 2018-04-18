/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 25/06/2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
double** v_treinamento;
int nimages_train;
double** v_testes;
int nimages_test;
int global_M;

typedef struct node{
	double dist;
	int index;
	struct node*next;
	
}NODE;
int GreaterThanZero(int* matrix, int N)
{
	int count=0;
	int i;
	
	for (i=0; i < N; i++)
	{

		if (matrix[i]>0)
			count++;
	}

	return count;
}
int EqualZero(int* line, int N)
{
	int count=0;
	int i;
	for (i=0; i < N; i++)
	{
		if (line[i]==0)
			count++;
	}
	return count;
}
int SmallerThanZero(int* line, int N){
	int count=0;
	int i;
	for (i=0; i < N; i++)
	{
		if (line[i]<0)
			count++;
	}
	return count;
}
double Media(int* line, int N){
	double media = 0.0;
	int i;
	for (i=0; i < N; i++)
	{
		media+= (double)line[i]*1.0;
	}
	media = (double)media/(N*1.0);
	return media;	
}
double Variancia(int* line, int N, double media){
	double variancia = 0.0;
	double base;
	int i;
	for (i=0; i < N; i++)
	{
		base = (double)line[i]*1.0 - media;	
		variancia+= pow(base,2.0);	
	}
	return (double)variancia/(N*1.0);
}
double Entropia(int* line, int N){
	double h = 0.0;
	int i;
	int b;
	for (i=0; i < N; i++)
	{
		b = abs(line[i]);
		h+= (double)(line[i]*(log2(b+1.0)))*1.0;
	}
	return h*(-1.0);
}
void ConvolucaoTestes(char* filename, int** conv, int m, int nconv, int index)
{
	int M, N, max, i, j, line, k, aux_i, aux_j, l;
	char tipo[5];
	int** m_original;
	int** m_sol;
	int** m_conv;
	FILE* file;	
	unsigned char c;	
	file = fopen(filename, "rb");
	if (file)
	{
		fscanf(file, "%s", tipo);	
		fscanf(file, "%d %d", &N, &M);		
		fscanf(file, "%d", &max);	

		m_original = (int**) malloc(sizeof(int*)*M);
		m_sol = (int**) calloc(M, sizeof(int*));		
		for (i=0; i < M; i++)
		{
			m_original[i] = (int*) malloc(sizeof(int)*N);
			m_sol[i] = (int*) calloc(N, sizeof(int));
		}
		
		for(i=0; i < M; i++)
		{			
			for(j=0; j < N; j++)
			{				
				fread(&c, sizeof(unsigned char), 1, file);		
				m_original[i][j] = (unsigned int)c;	
		//		printf("%d ", m_original[i][j])	;
			}		
		//	printf("\n");
		}
		
	}else{
		printf("file not found\n");
	}
	fclose(file);
	m_conv = (int**) malloc(sizeof(int*)*m);
	for (i=0; i < m ; i++)
	{
		m_conv[i] = (int*) malloc(sizeof(int)*m);
	}
	line = 0;
	int index_j = 0;	
	while (nconv>0)
	{	
		for (i=0; i < M; i++)
		{
			for (j=0; j < N; j++)		
				m_sol[i][j] = 0;
		}
		k=0;
		for (i=line; i < (line+m); i++)
		{
			for (j=0; j < m; j++)
			{
				m_conv[k][j] = conv[i][j];	
			}
			k++;		
		}
	
		for (i=0; i < M; i++)
		{
			for(j=0; j < N; j++)
			{
				aux_i = i - m/2;
				aux_j = j - m/2;
				for (k=0; k < m; k++)
				{
					for(l=0; l < m; l++)
					{
						if ((aux_i>=0)&&(aux_i < M)&&(aux_j>=0)&&(aux_j < N))
						{
							m_sol[i][j] += m_conv[k][l]*m_original[aux_i][aux_j];
						
						}
						aux_j++;
					}	
					aux_j= j - m/2;			
					aux_i++;
				}
			}
		}
		
		for(i=0; i < M; i++)
		{		
			v_testes[index][index_j] = GreaterThanZero(m_sol[i], N);			
			index_j++;
			v_testes[index][index_j] = EqualZero(m_sol[i], N);
			index_j++;
			v_testes[index][index_j] = SmallerThanZero(m_sol[i], N);
			index_j++;
			v_testes[index][index_j] = Media(m_sol[i], N);
			index_j++;
			v_testes[index][index_j] = Variancia(m_sol[i], N, v_testes[index][index_j-1]);
			index_j++;
			v_testes[index][index_j] = Entropia(m_sol[i], N);
			index_j++;
		}
		nconv--;
		line+=m;
	}
}
void Convolucao(char* filename, int** conv, int m, int nconv, int index)
{
	int M, N, max, i, j, line, k, aux_i, aux_j, l;
	char tipo[5];
	int** m_original;
	int** m_sol;
	int** m_conv;
	unsigned char c;
	FILE* file;
	file = fopen(filename, "rb");
	if (file)
	{
		fscanf(file, "%s", tipo);	
		fscanf(file, "%d %d", &N, &M);	
		fscanf(file, "%d", &max);	
		m_original = (int**) malloc(sizeof(int*)*M);
		m_sol = (int**) calloc(M, sizeof(int*));
		for (i=0; i < M; i++)
		{
			m_original[i] = (int*) malloc(sizeof(int)*N);
			m_sol[i] = (int*) calloc(N, sizeof(int));
		}
		
		for(i=0; i < M; i++)
		{			
			for(j=0; j < N; j++)
			{				
				fread(&c, sizeof(unsigned char), 1, file);		
				m_original[i][j] = (unsigned int)c;						
			}		
		}
	}else{
		printf("file not found\n");
	}
	fclose(file);
	m_conv = (int**) malloc(sizeof(int*)*m);
	for (i=0; i < m ; i++)
	{
		m_conv[i] = (int*) malloc(sizeof(int)*m);
	}
	global_M = M;
	line = 0;
	int index_j=0;
	while (nconv>0)
	{	
				
		for (i=0; i < M; i++)
		{
			for (j=0; j < N; j++)		
				m_sol[i][j] = 0;
		}		
		k=0;	
		for (i=line; i < (line+m); i++)
		{
			for (j=0; j < m; j++)
			{
				m_conv[k][j] = conv[i][j];			
			}			
			k++;
		}
		
		for (i=0; i < M; i++)
		{
			for(j=0; j < N; j++)
			{
				aux_i = i - m/2;
				aux_j = j - m/2;
				for (k=0; k < m; k++)
				{
					for(l=0; l < m; l++)
					{
						if ((aux_i>=0)&&(aux_i < M)&&(aux_j>=0)&&(aux_j < N))
						{
							m_sol[i][j] += m_conv[k][l]*m_original[aux_i][aux_j];
						
						}
						aux_j++;
					}	
					aux_j= j - m/2;			
					aux_i++;
				}
			}
		}

		for(i=0; i < M; i++)
		{
		
			v_treinamento[index][index_j] = GreaterThanZero(m_sol[i], N);
			index_j++;
			v_treinamento[index][index_j] = EqualZero(m_sol[i], N);
			index_j++;
			v_treinamento[index][index_j] = SmallerThanZero(m_sol[i], N);
			index_j++;
			v_treinamento[index][index_j] = Media(m_sol[i], N);
			index_j++;
			v_treinamento[index][index_j] = Variancia(m_sol[i], N, v_treinamento[index][index_j-1]);	
			index_j++;
			v_treinamento[index][index_j] = Entropia(m_sol[i], N);
			index_j++;
		}
		nconv--;
		line+=m;		
	}
}
void ReadClasses(char* classes, double** v_classes)
{	
	FILE* file;
	file = fopen(classes, "rb");
	double value;
	int count = 0;
	int i;
	if (file)
	{
		while(!feof(file))
		{
			fscanf(file, "%lf", &value);
			count++;		
		}
	}
	fclose(file);
	(*v_classes) = (double*) malloc(sizeof(double)*count);
	file = fopen(classes, "rb");
	i=0;
	if (file)
	{
		while(!feof(file))
		{
			fscanf(file, "%lf", &value);
			(*v_classes)[i] = value;	
			i++;	
		}
	}
	fclose(file);

}
void ReadTreinamento(char* treinamento, int** conv, int m, int nconv){
	FILE* file;
	char *filename;
	char c;
	char *aux;
	int nimages = 0;
	int i, index;
	aux = (char*) malloc(sizeof(char)*3);
	filename = (char*) malloc(sizeof(char)*50);
	filename[0] = '\0';
	file = fopen(treinamento, "r");
	if(file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
				
			if (c!=EOF)
			{
				if (c=='\n'){
					nimages++;
				}
			}
		}		
		nimages_train = nimages;
		v_treinamento = (double**) malloc(sizeof(double*)*nimages);
		for (i=0; i < nimages; i++)
		{
			v_treinamento[i] = (double*) malloc(sizeof(double)*6000);
		}
	}else{
		printf("file not found\n");
	}
	fclose(file);

	filename[0] = '\0';
	file = fopen(treinamento, "r");
	index = 0;
	if(file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
				
			if (c!=EOF)
			{
				if (c!='\n'){
					aux[0] = c;
					aux[1] ='\0';
					strcat(filename,aux); 
				}						
				else{
					
					Convolucao(filename, conv, m, nconv, index);	
					index++;										
					filename[0]='\0';
				}
			}
		}
		
	}else{
		printf("file not found\n");
	}
	fclose(file);	
	
}
void ReadTestes(char* testes, int** conv, int m, int nconv)
{
	FILE* file;
	char *filename;
	char c;
	char *aux;
	int nimages = 0;
	int i, index;
	aux = (char*) malloc(sizeof(char)*3);
	filename = (char*) malloc(sizeof(char)*50);
	filename[0] = '\0';
	file = fopen(testes, "r");
	if(file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
				
			if (c!=EOF)
			{
				if (c=='\n'){
					nimages++;
				}
			}
		}
		
	}else{
		printf("file not found\n");
	}
	fclose(file);
	nimages_test = nimages;
	v_testes = (double**) malloc(sizeof(double*)*nimages);
	for (i=0; i < nimages; i++)
	{
		v_testes[i] = (double*) malloc(sizeof(double)*6000);
	}
	filename[0] = '\0';
	file = fopen(testes, "r");
	index = 0;
	if(file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
				
			if (c!=EOF)
			{
				if (c!='\n'){
					aux[0] = c;
					aux[1] ='\0';
					strcat(filename,aux); 
				}						
				else{
					ConvolucaoTestes(filename, conv, m, nconv, index);	
					index++;				
					filename[0]='\0';
				}
			}
		}
		
	}else{
		printf("file not found\n");
	}
	fclose(file);
}
void AddToList(NODE **head, double dist, int index)
{
	NODE *p = malloc(sizeof(NODE));
	NODE *q = malloc(sizeof(NODE));
	p->dist = dist;	
	p->index = index;
	p->next = NULL;

	if ((*head)==NULL)
	{
	//	printf("Adding to the head\n");
		*head = p;	
	}else{
		if ((*head)->dist > p->dist)
		{
	//		printf("Adding to the head\n");
			p->next = *head;
			*head = p;		
		}else{
			q = *head;				
			while (q->next!=NULL)
			{
				if (q->next->dist >= p->dist)
				{					
				//		printf("Adding to the middle - != freq \n");
						p->next = q->next;
						q->next = p;							
						return;		
					
				}
				q=q->next;
			}
			//insert at the end	
	//		printf("Adding to the end\n");		
			q->next = p;		
		}	
	}
	
}
double Euclidiana(double* test, double* train, int m)
{
	double aux;
	double sum =0.0;
	int i;
	for (i=0; i < (global_M * 6 * m); i++)
	{
		
		aux = (double)(test[i] - train[i])*1.0;	
		
		sum+= pow(aux, 2);
	}
	sum = sqrt(sum);
	return sum;
}
void PrintKNearest(int K, double* v_classes, NODE* head)
{
	double* labels;
	double aux;
	NODE* p;
	p = malloc(sizeof(NODE));
	int i=0, j;
	labels = (double*)malloc (sizeof(double)*nimages_train);
	p = head;
	while ((i < K)&&(p!=NULL))
	{
		labels[i] = v_classes[p->index];
		p=p->next;
		i++;
	}
	//Ordena o vetor com os K mais proximos de acordo com o label da classe
	for (i=0; i < K; i++)
	{
		for(j=i; j < K; j++)
		{
			if (labels[j] < labels[i])
			{
				aux = labels[j];
				labels[j] = labels[i];
				labels[i] = aux;
			}
		}
	}
//	for (i=0; i < K; i++)
//	{
//		printf("%.3lf ", labels[i]);
//	}
//	printf("\n");
	//Finds the max frequent value
	if (K==1)
	{
		printf("%.3lf\n", labels[0]);			
	}
	else{
		int max = 1;
		int freq = 1;
		double index;
		double value = labels[0];
		for (i=1; i < K; i++)
		{
			if (labels[i]!=value)
			{
				if (freq > max){
					max = freq;
					index = value;
				}					
				value = labels[i];
				freq= 0;
			}
			freq++;		
		}
		if (freq > max){
			max = freq;
			index = value;
		}
		printf("%.3lf\n", index);
//		
//		value = labels[0];
//		freq = 1;
//		for (i=1; i < K; i++)
//		{
//			if (labels[i]!=value)
//			{
//				if (freq == max)
//				{
//					printf("%.3lf\n", labels[i]);	
//					break;
//				}	
//				value = labels[i];
//				freq =0;
//			}
//			freq++;		
//		}
	}
free(labels);
}
void KNN(char* classes, int K, int m){
	int i, j;
	NODE *head= NULL;
	double dist;
	double* v_classes;
	ReadClasses(classes, &v_classes);
	for (i=0; i < nimages_test; i++)
	{
		for (j=0; j < nimages_train;j++)
		{
			dist = Euclidiana(v_testes[i], v_treinamento[j], m);
			AddToList(&head, dist, j);
		}	
		PrintKNearest(K, v_classes, head);
		head = NULL;	
	}
}
int main(){
	char *treinamento;
	char *classes;
	char *testes;
	int** m_conv;
	int i, j, k, m, nmasc;
	
	treinamento = (char*) malloc(sizeof(char)*20);
	classes = (char*) malloc(sizeof(char)*20);
	testes = (char*) malloc(sizeof(char)*20);
	
	scanf("%s", treinamento);
	scanf("%s", classes);
	scanf("%s", testes);
	scanf("%d",  &nmasc);
	scanf("%d", &m);
	m_conv = (int**) malloc(sizeof(int*)*m*nmasc);
	for (i =0; i < m*nmasc; i++)
	{
		m_conv[i] = (int*) malloc(sizeof(int*)*m);
		for (j=0; j < m; j++)
		{
			scanf("%d", &m_conv[i][j]);
		}
		
	}
	scanf("%d", &k);
	
	ReadTreinamento(treinamento, m_conv, m, nmasc);
//	printf("reading tests\n");
	ReadTestes(testes, m_conv, m, nmasc);
	KNN(classes, k, nmasc);

}
