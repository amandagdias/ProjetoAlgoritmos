/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 09/06/2017
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct{
	int freq;
	char* value;
	char* table;	
}VECTOR;
typedef struct h{
	int freq;
	char *str;
	int prob;
	struct h * left;
	struct h* right;
	struct h * next;		
}H;
void AddToList(H **head, H* node)
{
	
	
	int comp;
	H *p = malloc(sizeof(H));
	H *q = malloc(sizeof(H));
	p->freq = node->freq;	
	p->next = node->next;
	p->left = node->left;
	p->right = node->right;
	p->prob = node->prob;
	p->str = malloc(sizeof(char)*200);
	q->str = malloc(sizeof(char)*200);
	strcpy(p->str, node->str);	
	if ((*head)==NULL)
	{
	//	printf("Adding to the head\n");
		*head = p;	
	}else{
		if ((*head)->freq > p->freq)
		{
	//		printf("Adding to the head\n");
			p->next = *head;
			*head = p;		
		}else{
			q = *head;
				
			while (q->next!=NULL)
			{
				if (q->next->freq >= p->freq)
				{
					if (q->next->freq != p->freq)
					{
				//		printf("Adding to the middle - != freq \n");
						p->next = q->next;
						q->next = p;							
						return;		
					}else{
					
						comp = strcmp(q->next->str, p->str);
						if (comp <= 0)
						{
							//q->next->freq is smaller -> goes before
				//			printf("Adding to the middle - == freq insert after\n");
							
							while ((q->next->next!=NULL)&&(q->next->next->freq == p->freq)&&(strcmp(q->next->next->str, p->str) < 0))							
								q = q->next;
							p->next = q->next->next;
							q->next->next = p;	
							return;								
						}
						else if (comp > 0)
						{
							//q->next->freq is greater -> goes after
				//			printf("Adding to the middle - == freq insert before\n");
							p->next = q->next;
							q->next = p;
							return;
						}
					}
							
				}
				q= q->next;
			}
			//insert at the end	
	//		printf("Adding to the end\n");		
			q->next = p;		
		}	
	}
	
}
H* removeFromList(H**head)
{
	H* p = malloc(sizeof(H));
	p->str = malloc(sizeof(char)*10);	
	p = (*head);
	*head = (*head)->next;
	return p;
}
void inOrder(H* node, VECTOR* v, char* path, int level)
{
	int index;
	char* prob = calloc(10, sizeof(char));
	char c;
	if (node)
	{
		
		if (node->prob!=-1)
		{
			prob[0] = node->prob+'0';
			prob[1] = '\0';
			strcat(path, prob);
		}	
		inOrder(node->left, v, path, level+1);
		path[level] = '\0';	
		inOrder(node->right, v, path, level+1);		
		
		if ((node->right==NULL)&&(node->left==NULL))
		{
			if (node->prob!=-1)
			{
				path[level-1] = '\0';
				prob[0] = node->prob+'0';
				prob[1] = '\0';
				strcat(path, prob);
			}
			if (node->str[0]==92)
			{
				index = 32;
			}				
			else
				index = (int)(node->str[0]);	
			v[index].table = calloc(30, sizeof(char));		
			
			strcpy(v[index].table, path);		
		
		}
	}
}

