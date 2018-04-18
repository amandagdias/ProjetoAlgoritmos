/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 27/05/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define BRANCO 0
#define PRETO 1
#define noT 0
#define isTbSame 1
#define isTbOther 2
#define isTbBoth 3
#define isEmpty 0
#define hasW 1
#define hasB 2

struct list{
	int origemL; 
	int origemC;
	int destL;
	int destC;
	int pos;
	int x;	
	char tipo;
	struct list* next;
};
typedef struct Edestiny{
	int n;
	struct list* head;
}Edestiny;
typedef struct p{
	char positions[10];
	double Smov;
	int OC;
	int OL;
}POSITIONS;
typedef struct ai{
	int T;
	int C; 
	char tipo;	
}AIMatrix;
int indexTemp = 0;
typedef struct peca{
	char coluna;
	char linha;
	int lado;
	char tipo;
	void (*function)(struct peca** tabuleiro, int origemL, int origemC, int* mov, Edestiny** matrix, POSITIONS* P, int* i, int VC, AIMatrix** AI, int lado);
}peca;

int getIntColumn(char c)
{
	if (c == 'a')
		return 0;
	if (c=='b')
		return 1;
	if (c=='c')
		return 2;
	if (c=='d')
		return 3;
	if (c=='e')
		return 4;
	if (c=='f')
		return 5;
	if (c=='g')
		return 6;
	if (c=='h')
		return 7;
	return -1;
}
char getColumn(int C)
{
	if (C == 0)
		return 'a';
	if (C==1)
		return 'b';
	if (C==2)
		return 'c';
	if (C==3)
		return 'd';
	if (C==4)
		return 'e';
	if (C==5)
		return 'f';
	if (C==6)
		return 'g';
	if (C==7)
		return 'h';
	return '0';

}
void OrdenaPositions2(POSITIONS *P, int count)
{
	POSITIONS *aux;
	aux = (POSITIONS*) malloc(sizeof(POSITIONS));
	int i, j, coluna1, linha1, coluna2, linha2;
	for(i = 0 ; i < count; i++)
	{
		if ((P[i].positions[strlen(P[i].positions)-1] != 'N')&&(P[i].positions[strlen(P[i].positions)-1] != 'B')&&
		(P[i].positions[strlen(P[i].positions)-1] != 'Q')&&(P[i].positions[strlen(P[i].positions)-1] != 'R'))
		{
			coluna1 = getIntColumn(P[i].positions[strlen(P[i].positions)-2]);
			linha1 = P[i].positions[strlen(P[i].positions)-1] - '0' - 1;
		}else{
			coluna1 = getIntColumn(P[i].positions[strlen(P[i].positions)-3]);
			linha1 = P[i].positions[strlen(P[i].positions)-2] - '0' - 1;
		}
//		if (P[i].positions[1] == 'x')
//		{
//			coluna1 = getIntColumn(P[i].positions[2]);
//			linha1 = P[i].positions[3];
//		}else{
//			coluna1 = getIntColumn(P[i].positions[1]);
//			linha1 = P[i].positions[2];
//		}		
		for (j=i; j < count; j++)
		{
			if ((P[j].positions[strlen(P[j].positions)-1] != 'N')&&(P[j].positions[strlen(P[j].positions)-1] != 'B')&&
			(P[j].positions[strlen(P[j].positions)-1] != 'Q')&&(P[j].positions[strlen(P[j].positions)-1] != 'R'))
			{
				coluna2 = getIntColumn(P[j].positions[strlen(P[j].positions)-2]);
				linha2 = P[j].positions[strlen(P[j].positions)-1] - '0' - 1;
			}else{
				coluna2 = getIntColumn(P[j].positions[strlen(P[j].positions)-3]);
				linha2 = P[j].positions[strlen(P[j].positions)-2] - '0' - 1;
			}
//			if (P[j].positions[1] == 'x')
//			{
//				coluna2 = getIntColumn(P[j].positions[2]);
//				linha2 = P[j].positions[3];
//			}else{
//				coluna2 = getIntColumn(P[j].positions[1]);
//				linha2 = P[j].positions[2];
//			}		
			if (linha2 < linha1)
			{
				
				aux->OC= P[i].OC;
				aux->OL = P[i].OL;
				strcpy(aux->positions, P[i].positions);
				aux->Smov = P[i].Smov;
				P[i] = P[j];
				P[j] = *aux;
			}			
			else{
				if ((linha2 == linha1)&&(coluna2 < coluna1))
				{
					aux->OC= P[i].OC;
					aux->OL = P[i].OL;
					strcpy(aux->positions, P[i].positions);
					aux->Smov = P[i].Smov;
					P[i] = P[j];
					P[j] = *aux;
				}
			}
		
		}
	}

}
char* OrdenaPositions(POSITIONS* P, int npos,int start, int** used, char tipo)
{
	int i, j, k;
	int linha, coluna;	
	for (j=0; j < 8; j++)
	{	
		for(i=0; i < 8; i++)
		{	
			for (k=start; k < npos; k++)
			{				
				if ((*used)[k]==0)
				{			
					if ((tipo=='p')||(tipo=='P'))
					{
						if (P[k].positions[strlen(P[k].positions)-1] == '.')
						{
							linha = P[k].positions[strlen(P[k].positions)-5] - 1 -'0';
							coluna = (int) getIntColumn(P[k].positions[strlen(P[k].positions)-6]);
						}else
						if ((P[k].positions[strlen(P[k].positions)-1] == 'N')||(P[k].positions[strlen(P[k].positions)-1] == 'B')||(P[k].positions[strlen(P[k].positions)-1] == 'R')||(P[k].positions[strlen(P[k].positions)-1] == 'Q'))
						{
							linha = P[k].positions[strlen(P[k].positions)-2] - 1 -'0';
							coluna = (int) getIntColumn(P[k].positions[strlen(P[k].positions)-3]);
						}
						else{
							linha = P[k].positions[strlen(P[k].positions)-1] - 1 -'0';
							coluna = (int) getIntColumn(P[k].positions[strlen(P[k].positions)-2]);	
						}
					}else{
						linha = P[k].positions[strlen(P[k].positions)-1] - 1 -'0';
						coluna = (int) getIntColumn(P[k].positions[strlen(P[k].positions)-2]);	
					}
					if ((coluna==j)&&(linha==i))
					{
						(*used)[k] = 1;			
						return P[k].positions;
					}
				}										
			}			
		}
	}
	return "none";
}
void AddToList(struct list **head, int origemL, int origemC, int destL, int destC, int pos, char tipo, int x)
{
	struct list *p;
	p = (struct list*) malloc(sizeof(struct list));
	p->origemC = origemC;
	p->origemL = origemL;
	p->destC = destC;
	p->destL = destL;
	p->tipo = tipo;
	p->pos = pos;
	p->x = x;
	p->next = NULL;
	
	if (*head==NULL)
	{
		*head = p;
	}
	else{
		p->next = *head;
		*head = p;		
	}
	
}
int MovimentosCheque(peca** copy, int lado, char tipo, int LRei, int CRei, AIMatrix** AI)
{
	int j, i, npos, mov, linha, coluna, k;
	Edestiny** matrix;
	POSITIONS *P;
	P = (POSITIONS*) calloc(100, sizeof(POSITIONS));
	matrix = (Edestiny**) malloc(sizeof(Edestiny*)*8);
	for (i = 0; i < 8; i++)
	{
		matrix[i] = (Edestiny*) malloc(sizeof(Edestiny)*8);
		for (j=0; j < 8; j++){
			matrix[i][j].n = 0;
			matrix[i][j].head = NULL;
		}
			
	}

	npos = 0;
	k=0;
	for (i=7; i >= 0; i--)
	{
			for (j=0; j < 8; j++)
			{	
			//	printf("%c ", copy[i][j].tipo);
				if((copy[i][j].lado == lado)&&(copy[i][j].tipo==tipo))
				{	
					mov = 0;			
					copy[i][j].function(copy, i, j, &mov, matrix, P, &npos, 0, AI, lado);							
				}			
			}
		//	printf("\n");
	}
//	printf("npos: %d\n", npos);
	for (k=0 ; k < npos; k++)
	{
		if ((P[k].positions[strlen(P[k].positions)-1] != 'N')&&(P[k].positions[strlen(P[k].positions)-1] != 'B')&&
		(P[k].positions[strlen(P[k].positions)-1] != 'Q')&&(P[k].positions[strlen(P[k].positions)-1] != 'R'))
		{
			coluna = getIntColumn(P[k].positions[strlen(P[k].positions)-2]);
			linha = P[k].positions[strlen(P[k].positions)-1] - '0' - 1;
		}else{
			coluna = getIntColumn(P[k].positions[strlen(P[k].positions)-3]);
			linha= P[k].positions[strlen(P[k].positions)-2] - '0' - 1;
		}
//		linha = P[k].positions[strlen(P[k].positions)-1] - 1 -'0';
//		coluna = (int) getIntColumn(P[k].positions[strlen(P[k].positions)-2]);
		if ((linha == LRei)&&(coluna == CRei)){		
	//		printf("cheque true %s\n", P[k].positions);			
			return 1;
		}
	}
//	printf("end movimentos cheque false\n");
	free(P);
	free(matrix);
	return 0;
}
int VerificaCheque(peca** tabuleiro, int origemL, int origemC, int destL,int destC, AIMatrix** AI)
{
	int ladoOp , lado, LRei, CRei, i, j;
	peca** copy;
	peca* aux;
	peca* pc;
	pc = (peca*) malloc(sizeof(peca));
	pc->function = tabuleiro[origemL][origemC].function;	
	pc->lado = tabuleiro[origemL][origemC].lado;
	pc->tipo = tabuleiro[origemL][origemC].tipo;
	pc->coluna = tabuleiro[origemL][origemC].coluna;
	pc->linha = tabuleiro[origemL][origemC].linha;
	lado = tabuleiro[origemL][origemC].lado;
	copy = (peca**) malloc(sizeof(peca*)*8);

	for (i = 0; i < 8; i++)
		copy[i] = (peca*) malloc(sizeof(peca)*8);	
//	printf("copia:\n");
	for (i=7; i >= 0; i--)
	{
		for (j=0; j < 8; j++)
		{
			
			if ((i==origemL)&&(j==origemC)){
				
				aux = (peca*) malloc(sizeof(peca));
				aux->tipo = '0';				
				copy[i][j] = *aux;		
			}else
			if ((i==destL)&&(j==destC))
			{			
				copy[i][j] = *pc;
			}else{				
				copy[i][j].function = tabuleiro[i][j].function;
				copy[i][j].lado = tabuleiro[i][j].lado;
				copy[i][j].tipo = tabuleiro[i][j].tipo;
				copy[i][j].coluna = tabuleiro[i][j].coluna;
				copy[i][j].linha = tabuleiro[i][j].linha;
			}
		//	printf("%c ", copy[i][j].tipo);					
		}
	//	printf("\n");
	
	}
//	printf("\n");
	for (i=0; i < 8; i++)
	{
		for (j=0; j < 8; j++)
		{
			if ((lado == BRANCO)&&(copy[i][j].tipo == 'K'))
			{
				LRei = i;
				CRei = j;
				continue;
			}else
			if ((lado == PRETO)&&(copy[i][j].tipo== 'k'))
			{
				LRei = i;
				CRei = j;
				continue;
			}
		}
	}
//	printf("LRei %d  CRei %d lado %d\n", LRei, CRei, lado);
	if (lado == BRANCO)
		ladoOp = PRETO;
	else
		ladoOp = BRANCO;

	if (ladoOp == BRANCO)
	{
		if (MovimentosCheque(copy, ladoOp, 'P', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'N', LRei, CRei, AI))	
			return 0;	
		if (MovimentosCheque(copy, ladoOp, 'B', LRei, CRei, AI))		
			return 0;			
		if (MovimentosCheque(copy, ladoOp, 'R', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'Q', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'K', LRei, CRei, AI))
			return 0;
		return 1;
	}
	else{

		if (MovimentosCheque(copy, ladoOp, 'p', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'n', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'b', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'r', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'q', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'k', LRei, CRei, AI))
			return 0;
		return 1;
	}
	
}
void AddToMatrix(Edestiny** matrix, int origemL, int origemC, int destL, int destC, int pos, char tipo, int x)
{
	
	matrix[destL][destC].n++;
	AddToList(&matrix[destL][destC].head, origemL, origemC, destL, destC, pos, tipo, x);
	
}
void AddToPositionsP(POSITIONS* P, int *i, int L, int C, int newC, int x, int promo)
{
	if (P==NULL){	
		return;	
	} 
	int j;
	char promo_list[4];
	promo_list[0] = 'N';
	promo_list[1] = 'B';
	promo_list[2] = 'R';
	promo_list[3] = 'Q';
	
	
	if (!x)
	{
		if (promo)
		{
			for (j=0; j < 4; j++)	
			{
				P[(*i)].positions[0] = getColumn(C);
				P[(*i)].positions[1] = getColumn(C);
				P[(*i)].positions[2] = (L + 1) + '0';
				P[(*i)].positions[3] = promo_list[j];
				P[(*i)].positions[4] = '\0';
				(*i)++;				
			}
		}
		else{
			P[(*i)].positions[0] = getColumn(C);
			P[(*i)].positions[1] = getColumn(C);
			P[(*i)].positions[2] = (L + 1) + '0';
			P[(*i)].positions[3] = '\0';		
			(*i)++;
		}
		
	}else{
		if (promo)
		{
			for (j=0; j < 4; j++)
			{
				P[(*i)].positions[0] = getColumn(C);
				P[(*i)].positions[1] = 'x';
				P[(*i)].positions[2] = getColumn(newC);
				P[(*i)].positions[3] = (L+1)+ '0';
				P[(*i)].positions[4] = promo_list[j];	
				P[(*i)].positions[5] = '\0';
				(*i)++;
			}
			
			
		}else{
			P[(*i)].positions[0] = getColumn(C);
			P[(*i)].positions[1] = 'x';
			P[(*i)].positions[2] = getColumn(newC);
			P[(*i)].positions[3] = (L+1)+ '0';
			P[(*i)].positions[4] = '\0';			
			(*i)++;
		}
	}

}
void AddToPositions(POSITIONS* P, int i, char tipo, int L, int C, int x)
{
	if (P==NULL){
	
		return;	
	} 
	if (!x){
		P[i].positions[0] = tipo;
		P[i].positions[1] = getColumn(C);
		P[i].positions[2] = (L + 1) + '0';
		P[i].positions[3] = '\0';
	}
	else{
		P[i].positions[0] = tipo;
		P[i].positions[1] = 'x';
		P[i].positions[2] = getColumn(C);
		P[i].positions[3] = (L + 1) + '0';
		P[i].positions[4] = '\0';	
	}
	
	
}
void AddToAIMatrix(AIMatrix** AI, int L, int C, int T, int Content, char tipo, POSITIONS* P, char caller)
{
	
	//printf("started AddToAIMatrix\n");
	if (AI)
	{	
		if (((L==7)&&(C==0))&&(T == isTbSame))
		{
			printf("caller: %c \n", caller);
		}
		if (((T==isTbOther)&&(tipo!='k'))||(T==isTbSame))
	//	if ((T==isTbOther)||(T==isTbSame))
		{
			if (P)//Means that came from Movimentos Cheque
			{	
				if (AI[L][C].T == noT)
					AI[L][C].T = T;	
				else
					if (AI[L][C].T == isTbSame)
						AI[L][C].T = isTbBoth;	
			
			//	AI[L][C].tipo = tipo;
			}	
			else{
				if (AI[L][C].T == noT)
					AI[L][C].T = T;	
				else
					if (AI[L][C].T == isTbOther)
						AI[L][C].T = isTbBoth;	
			}
		}
	
	}
	
}
double getValue(char tipo)
{

	if ((tipo =='p')||(tipo == 'P'))
		return 100.0;
	if ((tipo=='n')||(tipo == 'N')||(tipo == 'b')||(tipo == 'B'))
		return 325.0;
	if ((tipo == 'r')||(tipo == 'R'))
		return 550.0;
	if ((tipo == 'q')||(tipo=='Q'))
		return 1000.0;
	if ((tipo=='k')||(tipo == 'K'))
		return 50000.0;
	else
		return 1.0;
}
void CalcSMov(POSITIONS *P, int index, peca** tabuleiro, int origemL,int origemC,int destL,int destC, AIMatrix** AI)
{
	double SB = 0.0, SW = 0.0;
	int npos;
	int i, j, lado, mov;
	//Simulate moviments for black side
	peca** copy;
	peca* aux;
	peca* pc;
	pc = (peca*) malloc(sizeof(peca));
	pc->function = tabuleiro[origemL][origemC].function;	
	pc->lado = tabuleiro[origemL][origemC].lado;
	pc->tipo = tabuleiro[origemL][origemC].tipo;
	pc->coluna = tabuleiro[origemL][origemC].coluna;
	pc->linha = tabuleiro[origemL][origemC].linha;
	lado = PRETO;
	copy = (peca**) malloc(sizeof(peca*)*8);
	for (i = 0; i < 8; i++)
		copy[i] = (peca*) malloc(sizeof(peca)*8);	
	for (i=7; i >= 0; i--)
	{
		for (j=0; j < 8; j++)
		{		
			
			if ((i==origemL)&&(j==origemC)){
				
				aux = (peca*) malloc(sizeof(peca));
				aux->tipo = '0';								
				copy[i][j] = *aux;		
			}else
			if ((i==destL)&&(j==destC))
			{			
				copy[i][j] = *pc;
			}else{				
				copy[i][j].function = tabuleiro[i][j].function;
				copy[i][j].lado = tabuleiro[i][j].lado;
				copy[i][j].tipo = tabuleiro[i][j].tipo;
				copy[i][j].coluna = tabuleiro[i][j].coluna;
				copy[i][j].linha = tabuleiro[i][j].linha;
			}					
			if ((copy[i][j].tipo!='0')&&(copy[i][j].lado == BRANCO))
				AI[i][j].C = hasW;
			else if ((copy[i][j].tipo!='0')&&(copy[i][j].lado == PRETO))
				AI[i][j].C = hasB;
			else if (copy[i][j].tipo=='0')
				AI[i][j].C = isEmpty;							
			AI[i][j].tipo = copy[i][j].tipo;
		}
		
	
	}

	P[indexTemp].OC = origemC;
	P[indexTemp].OL = origemL;
	npos = 0;
	for (i=7; i >= 0; i--)
	{
			for (j=0; j < 8; j++)
			{	
				if((copy[i][j].tipo!='0')&&(copy[i][j].lado==lado)) //Realiza o movimento das peças pretas				
				{	
					mov = 0;
					
					copy[i][j].function(copy, i, j, &mov, NULL, NULL, &npos, 0, AI, lado);								
				}			
			}
	}
	//Read AI matriz and calculate Smov

	SB = 0.0;
	SW = 0.0;
	
	for (i=7; i >= 0; i--)
	{
			for (j=0; j < 8; j++)
			{	
		//		printf("%c ", AI[i][j].tipo);
				if ((AI[i][j].T == isTbSame)||(AI[i][j].T == isTbBoth))		
				{
		//			printf("\n%d %d\n", i, j);
					if (AI[i][j].C == isEmpty)
					{
						SB+= 50.00;		
		//				printf("+50 ");
					}									
					else if (AI[i][j].C == hasW)
					{
						SB+= (double) getValue(AI[i][j].tipo);	
		//			printf("+%lf ", getValue(AI[i][j].tipo));
					}						
					else if (AI[i][j].C == hasB)
					{
						SB+= (double) getValue(AI[i][j].tipo)/2.00;
		//				printf("+%lf/2 ", getValue(AI[i][j].tipo));
					}
						
				}
			}
	//		printf("\n");
	}
//printf("\n");
//	printf("\n");
	for (i = 7; i >=0; i--)
	{
		for (j = 0; j < 8; j++)
		{
	//		printf("%d ", AI[i][j].T);
			if ((AI[i][j].T == isTbOther)||(AI[i][j].T == isTbBoth))	
				{
		//			printf("\n%d %d\n", i, j);
					if (AI[i][j].C == isEmpty)
					{
						SW+= 50.00;
		//				printf("+50 ");
					}										
					else if (AI[i][j].C == hasB)
					{					
						SW+= (double) getValue(AI[i][j].tipo);
		//				printf("+%lf ", getValue(AI[i][j].tipo));
					}						
					else if (AI[i][j].C == hasW)
					{
						SW+= (double) getValue(AI[i][j].tipo)/2.00;
		//				printf("+%lf/2 ", getValue(AI[i][j].tipo));
						
					}
						
				}
			
		}
//		printf("\n");
	}
//	printf("\n");

//	printf("indexTemp: %d \n", indexTemp);
//	printf("%s   %lf\n", P[indexTemp].positions, SB);
	P[indexTemp].Smov = (double) SB/SW;
	
	indexTemp++;


	for (i = 0 ; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			AI[i][j].C = isEmpty;
			AI[i][j].T = noT;
			AI[i][j].tipo = '0';			
		}
	}
	for (i = 0 ; i < 8; i++)
		free(copy[i]);
	free(copy);
	
}
void D(peca** tabuleiro, int L, int C, POSITIONS *P, int* m, int* i, Edestiny** matrix, char tipo, int VC, AIMatrix** AI, int lado)
{
	int newL, newC, smov;

//	printf("from D\n");
	//Diagnoal esquerda inferior
	newL = L - 1;
	newC = C - 1;
	smov = 0;
	while  ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
	{
	
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{	
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				smov = 1;
				AddToPositions(P, (*i), tipo,  newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);			
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), tipo, newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, tipo);
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, tipo);
		
			if (P) (*i)++;
		}
		newL--;
		newC--;
	}
	if ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].tipo != '0')&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), tipo, newL, newC, 1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;		
			}
		}else{
			AddToPositions(P, (*i), tipo, newL, newC, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, tipo);				
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, tipo);							
			if (P) (*i)++;		
			
		}
	}else if ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].tipo != '0')&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado)&&(!smov))
	{
		if (lado == BRANCO)
			AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, tipo);	
		else
			AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, tipo);					
	}
