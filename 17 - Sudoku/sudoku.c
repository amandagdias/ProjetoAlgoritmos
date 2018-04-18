/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 12/06/2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef struct node{
	int v;
	struct node* next;
}NODE;

typedef struct{
	int value;
	NODE *head;	
}S;
char **allocMat(int c, int r){
	int i;
	char** mat = calloc(r, sizeof(char*))	;
	for (i=0; i < c; i++)
	{
		mat[i] = calloc(c, sizeof(char));
	}
	return mat;
}

char **readMat(int *c, int *r){

	*c = 0;
	*r = 0;
	int i;
	char** mat;
	char ch = '0';
	char* str = calloc(300, sizeof(char));
	char* line = malloc(sizeof(char)*20);
	
	while ((*r)<16)
	{
		scanf("%s", line);		
		strcat(str, line);
		(*r)++;	
	}
	mat = malloc(sizeof(char*)*(16));
	for (i=0; i < 16; i++)
	{
		mat[i] = malloc(sizeof(char)*(16));
	}
	i = 0;
	*r = 0;
	*c = 0;
	while((*r) < 16)
	{
		while((*c) < 16)
		{
			ch = str[i];		
			i++;
			mat[(*r)][(*c)] = ch;
			(*c)++;	
			
				
		}	
		(*c) = 0;
		ch='0';
		(*r)++;
	}
	(*c) = 16;
	
//	file = fopen(path, "r");
//
//	if (file)
//	{
//		while (!feof(file))
//		{
//			ch = fgetc(file);
//			printf("%c", ch);
//			if ((ch!='\n')&&(ch!=EOF))
//			{	
//				if ((*r) ==0)			
//					(*c)++; 
//			}else{	
//				if (ch=='\n')							
//					(*r)++;
//				
//			}
//		}
//	}	
//	fclose(file);
	
//	file = fopen(path, "r");
//	*c = 0;
//	*r = 0;
//	if (file)
//	{
//		while (!feof(file))
//		{
//			ch = fgetc(file);			
//			if ((ch!='\n')&&(ch!=EOF))
//			{				
//				mat[(*r)][(*c)] = ch;
//				(*c)++; 
//			}else{
//				if (ch=='\n')
//				{
//					(*c) = 0;
//					(*r)++;
//				}
//			}
//		}
//	}
//	printf("\n");
//	(*c)--;
//	fclose(file);
	return mat;
}