void Montagem(H**head, VECTOR* v)
{
	char* path;
	H* p = malloc(sizeof(H));
	p->str = malloc(sizeof(char)*200);
	H* q = malloc(sizeof(H));	
	q->str = malloc(sizeof(char)*200);
	H* root = malloc(sizeof(H));
	while ((*head)->next!=NULL){
		p = removeFromList(head);
		q = removeFromList(head);	
		root->freq = p->freq + q->freq;
		root->str = calloc(200, sizeof(char));	
		strcat(root->str, p->str);
		strcat(root->str, q->str);	
		p->prob = 0;
		q->prob = 1;
		root->left = p;
		root->right = q;
	//	printf("Adding to list: %s\n", root->str);
		AddToList(head, root);
	//	printf("Added\n");
	}
//	printf("head of the list: %s\n", (*head)->str);
	(*head)->prob = -1;

	path = calloc(50, sizeof(char));
	inOrder((*head), v, path, 0);
	
}
VECTOR* readFromFile(char* str)
{
	FILE *file;
	char c;
	int index;
	VECTOR *v = calloc(256, sizeof(VECTOR));
	file = fopen(str, "r");

	if (file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
			
			if ((c!='\n')&&(c!='\t')&&(c!='\r')&&(c!=EOF))
			{
				index = (int)c;	
			//	printf("%c    %d\n", c, index);
				if (c==' ')
				{		
					v[index].value = calloc(10, sizeof(char));
					v[index].table = NULL;
					v[index].freq++;			
					v[index].value[0] = 92;
					v[index].value[1] = '3';
					v[index].value[2] = '2';
					v[index].value[3] = '\0';
				}else{
					v[index].value = calloc(10, sizeof(char));
					v[index].table = NULL;
					v[index].freq++;
					v[index].value[0] = c;
					v[index].value[1] = '\0';	
				}
			
			}
		}		
	}
	fclose(file);
	return v;
}
void printList(H* head)
{
	while(head)
	{
		printf("%s   %d\n", head->str, head->freq);
		head=head->next;
	}
}
char* createByte(int num)
{
	char* byte = calloc(10, sizeof(char));
	char aux;
	int i=0, start = 0, end;
	while(num !=1)
	{
		
		byte[i] = num%2 + '0';	
		num = num/2;
		i++;
	}
	byte[i] = num +'0';
	i++;
	while(i < 8){
		byte[i] = '0';
		i++;
	}		
	byte[i] = '\0';
	end = strlen(byte)-1;
	while (start < end)
	{
		aux = byte[start];
		byte[start] = byte[end];
		byte[end] = aux;
		start++;
		end--;
	}
	return byte;
}
int convertByte(char* byte)
{
	int r = 0, i;
	int count = 0;
	for (i = 7; i >=0; i--)
	{
		r+= (byte[i]-'0')*pow(2,count);
		count++;
	}
	return r;
}
void printBytes(char* compact)
{
	int i =0, j=0, size;
	char* byte = calloc(10, sizeof(char));
	char* c = malloc(sizeof(char)*2);
	size = strlen(compact);
	while (i < size)
	{
		j=i;
		while (j < (i+8))
		{
			c[0] = compact[j];
			c[1] = '\0';
			strcat(byte, c);
			j++;
		}	
		printf("%d\n", convertByte(byte));
		byte[0] = '\0';
		i+=8;
	}

	free(byte);
	free(c);
}
void Compact(char* str, VECTOR* v){
	char* compact = calloc(4000, sizeof(char));
	int index;
	int i;
	int mod;
	char c;
	char* extra_byte = malloc(sizeof(char)*10);
	FILE *file;
	
	file = fopen(str, "r");
	if (file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
	
			if ((c!='\n')&&(c!='\r')&&(c!='\t')&&(c!=EOF))
			{
				index = (int)c;			
				strcat(compact, v[index].table);
			}
		}
	}
	fclose(file);
//	printf("%s\n", compact);
	mod = strlen(compact)%8;
	if (mod!=0)
	{
		i=0;
		while(i < (8 - mod))
		{
			strcat(compact, "0");
			i++;
		}
		extra_byte = createByte(mod);
//		printf("extra byte: %s\n", extra_byte);
		strcat(compact, extra_byte);
	}
//	printf("Bytes: %s\n", compact);
	printBytes(compact);
	free(compact);
	free(extra_byte);
}
int main(){
	VECTOR *v;
	int i;
	H *head = NULL;
	H* node = malloc(sizeof(H));
	node->str = malloc(sizeof(char)*10);
	char* str = malloc(sizeof(char)*10);
	scanf("%s", str);
	i=0;
	while(str[i]!='.')
	{
		i++;
	}
	if (str[i+1] == 't')
	{
		v = readFromFile(str);
		for (i = 0; i < 128; i++)
		{
			if (v[i].freq > 0)
			{
				node->freq = v[i].freq;
				node->left = NULL;
				node->right = NULL;
				node->prob = -1;
				node->next = NULL;
						
				strcpy(node->str, v[i].value);
				
				AddToList(&head, node);
			}
				
		}	
//		printList(head);
		Montagem(&head, v);
		for(i = 0; i < 128; i++)
		{
			if (v[i].freq > 0)
			{
				if (v[i].value[0] == 92)
				{
					printf("  - %s\n", v[i].table);	
				}else
				{
					printf("%s - %s\n", v[i].value, v[i].table);
				}				
			}
		}
		printf("-\n");
		Compact(str, v);
		
		free(v);
	}
	free(node->str);
	free(node);
	free(head);
	free(str);


}