//	}
	//Diagonal esquerda superior
	newL = L + 1;
	newC = C - 1;
	smov = 0;
	while  ((newC>=0)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
	{		
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				smov = 1;
				AddToPositions(P, (*i), tipo, newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);		
				(*i)++;
			}	
		}else{
			AddToPositions(P, (*i), tipo, newL, newC, 0);			
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, tipo);
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, tipo);	
			if (P) (*i)++;
		}
		newC--;
		newL++;
	}
	if ((newC>=0)&&(newL < 8)&&(tabuleiro[newL][newC].tipo != '0')&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), tipo, newL, newC, 1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				if (P) (*i)++;		
			}
		}else{
			AddToPositions(P, (*i), tipo, newL, newC, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, tipo);				
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, tipo);		
			if (P) (*i)++;		
		}						
	}else if ((newC>=0)&&(newL < 8)&&(tabuleiro[newL][newC].tipo != '0')&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado)&&(!smov))
	{	
		if (lado == BRANCO)
			AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, tipo);		
		else
			AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, tipo);					
	}	
	//Diagonal direita inferior
	newL = L - 1;
	newC = C + 1;
	smov = 0;
	while  ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				smov = 1;
				AddToPositions(P, (*i), tipo, newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);			
				if (P) (*i)++;
			}	
		}else{
			AddToPositions(P, (*i),tipo, newL, newC, 0);			
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, tipo);
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, tipo);		
			if (P) (*i)++;
		}
		newC++;
		newL--;
	}
	if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].tipo != '0')&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), tipo, newL, newC, 1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				if (P) (*i)++;		
			}
		}else{
			AddToPositions(P, (*i), tipo, newL, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, tipo);					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, tipo);		
			if (P) (*i)++;		
		}
	}else if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].tipo != '0')&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado)&&(!smov))
	{
		if (lado == BRANCO)
			AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, tipo);	
		else
			AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, tipo);				
	}
	//Diagonal direita superior
	newL = L + 1;
	newC = C + 1;
	smov = 0;
	while  ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				smov = 1;
				AddToPositions(P, (*i), tipo, newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);			
				if (P) (*i)++;
			}	
		}else{
			AddToPositions(P, (*i), tipo, newL, newC, 0);			
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, tipo);
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, tipo);	
			if (P) (*i)++;
		}
		newC++;
		newL++;
	}
	if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), tipo, newL, newC, 1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				if (P) (*i)++;		
			}
		}else{
			AddToPositions(P, (*i), tipo, newL, newC, 1);		
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, tipo);					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, tipo);	
			if (P) (*i)++;		
		}
	}else if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado)&&(!smov))
	{
		if (lado == BRANCO)
			AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, tipo);		
		else
			AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, tipo);					
	}		
	*m = *i;
}
void CBDE(peca** tabuleiro, int L, int C, POSITIONS* P, int* m, int* i, Edestiny** matrix, char tipo, int VC, AIMatrix** AI, int lado)
{
//	printf("from CBDE\n");
	int newL, newC, smov;
	//Para esquerda
	newC = C - 1;
	smov = 0;
	while  ((newC>=0)&&(tabuleiro[L][newC].tipo == '0'))
	{
	
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);
				smov = 1;
				AddToPositions(P, (*i), tipo, L, newC, 0);				
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);				
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), tipo, L, newC, 0);			
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, isEmpty, tabuleiro[L][newC].tipo, P, tipo);
			else
				AddToAIMatrix(AI, L, newC, isTbSame, isEmpty, tabuleiro[L][newC].tipo, P, tipo);			
			if (P) (*i)++;
		}	
		newC--;		
	}
	if ((newC>=0)&&(tabuleiro[L][newC].tipo != '0')&&(tabuleiro[L][newC].lado == tabuleiro[L][C].lado)&&(!smov))
	{	
//		printf("equal sides\n");
		if (lado == BRANCO)
			AddToAIMatrix(AI, L, newC, isTbOther, hasW, tabuleiro[L][newC].tipo, P, tipo);		
		else
			AddToAIMatrix(AI, L, newC, isTbSame, hasB, tabuleiro[L][newC].tipo, P, tipo);	
//		if (VC)
//			CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);					
	}else		
	if ((newC>=0)&&(tabuleiro[L][newC].tipo != '0')&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);
				AddToPositions(P, (*i), tipo, L, newC, 1);									
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 1);
				if (P) (*i)++;		
			}
		}
		else{					
			AddToPositions(P, (*i), tipo, L, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, hasB, tabuleiro[L][newC].tipo, P, tipo);					
			else
				AddToAIMatrix(AI, L, newC, isTbSame, hasW, tabuleiro[L][newC].tipo, P, tipo);				
			if (P) (*i)++;	
		}					
	}