void printMat(char **mat, int c, int r){
	int i, j;
	for (i=0; i < r; i++)
	{
		for (j=0; j < c; j++)
		{
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}
}

int getValue(char c)
{
	if (c == '.')
		return -1;	
	if (c=='A')
		return 10;
	if (c =='B')
		return 11;
	if (c=='C')
		return 12;
	if (c=='D')
		return 13;
	if (c=='E')
		return 14;
	if (c=='F')
		return 15;
	if (c=='0')
		return 0;
	if (c=='1')
		return 1;
	if (c=='2')
		return 2;
	if (c=='3')
		return 3;
	if (c=='4')
		return 4;
	if (c=='5')
		return 5;
	if (c=='6')
		return 6;
	if (c=='7')
		return 7;
	if (c=='8')
		return 8;
	return 9;
}

NODE* CreateFullList(int r){
	NODE* head;
	NODE *p, *q;
	int i;
	head = malloc(sizeof(NODE));	
	head->v = 0;
	head->next = NULL;
	p = head;
	for (i=1; i < r; i++)
	{		
		q = malloc(sizeof(NODE));
		q->v = i;
		q->next = NULL;
		p->next = q;
		p=p->next;
	}

	return head;
}

void CheckLineandColumn(S** sudoku, NODE** head, int n, int line, int column)
{
	NODE* p;
	p = malloc(sizeof(NODE));
	p = *head;
	int i, j;
	int startL, endL, startC, endC;
	int regionC, regionL; 
	for (i=0; i < n; i++)
	{
		for (j=0; j < n; j++)
		{
			if ((i==line)||(j==column))
			{
				if(sudoku[i][j].value != -1)
				{	
					if ((*head)->v == sudoku[i][j].value)
					{
						(*head) = (*head)->next;					
					}
					else{
						p = (*head);
						while(p->next)
						{
							if (p->next->v == sudoku[i][j].value)
							{				
								p->next = p->next->next;
								break;								
							}
							p=p->next;
						}
					}
				}
			}
		}
	}
	//Check Region
	regionL = (int)trunc(line/sqrt(n));
	regionC = (int)trunc(column/sqrt(n));
		
	startL = trunc(regionL*sqrt(n));
	endL = trunc(startL+sqrt(n));
	startC = trunc(regionC*sqrt(n));
	endC = trunc(startC+sqrt(n));

	for (i=startL; i < endL;i++)
	{
		for (j=startC; j < endC; j++)
		{
			if(sudoku[i][j].value != -1)
			{
				if ((*head)->v == sudoku[i][j].value)
				{
					(*head) = (*head)->next;
				}
				else{
					p = (*head);
					while(p->next)
					{
						if (p->next->v == sudoku[i][j].value)
						{
							p->next = p->next->next;	
							break;							
						}
						p=p->next;
					}
				}
			}
		}
	}
}

int EndSudoku(S** sudoku, int n)
{
	int i,j;
	for (i=0; i < n; i++)
	{
		for (j=0; j < n; j++)
		{	
			if (sudoku[i][j].value==-1)	
				return 0;							
		}
	}
	return 1;
}

char getCharValue(int v)
{
	if (v==10)
		return 'A';
	if (v==11)
		return 'B';
	if (v==12)
		return 'C';
	if (v==13)
		return 'D';
	if (v==14)
		return 'E';
	if (v==15)
		return 'F';
	if (v==0)
		return '0';
	if (v==1)
		return '1';
	if (v==2)
		return '2';
	if (v==3)
		return '3';
	if (v==4)
		return '4';
	if (v==5)
		return '5';
	if  (v==6)
		return '6';
	if (v==7)
		return '7';
	if (v==8)
		return '8';
	return '9';
}

void CalcProb(char** mat, int r, int c)
{
	int i, j;
	
	S** sudoku = malloc(sizeof(S*)*r);
	for (i = 0; i < r; i++)
	{	
		sudoku[i] = malloc(sizeof(S)*c);	
	}
	
	
	for (i=0; i < r; i++)
	{
		for (j=0; j < c; j++)
		{
			sudoku[i][j].value = getValue(mat[i][j]);			
			sudoku[i][j].head = CreateFullList(r);		
		}
	}
	while(EndSudoku(sudoku, r)==0)
	{
		//go through each line and collum removing elements from the list
		for (i=0; i < r; i++)
		{
			for (j=0; j < c; j++)
			{
				if (sudoku[i][j].value == -1)	
				{
					CheckLineandColumn(sudoku, &(sudoku[i][j].head), r, i, j);
				}
			}
		}
		//Find lists with one element and update value
		for (i=0; i < r; i++)
		{
			for (j=0; j < c; j++)
			{
				if (sudoku[i][j].value == -1)	
				{
					if (sudoku[i][j].head->next==NULL)
					{
						sudoku[i][j].value = sudoku[i][j].head->v;
					}
				}
			}
		}
	}	
	for (i=0; i < r; i++)
	{
		for (j=0; j < c; j++)
		{			
			mat[i][j] = getCharValue(sudoku[i][j].value);	
		}
	}
	for (i=0; i < r; i++)
		free(sudoku[i]);
	free(sudoku);
}

int main(){
	char** mat;
	int c, r, i;

	mat = readMat(&c, &r);
	c=16;
	r=16;
	CalcProb(mat, r, c);
	printMat(mat, c, r);
	
	for (i=0; i<r; i++)
	{
		free(mat[i]);		
	}
	free(mat);	
}