//	}
	//Para baixo
	newL = L - 1;
	smov = 0;
	while  ((newL>=0)&&(tabuleiro[newL][C].tipo == '0'))
	{
		
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);
				smov = 1;
				AddToPositions(P, (*i), tipo, newL, C, 0);
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);				
				if (P) (*i)++;			
			}
		}else{
			AddToPositions(P, (*i), tipo, newL, C, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, isEmpty, tabuleiro[newL][C].tipo, P, tipo);
			else
				AddToAIMatrix(AI, newL, C, isTbSame, isEmpty, tabuleiro[newL][C].tipo, P, tipo);			
			if (P) (*i)++;	
		}
		newL--;		
	}
	if ((newL>=0)&&(tabuleiro[newL][C].tipo != '0')&&(tabuleiro[newL][C].lado == tabuleiro[L][C].lado)&&(!smov))
	{
		if (lado == BRANCO)
			AddToAIMatrix(AI, newL, C, isTbOther, hasW, tabuleiro[newL][C].tipo, P, tipo);		
		else
			AddToAIMatrix(AI, newL, C, isTbSame, hasB, tabuleiro[newL][C].tipo, P, tipo);					
	}else
	if ((newL>=0)&&(tabuleiro[newL][C].tipo != '0')&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);
				AddToPositions(P, (*i), tipo, newL, C, 1);
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 1);
				if (P) (*i)++;	
			}
		}
		else{
			AddToPositions(P, (*i), tipo, newL, C, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, hasB, tabuleiro[newL][C].tipo, P, tipo);				
			else
				AddToAIMatrix(AI, newL, C, isTbSame, hasW, tabuleiro[newL][C].tipo, P, tipo);
			if (P) (*i)++;	
		}					
	}
	//Para cima
	newL = L+1;	
	smov = 0;
	while  ((newL<8)&&(tabuleiro[newL][C].tipo == '0'))
	{	
	
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);
				smov = 1;
				AddToPositions(P, (*i), tipo,  newL, C, 0);				
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);				
				if (P) (*i)++;
			}	
		}
		else{
			AddToPositions(P, (*i), tipo, newL, C, 0);				
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, isEmpty, tabuleiro[newL][C].tipo, P, tipo);
			else
				AddToAIMatrix(AI, newL, C, isTbSame, isEmpty, tabuleiro[newL][C].tipo, P, tipo);					
			if (P) (*i)++;
		}
		newL++;		
	}
	if ((newL<8)&&(tabuleiro[newL][C].tipo != '0')&&(tabuleiro[newL][C].lado == tabuleiro[L][C].lado)&&(!smov))
	{
		if (lado == BRANCO)
			AddToAIMatrix(AI, newL, C, isTbOther, hasW, tabuleiro[newL][C].tipo, P, tipo);		
		else
			AddToAIMatrix(AI, newL, C, isTbSame, hasB, tabuleiro[newL][C].tipo, P, tipo);					
	}else	
	if ((newL<8)&&(tabuleiro[newL][C].tipo != '0')&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);
				AddToPositions(P, (*i), tipo, newL, C, 1);
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 1);
				if (P) (*i)++;	
			}
		}
		else{
			AddToPositions(P, (*i), tipo, newL, C, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, hasB, tabuleiro[newL][C].tipo, P, tipo);					
			else
				AddToAIMatrix(AI, newL, C, isTbSame, hasW, tabuleiro[newL][C].tipo, P, tipo);
			if (P) (*i)++;	
		}					
	}	

	//Para direita
	newC = C + 1;
		smov = 0;
	while  ((newC<8)&&(tabuleiro[L][newC].tipo == '0'))
	{
	
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);
				smov = 1;
				AddToPositions(P, (*i), tipo, L, newC, 0);				
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);				
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), tipo, L, newC, 0);				
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, isEmpty, tabuleiro[L][newC].tipo, P, tipo);
			else
				AddToAIMatrix(AI, L, newC, isTbSame, isEmpty, tabuleiro[L][newC].tipo, P, tipo);						
			if (P) (*i)++;
		}
		newC++;
	}
	if ((newC<8)&&(tabuleiro[L][newC].tipo != '0')&&(tabuleiro[L][newC].lado == tabuleiro[L][C].lado)&&(!smov))
	{
		if (lado == BRANCO)
			AddToAIMatrix(AI, L, newC, isTbOther, hasW, tabuleiro[L][newC].tipo, P, tipo);		
		else
			AddToAIMatrix(AI, L, newC, isTbSame, hasB, tabuleiro[L][newC].tipo, P, tipo);					
	}else
	if ((newC<8)&&(tabuleiro[L][newC].tipo != '0')&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);
				AddToPositions(P, (*i), tipo, L, newC, 1);									
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 1);
				if (P) (*i)++;		
			}
		}
		else{
			AddToPositions(P, (*i), tipo, L, newC, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, hasB, tabuleiro[L][newC].tipo, P, tipo);					
			else
				AddToAIMatrix(AI, L, newC, isTbSame, hasW, tabuleiro[L][newC].tipo, P, tipo);	
			if (P) (*i)++;	
		}					
	} 
	*m =*i;
}
void CheckMatrix(POSITIONS *P, Edestiny** matrix)
{
	int i, j;
	struct list *p;
	if (matrix == NULL)
		return;
	for (i=0; i < 8; i++)
	{
		for (j=0;j<8; j++)
		{				
			if (matrix[i][j].n > 1)
			{
				p = matrix[i][j].head;
				
				if(p!=NULL)
				{
					
					if (!p->x){	
					//	P->positions[p->pos] = (char*)malloc(sizeof(char*)*10);					
						if (p->origemC != p->next->origemC)
						{
							P[p->pos].positions[0] = p->tipo;
							P[p->pos].positions[1] = getColumn(p->origemC);
							P[p->pos].positions[2] = getColumn(p->destC);
							P[p->pos].positions[3] = p->destL + 1 +'0';
							P[p->pos].positions[4] = '\0';
							
							P[p->next->pos].positions[0] = p->next->tipo;
							P[p->next->pos].positions[1] = getColumn(p->next->origemC);
							P[p->next->pos].positions[2] = getColumn(p->next->destC);
							P[p->next->pos].positions[3] = p->next->destL + 1 +'0';
							P[p->next->pos].positions[4] = '\0';				
						}						
						else if (p->origemL != p->next->origemL){
							P[p->pos].positions[0] = p->tipo;
							P[p->pos].positions[1] = p->origemL + 1 +'0';
							P[p->pos].positions[2] = getColumn(p->destC);
							P[p->pos].positions[3] = p->destL + 1 + '0';
							P[p->pos].positions[4] = '\0';
							
							P[p->next->pos].positions[0] = p->next->tipo;
							P[p->next->pos].positions[1] = p->next->origemL + 1 + '0';
							P[p->next->pos].positions[2] = getColumn(p->next->destC);
							P[p->next->pos].positions[3] = p->next->destL + 1 +'0';
							P[p->next->pos].positions[4] = '\0';
						}else{
							P[p->pos].positions[0] = p->tipo;
							P[p->pos].positions[1] = getColumn(p->origemC);
							P[p->pos].positions[2] = p->origemL + 1 + '0';
							P[p->pos].positions[3] = getColumn(p->destC);
							P[p->pos].positions[4] = p->destL+ 1 + '0';
							P[p->pos].positions[5] = '\0';
							
							P[p->next->pos].positions[0] = p->next->tipo;
							P[p->next->pos].positions[1] = getColumn(p->next->origemC);
							P[p->next->pos].positions[2] = p->next->origemL + 1 + '0';
							P[p->next->pos].positions[3] = getColumn(p->next->destC);
							P[p->next->pos].positions[4] = p->next->destL+ 1 + '0';
							P[p->next->pos].positions[5] = '\0';
						}						
					}
					else{
						if (p->origemC != p->next->origemC)
						{
							P[p->pos].positions[0] = p->tipo;
							P[p->pos].positions[1] = getColumn(p->origemC);
							P[p->pos].positions[2] = 'x';
							P[p->pos].positions[3] = getColumn(p->destC);
							P[p->pos].positions[4] = p->destL+ 1 + '0';
							P[p->pos].positions[5] = '\0';
							
							P[p->next->pos].positions[0] = p->next->tipo;
							P[p->next->pos].positions[1] = getColumn(p->next->origemC);
							P[p->next->pos].positions[2] = 'x';
							P[p->next->pos].positions[3] = getColumn(p->next->destC);
							P[p->next->pos].positions[4] = p->next->destL+ 1 + '0';
							P[p->next->pos].positions[5] = '\0';
						}						
						else if (p->origemL != p->next->origemL){
							P[p->pos].positions[0] = p->tipo;
							P[p->pos].positions[1] = p->origemL+ 1 + '0';
							P[p->pos].positions[2] = 'x';
							P[p->pos].positions[3] = getColumn(p->destC);
							P[p->pos].positions[4] = p->destL+ 1 + '0';
							P[p->pos].positions[5] = '\0';
							
							P[p->next->pos].positions[0] = p->next->tipo;
							P[p->next->pos].positions[1] = p->next->origemL+ 1 + '0';
							P[p->next->pos].positions[2] = 'x';
							P[p->next->pos].positions[3] = getColumn(p->next->destC);
							P[p->next->pos].positions[4] = p->next->destL+ 1 + '0';
							P[p->next->pos].positions[5] = '\0';
						}else{
							P[p->pos].positions[0] = p->tipo;
							P[p->pos].positions[1] = getColumn(p->origemC);
							P[p->pos].positions[2] = p->origemL+ 1 + '0';
							P[p->pos].positions[3] = 'x';
							P[p->pos].positions[4] = getColumn(p->destC);
							P[p->pos].positions[5] = p->destL+ 1 + '0';
							P[p->pos].positions[6] = '\0';
							
							P[p->next->pos].positions[0] = p->next->tipo;
							P[p->next->pos].positions[1] = getColumn(p->next->origemC);
							P[p->next->pos].positions[2] = p->next->origemL+ 1 + '0';
							P[p->next->pos].positions[3] = 'x';
							P[p->next->pos].positions[4] = getColumn(p->next->destC);
							P[p->next->pos].positions[5] = p->next->destL+ 1 + '0';
							P[p->next->pos].positions[6] = '\0';
						}	
					}
					
				}
			}
		}
	}
}


void Torre(peca** tabuleiro, int L, int C, int* mov, Edestiny** matrix, POSITIONS *P, int* i, int VC, AIMatrix** AI, int lado)
{
	int m;	

	*mov = 0;

	CBDE(tabuleiro, L, C, P, &m, i, matrix, 'R', VC, AI, lado);
	*mov += m;
	if((VC)&&(P))
		CheckMatrix(P, matrix);
}
void Bispo (peca** tabuleiro, int L, int C, int* mov, Edestiny** matrix, POSITIONS *P, int* i, int VC, AIMatrix** AI, int lado)
{
	
	int  m;

	*mov = 0;

	D(tabuleiro, L, C, P, &m, i, matrix, 'B', VC, AI, lado);

	*mov += m ;
	if((VC)&&(P))
		CheckMatrix(P, matrix);
}
void Cavalo(peca** tabuleiro, int L, int C, int* mov, Edestiny** matrix, POSITIONS *P, int* i, int VC, AIMatrix** AI, int lado)
{
	int newL, newC;
	//Duas para a esquerda uma para baixo
	newL = L - 1;
	newC = C - 2;

	if((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].tipo=='0'))
	{		
		if(VC)
		{			
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
				if (P) (*i)++;
			}
		}else{		
			
			AddToPositions(P, (*i), 'N', newL, newC, 0);			
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			if (P) (*i)++;
		}
	}else 
		if ((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
		{	
			if(VC)
			{
				if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
				{
					CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
					AddToPositions(P, (*i), 'N', newL, newC,1);			
					AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
					if (P) (*i)++;
				}
			}else{		
				AddToPositions(P, (*i), 'N', newL, newC, 1);		
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
				else
					AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'N');	
				if (P) (*i)++;
			}
		}else if ((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
		}	
//	}
	//Duas para a esquerda uma para cima
	newL = L + 1;
	newC = C - 2;
	if((newL < 8)&&(newC >= 0)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
				if (P) (*i)++;
			}
		}else{			
			AddToPositions(P, (*i), 'N', newL, newC, 0);
			
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			if (P) (*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				if (P) (*i)++;
			}
		}else{		
			AddToPositions(P, (*i), 'N', newL, newC, 1);		
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'N');				
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'N');	
			if (P) (*i)++;
		}
	}else if ((newL < 8)&&(newC >= 0)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
		}	

	//Duas para baixo uma para esquerda
	newL = L-2;
	newC = C - 1;
	if((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N',0);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'N', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			if (P) (*i)++;
		}
	
	}else
	if ((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				if (P) (*i)++;
			}
		}else{		
			AddToPositions(P, (*i), 'N', newL, newC, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'N');				
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'N');			
			if (P) (*i)++;
		}
	}else if ((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
		}	
	//Duas para cima uma para esquerda
	newL = L + 2;
	newC = C - 1;
	if((newL < 8)&&(newC >=0)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				if (P) (*i)++;
			}
		}else{
				
				AddToPositions(P, (*i), 'N', newL, newC, 0);				
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
				else
					AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
				if (P) (*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC >=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				if (P) (*i)++;
			}
		}else{		
			AddToPositions(P, (*i), 'N', newL, newC, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			if (P) (*i)++;
		}
	}else if ((newL < 8)&&(newC >=0)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
		}	
	//Duas para baixo uma para direita
	newL = L-2;
	newC = C + 1;	
	if((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i),'N',0);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'N', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			if (P) (*i)++;
		}		
	}else
	if ((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				if (P) (*i)++;
			}
		}else{		
			AddToPositions(P, (*i), 'N', newL, newC, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			if (P) (*i)++;
		}
	}else if ((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
		}	
	//Duas para cima uma para direita
	newL = L+2;
	newC = C+1;
	if((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'N', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			if (P) (*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{	
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);			
				AddToPositions(P, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				if (P) (*i)++;
			}
		}else{		
			AddToPositions(P, (*i), 'N', newL, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'N');				
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'N');			
			if (P) (*i)++;
		}
	}else if ((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
		}	
//	}
	//Duas para a direita uma para baixo
	newL = L - 1;
	newC = C + 2;
	if((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				if (P) (*i)++;
			}
		}
		else{
			AddToPositions(P, (*i), 'N', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			if (P) (*i)++;
		}
	}else
	if ((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				if (P) (*i)++;
			}
		}else{		
			AddToPositions(P, (*i), 'N', newL, newC, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			if (P) (*i)++;
		}
	}else if ((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'N');	
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
		}	
	//Duas para a direita uma para cima
	newL = L + 1;
	newC = C + 2;
	if((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				if (P) (*i)++;		
			}
		}else{
			AddToPositions(P, (*i), 'N', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'N');
			if (P) (*i)++;	
		}		
	}else
	if ((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				if (P) (*i)++;
			}
		}else{		
			AddToPositions(P, (*i), 'N', newL, newC, 1);	
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'N');				
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			if (P) (*i)++;
		}
	}else if ((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'N');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'N');					
		}	
	*mov = (*i);
	
	if (VC)
		CheckMatrix(P, matrix);

}
void Rainha(peca** tabuleiro,int L, int C, int* mov, Edestiny** matrix, POSITIONS *P, int* i, int VC, AIMatrix** AI, int lado)
{
	
	int m=0;	
	*mov = 0;
	CBDE(tabuleiro, L, C, P, &m, i, matrix, 'Q', VC, AI, lado);
	*mov+=m;
	m=0;
	D(tabuleiro, L, C, P, &m, i, matrix, 'Q', VC, AI, lado);
	
	*mov+=m;
	if ((VC)&&(P))
		CheckMatrix(P, matrix);
}
void Rei(peca** tabuleiro,int L, int C, int* mov, Edestiny** matrix, POSITIONS *P, int* i, int VC, AIMatrix** AI, int lado)
{

	int newL, newC;
	//Diagnoal esquerda inferior
	newL = L - 1;
	newC = C - 1;
	if((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI)){	
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);		
				AddToPositions(P, (*i), 'K', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'K');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'K');
			if (P) (*i)++;
		}		
	}else
	if ((newC>=0)&&(newL>=0)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI)){	
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);		
				AddToPositions(P, (*i), 'K', newL, newC, 1);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'K');					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'K');	
			if (P) (*i)++;
		}	
	}else if ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'K');	
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'K');					
		}	
	//Para esquerda
	newC = C - 1;
	if ((newC>=0)&&(tabuleiro[L][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);
				AddToPositions(P, (*i), 'K', L, newC, 0);
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', L, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, isEmpty, tabuleiro[L][newC].tipo, P, 'K');
			else
				AddToAIMatrix(AI, L, newC, isTbSame, isEmpty, tabuleiro[L][newC].tipo, P, 'K');
			if (P) (*i)++;
		}
		
	}else
	if ((newC>=0)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC, AI)){		
				CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);	
				AddToPositions(P, (*i), 'K', L, newC, 1);
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 1);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', L, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, hasB, tabuleiro[L][newC].tipo, P, 'K');					
			else
				AddToAIMatrix(AI, L, newC, isTbSame, hasW, tabuleiro[L][newC].tipo, P, 'K');	
			if (P)	(*i)++;
		}		
	}
	else if ((newC>=0)&&(tabuleiro[L][newC].lado == tabuleiro[L][C].lado))	
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, hasW, tabuleiro[L][newC].tipo, P, 'K');		
			else
				AddToAIMatrix(AI, L, newC, isTbSame, hasB, tabuleiro[L][newC].tipo, P, 'K');					
		}	
	//Diagonal esquerda superior
	newL = L + 1;
	newC = C - 1;
	if((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'K', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				if (P) (*i)++;
			}
		}
		else{
			AddToPositions(P, (*i), 'K', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'K');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'K');
			if (P) (*i)++;
		}
	}else
	if ((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))			
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI)){
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);			
				AddToPositions(P, (*i), 'K', newL, newC, 1);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'K');					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'K');	
			if (P) (*i)++;
		}	
	}else if ((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'K');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'K');					
		}	

	//Para baixo
	newL = L - 1;
	if ((newL>=0)&&(tabuleiro[newL][C].tipo == '0'))
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);
				AddToPositions(P, (*i), 'K', newL, C, 0);
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);			
				if (P) (*i)++;
			}
		}
		else{
				AddToPositions(P, (*i), 'K', newL, C, 0);
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, C, isTbOther, isEmpty, tabuleiro[newL][C].tipo, P, 'K');
				else
					AddToAIMatrix(AI, newL, C, isTbSame, isEmpty, tabuleiro[newL][C].tipo, P, 'K');			
				if (P) (*i)++;
		}
	}else
	if ((newL>=0)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C, AI)){		
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);	
				AddToPositions(P, (*i), 'K', newL, C, 1);
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 1);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, C, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, hasB, tabuleiro[newL][C].tipo, P, 'K');					
			else
				AddToAIMatrix(AI, newL, C, isTbSame, hasW, tabuleiro[newL][C].tipo, P, 'K');	
			if (P) (*i)++;
		}	
	}else if ((newL>=0)&&(tabuleiro[newL][C].lado == tabuleiro[L][C].lado))	
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, hasW, tabuleiro[newL][C].tipo, P, 'K');		
			else
				AddToAIMatrix(AI, newL, C, isTbSame, hasB, tabuleiro[newL][C].tipo, P, 'K');					
		}	
	//Para cima
	newL = L+1;	
	if((newL<8)&&(tabuleiro[newL][C].tipo == '0'))
	{
		if(VC){
			if (VerificaCheque(tabuleiro, L, C, newL, C, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);
				AddToPositions(P, (*i), 'K', newL, C, 0);
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, C, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, isEmpty, tabuleiro[newL][C].tipo, P, 'K');
			else
				AddToAIMatrix(AI, newL, C, isTbSame, isEmpty, tabuleiro[newL][C].tipo, P, 'K');
			if (P) (*i)++;
		}
		
	}else
	if ((newL<8)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C, AI)){	
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);		
				AddToPositions(P, (*i), 'K', newL, C, 1);
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 1);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, C, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, hasB, tabuleiro[newL][C].tipo, P, 'K');					
			else
				AddToAIMatrix(AI, newL, C, isTbSame, hasW, tabuleiro[newL][C].tipo, P, 'K');	
			if (P) (*i)++;
		}	
	}else if  ((newL<8)&&(tabuleiro[newL][C].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, C, isTbOther, hasW, tabuleiro[newL][C].tipo, P, 'K');		
			else
				AddToAIMatrix(AI, newL, C, isTbSame, hasB, tabuleiro[newL][C].tipo, P, 'K');					
		}	

	//Diagonal direita inferior
	newL = L - 1;
	newC = C + 1;
	if((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'K', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'K');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'K');
			if (P) (*i)++;
		}		
	}else
	if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI)){
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);			
				AddToPositions(P, (*i), 'K', newL, newC, 1);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'K');					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'K');	
			if (P) (*i)++;
		}	
	}else if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))	
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'K');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'K');					
		}	

	//Para direita
	newC = C + 1;
	if ((newC<8)&&(tabuleiro[L][newC].tipo == '0'))
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);
				AddToPositions(P, (*i), 'K', L, newC, 0);
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', L, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, isEmpty, tabuleiro[L][newC].tipo, P, 'K');
			else
				AddToAIMatrix(AI, L, newC, isTbSame, isEmpty, tabuleiro[L][newC].tipo, P, 'K');
			if (P) (*i)++;
		}
	
	}else
	if ((newC<8)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC, AI)){			
				CalcSMov(P, (*i), tabuleiro, L, C, L, newC, AI);
				AddToPositions(P, (*i), 'K', L, newC, 1);
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 1);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', L, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, hasB, tabuleiro[L][newC].tipo, P, 'K');					
			else
				AddToAIMatrix(AI, L, newC, isTbSame, hasW, tabuleiro[L][newC].tipo, P, 'K');	
			if (P) (*i)++;
		}	
	}else if ((newC<8)&&(tabuleiro[L][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, L, newC, isTbOther, hasW, tabuleiro[L][newC].tipo, P, 'K');		
			else
				AddToAIMatrix(AI, L, newC, isTbSame, hasB, tabuleiro[L][newC].tipo, P, 'K');					
		}	

	//Diagonal direita superior
	newL = L + 1;
	newC = C + 1;
	if((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI))
			{
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);
				AddToPositions(P, (*i), 'K', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);		
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, newC, 0);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'K');
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'K');
			if (P) (*i)++;
		}
	
	}else
	if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC, AI)){
				CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);			
				AddToPositions(P, (*i), 'K', newL, newC, 1);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				if (P) (*i)++;
			}
		}else{
			AddToPositions(P, (*i), 'K', newL, newC, 1);
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'K');					
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'K');	
			if (P) (*i)++;
		}	
	}else if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado))
		{
			if (lado == BRANCO)
				AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'K');		
			else
				AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'K');					
		}	
	*mov = (*i);
	if (VC)
		CheckMatrix(P, matrix);
}
void Peao(peca** tabuleiro,int L, int C, int* mov, Edestiny** matrix, POSITIONS *P, int* i, int VC, AIMatrix** AI, int lado)
{	
	int newL, newC;
	if (tabuleiro[L][C].lado == BRANCO)
		newL = L+1; 
	else
		newL = L-1;
	
	if ((tabuleiro[newL][C].tipo=='0')&&((newL>=0)&&(newL < 8)))	
	{
		if (VC)
		{			
			if(VerificaCheque(tabuleiro, L, C, newL, C, AI))
			{				
				CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);	
				if (((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO)))//Promocao do Peao
				{					
					AddToPositionsP(P, i, newL, C,  C, 0, 1);				
				}else {				
					AddToPositionsP(P, i, newL, C,  C, 0, 0);										
				}			
			}	
			newL = L+2;	
			if((L==1)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==BRANCO)){
						
				if(VerificaCheque(tabuleiro, L, C, newL, C, AI))
				{	
					CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);						
					AddToPositionsP(P, i, newL, C,  C, 0, 0);
				}
			}
			newL = L-2;
			if ((L==6)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==PRETO))
			{
				if(VerificaCheque(tabuleiro, L, C, newL, C, AI))
				{
					CalcSMov(P, (*i), tabuleiro, L, C, newL, C, AI);		
					AddToPositionsP(P, i, newL, C,  C, 0, 0);				
				}
			}
		}		
		else{
			if (((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO)))//Promocao do Peao
			{
				AddToPositionsP(P, i, newL, C,  C, 0, 1);			
			}else{
				AddToPositionsP(P, i, newL, C,  C, 0, 0);
			}
			
			newL = L+2;	
			if((L==1)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==BRANCO)){						
				AddToPositionsP(P, i, newL, C,  C, 0, 0);
			
			}
			newL = L-2;
			if ((L==6)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==PRETO))
			{						
				AddToPositionsP(P, i, newL, C,  C, 0, 0);
				
			}
		}
		
	}
	//Movimentos Diagonais
	//Diagonal Esquerda
//	printf("comecando a funcao:\n");
		if (tabuleiro[L][C].lado == BRANCO)
		{
			newL = L + 1;
			newC = C - 1;
		}else{
			newL = L - 1;
			newC = C - 1;
		}
		if(VC)
		{
			if ((tabuleiro[newL][newC].tipo!='0')&&(VerificaCheque(tabuleiro, L, C, newL, newC, AI)))
			{		
			//	CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);				
				if ((newL<8)&&(newC >= 0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
				{
					if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){
							CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);							
							AddToPositionsP(P, i, newL, C,  newC, 1, 1);
					}else{			
							CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);			
							AddToPositionsP(P, i, newL, C,  newC, 1, 0);
						}
				}
			}
		}else{
			if ((newL<8)&&(newC >= 0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
			{
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'P');					
				else
					AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'P');	
				if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){						
						AddToPositionsP(P, i, newL, C,  newC, 1, 1);			
				}else{						
						AddToPositionsP(P, i, newL, C,  newC, 1, 0);
					}
			}else if ((newL<8)&&(newC >= 0)&&(newL>=0)&&(tabuleiro[(newL)][newC].tipo=='0'))
			{
			
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'P');					
				else
					AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'P');	
			
			}else if ((newL<8)&&(newC >= 0)&&(newL>=0)&&(tabuleiro[(newL)][newC].tipo!='0')&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado)){
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'P');					
				else
					AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'P');	
			}
		}	
		//Diagonal Direita
		if (tabuleiro[L][C].lado == BRANCO)
		{
			newL = L + 1;
			newC = C + 1;
		}else{
			newL = L - 1;
			newC = C + 1;
		}
		if(VC)
		{
			if ((tabuleiro[newL][newC].tipo!='0')&&(VerificaCheque(tabuleiro, L, C, newL, newC, AI)))
			{
			//	CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);			
				if ((newL<8)&&(newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
				{
					if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){	
							CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);								
							AddToPositionsP(P, i, newL, C,  newC, 1, 1);
					}else{	
							CalcSMov(P, (*i), tabuleiro, L, C, newL, newC, AI);								
							AddToPositionsP(P, i, newL, C,  newC, 1, 0);
						}
				}
			}
		}else{
			if ((newL<8)&&(newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
			{
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, newC, isTbOther, hasB, tabuleiro[newL][newC].tipo, P, 'P');					
				else
					AddToAIMatrix(AI, newL, newC, isTbSame, hasW, tabuleiro[newL][newC].tipo, P, 'P');	
				if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){						
						AddToPositionsP(P, i, newL, C,  newC, 1, 1);			
				}else{						
						AddToPositionsP(P, i, newL, C,  newC, 1, 0);
					}
			}else if ((newL<8)&&(newC < 8)&&(newL>=0)&&(tabuleiro[(newL)][newC].tipo=='0'))
			{
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, newC, isTbOther, isEmpty, tabuleiro[newL][newC].tipo, P, 'P');					
				else
					AddToAIMatrix(AI, newL, newC, isTbSame, isEmpty, tabuleiro[newL][newC].tipo, P, 'P');	
			}else if ((newL<8)&&(newC < 8)&&(newL>=0)&&(tabuleiro[(newL)][newC].tipo!='0')&&(tabuleiro[newL][newC].lado == tabuleiro[L][C].lado)){
				if (lado == BRANCO)
					AddToAIMatrix(AI, newL, newC, isTbOther, hasW, tabuleiro[newL][newC].tipo, P, 'P');					
				else
					AddToAIMatrix(AI, newL, newC, isTbSame, hasB, tabuleiro[newL][newC].tipo, P, 'P');	
			}
		}	
	if ((tabuleiro[L][C].coluna != '-')&&(P))
	{
		P[(*i)].positions[0] = getColumn(C);
		P[(*i)].positions[1] = 'x';
		P[(*i)].positions[2] = tabuleiro[L][C].coluna;
		P[(*i)].positions[3] = tabuleiro[L][C].linha;
		P[(*i)].positions[4] = 'e';
		P[(*i)].positions[5] = '.';
		P[(*i)].positions[6] = 'p';
		P[(*i)].positions[7] = '.';
		P[(*i)].positions[8] = '\0';	
		
		(*i)++;
	}
	*mov = (*i);
	
	if ((VC)&&(P)&&(matrix))
		CheckMatrix(P, matrix);
//	printf("fim funcao\n");
}


//typedef struct p peca;
//Para cada caractere, salvar na matriz 8x8 a struct correspondente a cada peça.
//Para espaços em branco, a struct é NULL
//Salvar quem joga
void PreencherTabuleiro(peca** tabuleiro, char* s)
{
	peca *pc;
	int i, j, k, n;
	char coluna, linha;
	i = 7;
	j=0;
	k= 0;
	int isNumber = 0;
	int ElPassante;
	
	while (s[k]!=' ')
		k++;
	k++; //position of side
	k++; //space after
	k++; //Roque movement
	while(s[k]!=' ')
		k++;
	k++; //space

	if (s[k]=='-')
		ElPassante = 0;
	else{
		ElPassante = 1;
		while(s[k]!=' ')
		{
			coluna = s[k];
			k++;
			linha = s[k];
			k++;
		//	printf("peao: %c\n", s[k]);		
		}
	}
		
	k = 0;
	while (i >=0)
	{
		while((s[k] != '/')&&(j < 8))
		{
			pc = (peca*) malloc (sizeof(peca));	
			
			if (s[k]=='r')
			{
				pc->tipo = 'r';
				pc->lado = PRETO;
				pc->function = &Torre;
			}
			else if (s[k]=='R')
			{
				pc->tipo = 'R';
				pc->lado = BRANCO;
				pc->function = &Torre;
			}
			else if (s[k]=='n')
			{
				pc->tipo = 'n';
				pc->lado = PRETO;
				pc->function = &Cavalo;
			}
			else if (s[k]=='N')
			{
				pc->tipo = 'N';
				pc->lado = BRANCO;
				pc->function = &Cavalo;
			}
			else if (s[k]=='b')
			{
				pc->tipo = 'b';
				pc->lado = PRETO;
				pc->function = &Bispo;
			}
			else if (s[k]=='B')
			{
				pc->tipo = 'B';
				pc->lado = BRANCO;
				pc->function = &Bispo;
			}
			else if(s[k]=='q')
			{
				pc->tipo = 'q';
				pc->lado = PRETO;
				pc->function = &Rainha;
			}
			else if (s[k]=='Q')
			{
				pc->tipo = 'Q';
				pc->lado = BRANCO;
				pc->function = &Rainha;
			}
			else if(s[k]=='k')
			{
				pc->tipo = 'k';
				pc->lado = PRETO;
				pc->function = &Rei;
			}
			else if (s[k]=='K')
			{
				pc->tipo = 'K';
				pc->lado = BRANCO;
				pc->function = &Rei;
			}
			else if (s[k]=='p')
			{
				pc->tipo = 'p';
				pc->lado = PRETO;
				pc->function = &Peao;
				
				if (ElPassante)
				{			
					if (((linha - '0') == i)&&((j == (getIntColumn(coluna) - 1))||(j == (getIntColumn(coluna) + 1))))
					{
						pc->coluna = coluna;
						pc->linha = linha;
					}					
				}
				else{
						pc->coluna = '-';
						pc->linha = '-';
					}
			}
			else if (s[k]=='P')
			{
				pc->tipo = 'P';
				pc->lado = BRANCO;
				pc->function = &Peao;
				if (ElPassante)
				{
					if (((linha-'0') == i)&&((j == (getIntColumn(coluna) - 1))||(j == (getIntColumn(coluna) + 1))))
					{
						pc->coluna = coluna;
						pc->linha = linha;
					}				
				}
				else{
					pc->coluna = '-';
					pc->linha = '-';
				}
			}
			else{
				//it is a number
				isNumber = 1;
				pc->tipo = '0';
				for (n=0; n < (s[k]-'0'); n++)
				{					
					tabuleiro[i][j] = *pc;			
			//		printf("%c ", tabuleiro[i][j].tipo);
					j++;				
				}		
				
			}
			if (!isNumber)
			{
				tabuleiro[i][j] = *pc;		
		//		printf("%c ", tabuleiro[i][j].tipo);	
				j++;
			
			
			}	
			isNumber = 0;
			k++;
		}
		i--;
		j=0;
		k++;
	}
}
int MovimentosB(char tipo, peca** tabuleiro, int lado, char* s)
{
	int mov, i, j, npos;	
	Edestiny** matrix;
	AIMatrix** AI;
	AI = (AIMatrix**) calloc(8, sizeof(AIMatrix*));
	for (i = 0 ; i < 8; i++)
	{
		AI[i] = (AIMatrix*) calloc(8, sizeof(AIMatrix));
	}
	POSITIONS *P;
	P = (POSITIONS*) calloc(100, sizeof(POSITIONS));
	int rBK = 0, rBQ = 0, rpk = 0, rpq = 0, roque = 0;
	i=0;
	//possibilidade de roque
	while(s[i]!=' ')
		i++;
	i+=3;
	while(s[i]!=' ')
	{
		if (s[i]!='-')
		{
			if (s[i] == 'K')
				rBK = 1;
			else
				if (s[i] == 'Q')
					rBQ = 1;
			else
				if(s[i] == 'k')
					rpk = 1;
			else 
				if (s[i] == 'q')
						rpq = 1;
			roque = 1;
		}else
		{
			roque = 0;
		}
			i++;		
	}
	i++;

	matrix = (Edestiny**) malloc(sizeof(Edestiny*)*8);
	for (i = 0; i < 8; i++)
	{
		matrix[i] = (Edestiny*) malloc(sizeof(Edestiny)*8);
		for (j=0; j < 8; j++){
			matrix[i][j].n = 0;
			matrix[i][j].head = NULL;
		}
			
	}
	char** positions;
	
	positions = (char**)malloc(sizeof(char*)*100);
	
	for (i = 0 ; i < 100; i++)
	{
		positions[i] = (char*)malloc(sizeof(char*)*10);
	}

	npos=0;
		for (j=0; j < 8; j++)
		{
			for (i=0; i < 8; i ++)
			{
	
				if((tabuleiro[i][j].lado == lado)&&(tabuleiro[i][j].tipo==tipo))
				{
					mov = 0;			
					tabuleiro[i][j].function(tabuleiro, i, j, &mov, matrix, P, &npos, 1, NULL, lado);	
			
				}			
			}
		}
		if ((tipo=='K')||(tipo=='k'))
		{
		
			if (roque)
			{
				if (lado==BRANCO)
				{
					if (rBK)
					{
						if ((tabuleiro[0][5].tipo=='0')&&(tabuleiro[0][6].tipo=='0'))
						{
							if ((VerificaCheque(tabuleiro, 0, 4, 0, 6, NULL))&&(VerificaCheque(tabuleiro, 0, 4, 0, 5, NULL)))
							{
								positions[npos][0] = 'K';
								positions[npos][1] = 'g';
								positions[npos][2] = '1';
								positions[npos][3] = '\0';
								npos++;						
							}						
						}
									
					}
					
					if (rBQ)
					{
						if ((tabuleiro[0][1].tipo=='0')&&(tabuleiro[0][2].tipo=='0')&&(tabuleiro[0][3].tipo=='0'))
						{
							if ((VerificaCheque(tabuleiro, 0, 4, 0, 2, NULL))&&(VerificaCheque(tabuleiro, 0, 4, 0, 3, NULL)))
							{
								positions[npos][0] = 'K';
								positions[npos][1] = 'c';
								positions[npos][2] = '1';
								positions[npos][3] = '\0';	
								npos++;		
							}					
						}
							
					}
				}else if (lado ==PRETO)
				{
					if (rpk)
					{
						if ((tabuleiro[7][5].tipo=='0')&&(tabuleiro[7][6].tipo=='0'))					
						{
							if ((VerificaCheque(tabuleiro, 7, 4, 7, 6, NULL))&&(VerificaCheque(tabuleiro, 7, 4, 7, 5, NULL)))
							{
								positions[npos][0] = 'K';
								positions[npos][1] = 'g';
								positions[npos][2] = '8';
								positions[npos][3] = '\0';
								npos++;							
							}					
						}		
					}
		
					if (rpq)
					{
						if ((tabuleiro[7][1].tipo=='0')&&(tabuleiro[7][2].tipo=='0')&&(tabuleiro[7][3].tipo=='0'))
						{
							if ((VerificaCheque(tabuleiro, 7, 4, 7, 2, NULL))&&(VerificaCheque(tabuleiro, 7, 4, 7, 3, NULL)))
							{
								positions[npos][0] = 'K';
								positions[npos][1] = 'c';
								positions[npos][2] = '8';
								positions[npos][3] = '\0';
								npos++;
							}					
							}	
					}
				}		
				roque=0;
			}
		}

		if (npos == 0)
			return 0;
		else
			return 1;	
}
int Movimentos(POSITIONS *aux, double * max, int * count, char tipo, peca** tabuleiro, int lado, char* s)
{
	int mov, i, j, npos;	
	Edestiny** matrix;
	POSITIONS *P;
	AIMatrix** AI;
	AI = (AIMatrix**) calloc(8, sizeof(AIMatrix*));
	for (i = 0 ; i < 8; i++)
	{
		AI[i] = (AIMatrix*) calloc(8, sizeof(AIMatrix));
	}
	
	P = (POSITIONS*) calloc(100, sizeof(POSITIONS));
	int rBK = 0, rBQ = 0, rpk = 0, rpq = 0, roque = 0;
	i=0;

	//possibilidade de roque
	while(s[i]!=' ')
		i++;
	i+=3;
	while(s[i]!=' ')
	{
		if (s[i]!='-')
		{
			if (s[i] == 'K')
				rBK = 1;
			else
				if (s[i] == 'Q')
					rBQ = 1;
			else
				if(s[i] == 'k')
					rpk = 1;
			else 
				if (s[i] == 'q')
						rpq = 1;
			roque = 1;
		}else
		{
			roque = 0;
		}
			i++;		
	}
	i++;

	matrix = (Edestiny**) malloc(sizeof(Edestiny*)*8);
	for (i = 0; i < 8; i++)
	{
		matrix[i] = (Edestiny*) malloc(sizeof(Edestiny)*8);
		for (j=0; j < 8; j++){
			matrix[i][j].n = 0;
			matrix[i][j].head = NULL;
		}
			
	}
	npos=0;
	indexTemp = 0;
		for (j=0; j < 8; j++)
		{
			for (i=0; i < 8; i++)
			{
	
				if((tabuleiro[i][j].lado == lado)&&(tabuleiro[i][j].tipo==tipo))
				{
					mov = 0;					
					tabuleiro[i][j].function(tabuleiro, i, j, &mov, matrix, P, &npos, 1, AI, lado);											
				}			
			}
		}
	//	printf("acabou o tabuleiro, verificando roque\n");
		if ((tipo=='K')||(tipo=='k'))
		{
		
			if (roque)
			{
				if (lado==BRANCO)
				{
					if (rBK)
					{
						if ((tabuleiro[0][5].tipo=='0')&&(tabuleiro[0][6].tipo=='0'))
						{
							if ((VerificaCheque(tabuleiro, 0, 4, 0, 6, AI))&&(VerificaCheque(tabuleiro, 0, 4, 0, 5, AI)))
							{
								P[npos].positions[0] = 'K';
								P[npos].positions[1] = 'g';
								P[npos].positions[2] = '1';
								P[npos].positions[3] = '\0';
								npos++;						
							}						
						}
									
					}
					
					if (rBQ)
					{
						if ((tabuleiro[0][1].tipo=='0')&&(tabuleiro[0][2].tipo=='0')&&(tabuleiro[0][3].tipo=='0'))
						{
							if ((VerificaCheque(tabuleiro, 0, 4, 0, 2, AI))&&(VerificaCheque(tabuleiro, 0, 4, 0, 3, AI)))
							{
								P[npos].positions[0] = 'K';
								P[npos].positions[1] = 'c';
								P[npos].positions[2] = '1';
								P[npos].positions[3] = '\0';	
								npos++;		
							}					
						}
							
					}
				}else if (lado ==PRETO)
				{
					if (rpk)
					{
						if ((tabuleiro[7][5].tipo=='0')&&(tabuleiro[7][6].tipo=='0'))
						{
							if ((VerificaCheque(tabuleiro, 7, 4, 7, 6, AI))&&(VerificaCheque(tabuleiro, 7, 4, 7, 5, AI)))
							{
								P[npos].positions[0] = 'K';
								P[npos].positions[1] = 'g';
								P[npos].positions[2] = '8';
								P[npos].positions[3] = '\0';
								npos++;							
							}					
						}		
					}
		
					if (rpq)
					{
						if ((tabuleiro[7][1].tipo=='0')&&(tabuleiro[7][2].tipo=='0')&&(tabuleiro[7][3].tipo=='0'))					
						{
							if ((VerificaCheque(tabuleiro, 7, 4, 7, 2, AI))&&(VerificaCheque(tabuleiro, 7, 4, 7, 3, AI)))
							{
								P[npos].positions[0] = 'K';
								P[npos].positions[1] = 'c';
								P[npos].positions[2] = '8';
								P[npos].positions[3] = '\0';
								npos++;
							}					
							}	
					}
				}		
				roque=0;
			}
		}	

		for (i = 0 ; i < npos; i++)
		{
	//		printf("%s   %lf\n", P[i].positions, P[i].Smov);			
			if (P[i].Smov > *max)
				*max = P[i].Smov;		
		}	
		for (i = 0 ; i < npos; i++)
		{
			
			if (P[i].Smov == *max)
			{			
				strcat(aux[(*count)].positions, P[i].positions);
				aux[(*count)].Smov = P[i].Smov;
				aux[(*count)].OC = P[i].OC;
				aux[(*count)].OL = P[i].OL;
				
				(*count)++;				
			}	
		}
		for (i=0; i < 8; i++)
			free(AI[i]);
		free(AI);
		if (npos == 0)
			return 0;
		else
			return 1;	
}
int VerificaRoque(peca** tabuleiro){
	AIMatrix** AI;
	AI = (AIMatrix**) calloc(8, sizeof(AIMatrix*));
	int i;
	for (i = 0 ; i < 8; i++)
	{
		AI[i] = (AIMatrix*) calloc(8, sizeof(AIMatrix));
	}
	if (tabuleiro[7][4].tipo !='k')
		return 0;
	if ((VerificaCheque(tabuleiro, 7, 4, 7, 5, AI)&&(VerificaCheque(tabuleiro, 7, 4, 7, 6, AI)))||(VerificaCheque(tabuleiro, 7, 4, 7, 2, AI) &&(VerificaCheque(tabuleiro, 7, 4, 7, 3, AI))))
		return 1;
	return 0;
}
void ConstroiString(peca** tabuleiro, char** s, char lado, int origemL, int origemC, int destL, int destC, char elpC, char elpL, int meioturno, int turnos)
{
	int i, j, zeros, k, rBK = 0, rBQ = 0, rpk = 0, rpq = 0, roque = 0;
	int tBK = 1, tBQ = 1, tpk = 1, tpq = 1;
	char str[4];
	k = 0;
	AIMatrix** AI;
	AI = (AIMatrix**) calloc(8, sizeof(AIMatrix*));
	for (i = 0 ; i < 8; i++)
	{
		AI[i] = (AIMatrix*) calloc(8, sizeof(AIMatrix));
	}
	
	//ROQUE
	while((*s)[k]!=' ')
		k++;
	k+=3;
	if (tabuleiro[0][0].tipo != 'R') //moveu torre branca lado rainha
		tBQ = 0;
	if (tabuleiro[0][7].tipo != 'R') //moveu torre branca lado rei
		tBK = 0;
	if (tabuleiro[7][0].tipo != 'r') //moveu torre preta lado rainha
		tpq = 0;
	if (tabuleiro[7][7].tipo != 'r') //moveu torre preta lado rei
		tpk = 0;

	while((*s)[k]!=' ')	
	{
		
		if ((*s)[k]!='-')
		{
			if ((*s)[k] == 'K')
			{
				if ((origemL == 0)&&((origemC == 4)||(origemC == 7)))//moveu rei ou torre	
				{
					if ((destL==0)&&(destC==6))//roque no lado do rei
					{											
						tabuleiro[0][7].tipo = '0';						
						tabuleiro[0][5].lado = BRANCO;						
						tabuleiro[0][5].tipo = 'R';
						tabuleiro[0][5].function = &Torre;
					}	
										
					k++;
				}					
				else{			
					rBK = 1;
					roque = 1;												
					k++;
				}
								
			}
			if ((*s)[k] == 'Q')
			{
				if ((origemL == 0)&&((origemC == 4)||(origemC == 0))) //moveu rei ou torre	
				{
					if (!rBK) //n moveu o rei anteriormente
					{
						if ((destL==0)&&(destC == 2)) //roque no lado da rainha
						{
							tabuleiro[0][0].tipo = '0';								
							tabuleiro[0][3].lado = BRANCO;						
							tabuleiro[0][3].tipo = 'R';
							tabuleiro[0][3].function = &Torre;	
						}
					}				
					k++;
				}					
				else{				
					rBQ = 1;		
					roque = 1;					
					k++;									
				}
			}
			if ((*s)[k] == 'k')
			{
				if ((origemL == 7)&&((origemC == 4)||(origemC == 7))) //moveu rei ou torre
				{
					if ((destL == 7)&&(destC == 6))
					{
			
						tabuleiro[7][7].tipo = '0';	
						
						tabuleiro[7][5].lado = PRETO;						
						tabuleiro[7][5].tipo = 'r';
						tabuleiro[7][5].function = &Torre;
			
					}
					k++;
				}					
				else{				
					rpk = 1;
					roque = 1;
					k++;											
				}
				
			}
			if ((*s)[k] == 'q')
			{
				if ((origemL == 7)&&((origemC == 4)||(origemC == 0))) //moveu rei ou torre
				{
					if (!rpk)
					{
						if ((destL == 7)&&(destC == 2))
						{
							tabuleiro[7][0].tipo = '0';	
							
							tabuleiro[7][3].lado = PRETO;						
							tabuleiro[7][3].tipo = 'r';
							tabuleiro[7][3].function = &Torre;	
						}
					}
				
					k++;
				}					
				else{				
					rpq = 1;
					roque = 1;					
					k++;
								
				}				
			}			
		}else{
			k++;
		}
		
		
	}	
	k=0;
	for (i = 7; i >= 0; i--)
	{
		for (j=0; j < 8; j++)
		{		
			zeros = 0;
			if (tabuleiro[i][j].tipo == '0')
			{
				while(tabuleiro[i][j].tipo == '0')
				{
					zeros++;
					j++;
				}
				(*s)[k] = zeros + '0';
				k++;
				j--;
			}
			else{				
				(*s)[k] = (char) tabuleiro[i][j].tipo;
				k++;
			}
		}
		if (i!=0){
			(*s)[k] = '/';
			k++;
		}		
	}
	(*s)[k] = ' ';
	k++;
	(*s)[k] = lado;
	k++;
	(*s)[k] = ' ';	
	k++;

//	if (roque)
//	{
//		if (rBK)
//		{
//			if ((tabuleiro[0][5].tipo=='0')&&(tabuleiro[0][6].tipo=='0'))
//			{
//				if ((!VerificaCheque(tabuleiro, 0, 4, 0, 6, AI))||(!VerificaCheque(tabuleiro, 0, 4, 0, 5, AI)))
//				{
//					rBK = 0;					
//				}						
//			}
//		}
//		if (rBQ)
//		{
//			if ((tabuleiro[0][1].tipo=='0')&&(tabuleiro[0][2].tipo=='0')&&(tabuleiro[0][3].tipo=='0'))
//			{
//				if ((!VerificaCheque(tabuleiro, 0, 4, 0, 2, AI))||(!VerificaCheque(tabuleiro, 0, 4, 0, 3, AI)))
//				{
//					rBQ = 0;
//				}					
//			}
//		}
//		if (rpk)
//		{
//			if ((tabuleiro[7][1].tipo=='0')&&(tabuleiro[7][2].tipo=='0')&&(tabuleiro[7][3].tipo=='0'))
//			{
//				if ((!VerificaCheque(tabuleiro, 7, 4, 7, 6, AI))||(!VerificaCheque(tabuleiro, 7, 4, 7, 5, AI)))
//				{
//					rpk = 0;	
//				}		
//			}
//		}
//		if (rpq)
//		{
//			if ((tabuleiro[7][5].tipo=='0')&&(tabuleiro[7][6].tipo=='0'))
//			{
//				if ((!VerificaCheque(tabuleiro, 7, 4, 7, 2, AI))||(!VerificaCheque(tabuleiro, 7, 4, 7, 3, AI)))
//				{
//					rpq = 0;
//				}					
//			}	
//		}
//		
//	}
	if (roque)
	{
		if ((rBK)&&(tBK))
		{
			(*s)[k] = 'K';
			k++;
		}
		if ((rBQ)&&(tBQ))
		{
			(*s)[k] = 'Q';
			k++;
		}
		if((rpk)&&(tpk))
		{
			(*s)[k] = 'k';
			k++;
		}
		if ((rpq)&&(tpq))
		{
			(*s)[k] = 'q';
			k++;
		}	
	}else{
		(*s)[k] = '-';
		k++;		
	}	
	(*s)[k] = ' ';
	k++;
	//ELPASSANT
	if (elpC != '-')
	{
		(*s)[k] = elpC;
		k++;
		(*s)[k] = elpL;
		k++;
	}
	else{
		(*s)[k] = '-';
		k++;
	}
	//MeioTurno
	(*s)[k] = ' ';
	k++;
	sprintf(str, "%d", meioturno);
	i =0;
	while(str[i] != '\0')
	{
		(*s)[k] = str[i];
		k++;
		i++;
	}	
	(*s)[k] = ' ';
	k++;
	i=0;
	sprintf(str, "%d", turnos);
	while(str[i]!='\0')
	{
		(*s)[k] = str[i];
		k++;
		i++;
	}	
	(*s)[k] = '\0';	
}
int FaltaMaterial(peca** tabuleiro){
	int i, j;
	int material = 1;
	//Rei contra rei?
	for (i=0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if ((tabuleiro[i][j].tipo != 'k')&&(tabuleiro[i][j].tipo!='K')&&(tabuleiro[i][j].tipo!='0'))
			{
				material = 0;
				continue;
			}
			
		}
	}

	if (material)
		return 1;
	//rei e cavalo contra rei?
	material = 1;
	int cb = 0, cp = 0;
	for (i=0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if ((tabuleiro[i][j].tipo!='N')&&(tabuleiro[i][j].tipo!='n')&&(tabuleiro[i][j].tipo!='K')&&(tabuleiro[i][j].tipo!='k')&&(tabuleiro[i][j].tipo!='0'))
			{
				material = 0;
				continue;
			}else{
					if (tabuleiro[i][j].tipo == 'N')
						cb++;
					if (tabuleiro[i][j].tipo == 'n')
						cp++;
			}								
		}
	}	
	if(material)
	{
		if (((cb == 1)&&(cp == 0)) || ((cb == 0)&&(cp == 1)))
			return 1;
	}
	
	material = 1;
	cb =0 ; cp = 0;
	for (i=0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if ((tabuleiro[i][j].tipo!='B')&&(tabuleiro[i][j].tipo!='b')&&(tabuleiro[i][j].tipo!='K')&&(tabuleiro[i][j].tipo!='k')&&(tabuleiro[i][j].tipo!='0'))
			{
				material = 0;
				continue;
			}else{
					if (tabuleiro[i][j].tipo == 'B')
						cb++;
					if (tabuleiro[i][j].tipo == 'b')
						cp++;
			}								
		}
	}
	if(material)
	{
		if (((cb == 1)&&(cp == 0)) || ((cb == 0)&&(cp == 1)))
			return 1;
	}
	return 0;
	
}
int VerificaChequeMate(peca** tabuleiro, int lado)
{
	int i, j, LRei, CRei, ladoOp;
	AIMatrix** AI;
	AI = (AIMatrix**) calloc(8, sizeof(AIMatrix*));
	for (i = 0 ; i < 8; i++)
	{
		AI[i] = (AIMatrix*) calloc(8, sizeof(AIMatrix));
	}
	for (i=0; i < 8; i++)
	{
		for (j=0; j < 8; j++)
		{
			if ((lado == BRANCO)&&(tabuleiro[i][j].tipo == 'K'))
			{
				LRei = i;
				CRei = j;
				continue;
			}else
			if ((lado == PRETO)&&(tabuleiro[i][j].tipo== 'k'))
			{
				LRei = i;
				CRei = j;
				continue;
			}
		}
	}
	if (lado == BRANCO)
		ladoOp = PRETO;
	else
		ladoOp = BRANCO;

	if (ladoOp == BRANCO)
	{
		if (MovimentosCheque(tabuleiro, ladoOp, 'P', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'N', LRei, CRei, AI))	
			return 0;		
		if (MovimentosCheque(tabuleiro, ladoOp, 'B', LRei, CRei, AI))		
			return 0;			
		if (MovimentosCheque(tabuleiro, ladoOp, 'R', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'Q', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'K', LRei, CRei, AI))
			return 0;
		return 1;
	}
	else{
	
		if (MovimentosCheque(tabuleiro, ladoOp, 'p', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'n', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'b', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'r', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'q', LRei, CRei, AI))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'k', LRei, CRei, AI))
			return 0;
		return 1;
	}
}

int main()
{

	char *s;
	char **historico;
	int i, index, k =0, count = 0;
	int meioturno = 0, turno = 1, captura = 0;
	peca **tabuleiro;
	int OrigemL, OrigemC, DestL, DestC;
	char movimento[10]; 
	char turnos[4];
	int lado;
	int chequemate = 0;
	char elpC, elpL;
	int afogamento = 0;
	int faltamaterial= 0;
	int ismeioturno = 0;
	double max = 0.0;
	POSITIONS* aux;	
	FILE *file;
	file = fopen("case4.txt", "r");
	aux = (POSITIONS*) calloc(100, sizeof(POSITIONS));
	AIMatrix** AI;
	AI = (AIMatrix**) calloc(8, sizeof(AIMatrix*));
	for (i = 0 ; i < 8; i++)
	{
		AI[i] = (AIMatrix*) calloc(8, sizeof(AIMatrix));
	}
	
	s = (char*) malloc(sizeof(char)*100);
	historico = (char**) malloc(sizeof(char*)*300);
	for (i = 0 ; i < 300; i++)
	{
		historico[i] = (char*) malloc(sizeof(char)*100);
	}
	tabuleiro = (peca**) malloc(sizeof(peca*)*8);
	
	for (i = 0; i < 8; i++)
	{
		tabuleiro[i] = (peca*) malloc(sizeof(peca)*8);
	}
	scanf(" %[^\n]", s);

	PreencherTabuleiro(tabuleiro, s);

	index = 0;
	strcpy(historico[index], s);
	index++;
	i=0;

	while(s[i]!=' ')
		i++;
	i++;
	if (s[i]=='w')
		lado = BRANCO;
	else
		lado = PRETO;
	i+=2;
	
	while(s[i] != ' ')
		i++;
	i++;
	
	while(s[i]!=' ')
		i++;
	i++;

	while(s[i]!=' ') //meio turno
	{
		turnos[k] = s[i];	
		k++;
		i++;
	}
	turnos[k] = '\0';
	meioturno = atoi(turnos);

	i++;
	k=0;
	while((s[i]!=' ')&&(s[i]!='\n')&&(s[i]!='\0'))
	{
		turnos[k] = s[i];
		k++;
		i++;
	}
	turnos[k] = '\0';
	turno = atoi(turnos);		
	chequemate = 0;
	peca *auxP;
	peca *none;
	none = malloc(sizeof(peca));
	auxP = malloc(sizeof(peca));
	none->tipo = '0';
	int canMov;

		
	if (lado == BRANCO)
	{
		if (FaltaMaterial(tabuleiro))
			faltamaterial = 1;
//		else
//		if ((!MovimentosB('P', tabuleiro, BRANCO,s))&&(!MovimentosB('N', tabuleiro, BRANCO,s))&&(!MovimentosB('B', tabuleiro, BRANCO,s))&&(!MovimentosB('R', tabuleiro, BRANCO,s))&&(!MovimentosB('Q', tabuleiro, BRANCO,s))&&(!MovimentosB('K', tabuleiro, BRANCO,s)))
//		{		
//			if (!VerificaChequeMate(tabuleiro, BRANCO))
//				chequemate = 1;
//			else{			
//				afogamento = 1;
//			}					
//		}		
	}else{
		if (FaltaMaterial(tabuleiro))
			faltamaterial = 1;
//		else
//		if ((!MovimentosB('p', tabuleiro, PRETO,s))&&(!MovimentosB('n', tabuleiro, PRETO,s))&&(!MovimentosB('b', tabuleiro, PRETO,s))&&(!MovimentosB('r', tabuleiro, PRETO,s))&&(!MovimentosB('q', tabuleiro, PRETO,s))&&(!MovimentosB('k', tabuleiro, PRETO,s)))
//		{			
//			if (!VerificaChequeMate(tabuleiro, PRETO))
//				chequemate = 1;
//			else{			
//				afogamento = 1;
//			}	
//		}	
	}
	if ((!chequemate)&&(!afogamento)&&(!faltamaterial)&&(meioturno < 50))
	{
		
	//	scanf("%s", movimento);
		fgets(movimento, 10, file);
		printf("%s\n", movimento);
		OrigemC = getIntColumn(movimento[0]);
		OrigemL = movimento[1] - '0' - 1;
		DestC = getIntColumn(movimento[2]);
		DestL = movimento[3] - '0' - 1;	
	}
	if (chequemate)
	{			
		for (i = 0; i < (index); i++)		
			printf("%s\n", historico[i]);
			if (lado == BRANCO)
			{
				printf("Xeque-mate -- Vitoria: PRETO\n");						
			}else{
				printf("Xeque-mate -- Vitoria: BRANCO\n");
			}
	}
	if (afogamento)			
	{
		for (i = 0; i < (index); i++)		
			printf("%s\n", historico[i]);
		printf("Empate -- Afogamento");
	}
	if (faltamaterial)
	{
		for (i = 0; i < (index); i++)		
			printf("%s\n", historico[i]);
		printf("Empate -- Falta de Material");
	}
	if (meioturno >= 50)
	{
		for (i = 0; i < (index); i++)		
			printf("%s\n", historico[i]);
		printf("Empate -- Regra dos 50 Movimentos");
		meioturno++;
	}
//	printf("comecou while\n");
//	while ((VerificaCheque(tabuleiro, OrigemL, OrigemC, DestL, DestC, AI))&&(!chequemate)&&(meioturno <= 50)&&(!afogamento)&&(!faltamaterial))
	while ((!chequemate)&&(meioturno <= 50)&&(!afogamento)&&(!faltamaterial))	
	{		
		//	printf("%d %d %d %d\n", OrigemL, OrigemC, DestL, DestC);	
			//ElPassant
			captura = 0;
			elpC = '-';
			elpL = '-';
			if ((tabuleiro[OrigemL][OrigemC].tipo == 'p')||(tabuleiro[OrigemL][OrigemC].tipo == 'P'))
			{
				if (abs(DestL - OrigemL) > 1)
				{
					elpC = getColumn(OrigemC);
					if (tabuleiro[OrigemL][OrigemC].lado == BRANCO)
						elpL = OrigemL + 2 + '0';
					else
						elpL = OrigemL + '0';
				}
				if ((movimento[4]!='\n')&&(movimento[4]!='\0'))
				{							
					tabuleiro[OrigemL][OrigemC].tipo = movimento[4];
					if (movimento[4]=='Q')
						tabuleiro[OrigemL][OrigemC].function = &Rainha;
					else if (movimento[4]=='N')
						tabuleiro[OrigemL][OrigemC].function = &Cavalo;
					else if (movimento[4]=='B')
						tabuleiro[OrigemL][OrigemC].function = &Bispo;
					else if (movimento[4]=='R')
						tabuleiro[OrigemL][OrigemC].function = &Torre;
				}
			}
			auxP->coluna =tabuleiro[OrigemL][OrigemC].coluna;
			auxP->function = tabuleiro[OrigemL][OrigemC].function;
			auxP->lado = tabuleiro[OrigemL][OrigemC].lado;
			auxP->tipo = tabuleiro[OrigemL][OrigemC].tipo;		
			auxP->coluna = tabuleiro[OrigemL][OrigemC].coluna;
			auxP->linha = tabuleiro[OrigemL][OrigemC].linha;
			tabuleiro[OrigemL][OrigemC] = *none;
			if (tabuleiro[DestL][DestC].tipo!='0')
				captura = 1;
			tabuleiro[DestL][DestC] = *auxP;
			
		
			int j;
			for (i = 7; i >=0; i--)
			{
				for (j=0; j < 8; j++)
					printf("%c ", tabuleiro[i][j].tipo);
				printf("\n");
			}
			printf("\n");
			//check if was an ElPassant
			if ((DestL == ((elpL - '0') - 1))&&(DestC == getIntColumn(elpC)))
			{
				tabuleiro[DestL+1][DestC].tipo = '0';
				captura = 1;
			}	
			if ((auxP->tipo == 'P')||(captura)||(auxP->tipo=='p'))
					meioturno = 0;
				else
					meioturno++;
			if (meioturno <= 50){
				if (meioturno == 50)
					ismeioturno = 1;
				if (tabuleiro[DestL][DestC].lado == BRANCO) //Pecas brancas acabaram de jogar, ver se pretas conseguem realizar algum movimento
				{	
					if (FaltaMaterial(tabuleiro)){
						faltamaterial = 1;
						if (!ismeioturno)
						{
							ConstroiString(tabuleiro, &s, 'b', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);				
							strcpy(historico[index], s);
							index++;
						}					
					}
					else
					{
						canMov = 0;
						max = 0.0;
						count = 0;
						if (Movimentos(aux, &max, &count, 'p', tabuleiro, PRETO,s))	
							canMov = 1;
						if (Movimentos(aux, &max, &count, 'n', tabuleiro, PRETO,s))
							canMov = 1;
						if (Movimentos(aux, &max, &count, 'b', tabuleiro, PRETO,s))
							canMov = 1;
						if (Movimentos(aux, &max, &count, 'r', tabuleiro, PRETO,s))
							canMov = 1;
						if (Movimentos(aux, &max, &count, 'q', tabuleiro, PRETO,s))
							canMov = 1;
						if (Movimentos(aux, &max, &count, 'k', tabuleiro, PRETO,s))
							canMov = 1;	
						
						if (canMov)
						{					
							//Salva tabuleiro atual em s -> qd achar tipo 0, ir somando até encontrar numero diferente ou final de linha					
							//-> Meio-turno: acrescenta qd o movimento n envolver captura ou peão, zerar qd envolver. 
							//Checar quando peao faz o movimento de duas casas - Acrescentar ElPassant				]
							//Verificar roque	
						
							ConstroiString(tabuleiro, &s, 'b', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);				
							strcpy(historico[index], s);
							printf("%s\n", historico[index]);
						//	printf("%s\n", historico[index]);				
							index++;
											
							OrdenaPositions2(aux, count);
							
							for (i = 0; i < count; i++)
							{
								if (aux[i].Smov == max)
								{
								//	printf("Best move: %s   %lf  %d %d\n", aux[i].positions, aux[i].Smov, aux[i].OC, aux[i].OL);
									strcpy(movimento, aux[i].positions);
									break;
								}
							}	
											
							printf("movimento %s\n", movimento);
							OrigemC = aux[i].OC;
							OrigemL = aux[i].OL;	
							
							//Se n for promocao de peao
							if ((movimento[strlen(movimento)-1] != 'N')&&(movimento[strlen(movimento)-1] != 'B')&&(movimento[strlen(movimento)-1] != 'Q')&&(movimento[strlen(movimento)-1] != 'R'))
							{
								DestC = getIntColumn(movimento[strlen(movimento)-2]);
								DestL = movimento[strlen(movimento)-1] - '0' - 1;
							}else{
								DestC = getIntColumn(movimento[strlen(movimento)-3]);
								DestL = movimento[strlen(movimento)-2] - '0' - 1;
							}
							if ((OrigemC == 7)&&(OrigemL == 7)&&(tabuleiro[OrigemL][OrigemC].tipo == 'r')) //moveu torre, verificar o roque e mover o rei
							{
								if (VerificaRoque(tabuleiro))
								{
									OrigemC = 4;
									OrigemL = 7;
									DestL = 7;
									DestC = 6;		
								}
												
							}else if((OrigemC == 0)&&(OrigemL==7)&&(tabuleiro[OrigemL][OrigemC].tipo == 'r'))					
							{
								if (VerificaRoque(tabuleiro))
								{
									OrigemC = 4;
									OrigemL = 7;
									DestL = 7;
									DestC = 2;
								}
								
							}	
							free(aux);
							aux = (POSITIONS*) calloc(100, sizeof(POSITIONS));
							max = 0.0;
							count = 0;																						
						}
//						else if (!VerificaChequeMate(tabuleiro, PRETO)){						
//							ConstroiString(tabuleiro, &s, 'b', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);				
//							strcpy(historico[index], s);
//							index++;
//							chequemate = 1;												
//						}else{
//							ConstroiString(tabuleiro, &s, 'b', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);				
//							strcpy(historico[index], s);
//							index++;
//							afogamento = 1;
//						}
					}				
						
				}else{
					turno++;
					if (FaltaMaterial(tabuleiro)){
						faltamaterial = 1;
						if (!ismeioturno)
						{
							ConstroiString(tabuleiro, &s, 'w', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);				
							strcpy(historico[index], s);
							index++;
						}
					
					}else
				//	if ((MovimentosB('P', tabuleiro, BRANCO,s))||(MovimentosB('N', tabuleiro, BRANCO,s))||(MovimentosB('B', tabuleiro, BRANCO,s))||(MovimentosB('R', tabuleiro, BRANCO,s))||(MovimentosB('Q', tabuleiro, BRANCO,s))||(MovimentosB('K', tabuleiro, BRANCO,s)))
					{						
						ConstroiString(tabuleiro, &s, 'w', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);
						strcpy(historico[index], s);
						printf("%s\n", historico[index]);
						index++;
						
					//	scanf("%s", movimento);
						fgets(movimento, 10, file);
						printf("%s\n", movimento);
						
						OrigemC = getIntColumn(movimento[0]);
						OrigemL = movimento[1] - '0' - 1;						
						DestC = getIntColumn(movimento[2]);
						DestL = movimento[3] - '0' - 1;	
				
						
						while ((tabuleiro[OrigemL][OrigemC].lado != BRANCO)&&((tabuleiro[DestL][DestC].tipo!='0')&&(tabuleiro[DestL][DestC].lado != PRETO)))
						{				
							printf("Movimento invalido. Tente novamente.\n");			
							scanf("%s", movimento);
							OrigemC = getIntColumn(movimento[0]);
							OrigemL = movimento[1] - '0' - 1;
							DestC = getIntColumn(movimento[2]);
							DestL = movimento[3] - '0' - 1;		
						}						
					}
//					else if (!VerificaChequeMate(tabuleiro, BRANCO)){
//						ConstroiString(tabuleiro, &s, 'w', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);
//						strcpy(historico[index], s);
//						index++;				
//						chequemate = 1;					
//					}else {
//						ConstroiString(tabuleiro, &s, 'w', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);
//						strcpy(historico[index], s);
//						index++;
//						afogamento = 1;
//					}		
				}
				if (chequemate)
				{			
					for (i = 0; i < (index); i++)		
						printf("%s\n", historico[i]);
					if (tabuleiro[DestL][DestC].lado == BRANCO)
					{
						printf("Xeque-mate -- Vitoria: BRANCO\n");						
					}else{
						printf("Xeque-mate -- Vitoria: PRETO\n");
					}
				}
			}
		}
	//	printf("ops cheque mate: %d meio turno: %d afogamento: %d falta material %d \n", chequemate, meioturno, afogamento, faltamaterial);
		if (index > 1)
		{			
			if (ismeioturno)
			{
				for (i = 0; i < (index); i++)		
					printf("%s\n", historico[i]);
				printf("Empate -- Regra dos 50 Movimentos");
			}else
			if (afogamento)
			{
				for (i = 0; i < (index); i++)		
							printf("%s\n", historico[i]);
					printf("Empate -- Afogamento");	
			}
			else if (faltamaterial)
			{
				for (i = 0; i < (index); i++)		
							printf("%s\n", historico[i]);
					printf("Empate -- Falta de Material");		
			}
		}
	fclose(file);
	free(s);
	free(historico);
	free(tabuleiro);
}
