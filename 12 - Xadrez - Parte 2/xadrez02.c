/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 15/05/2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define BRANCO 0
#define PRETO 1
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
typedef struct peca{
	char coluna;
	char linha;
	int lado;
	char tipo;
	void (*function)(struct peca** tabuleiro, int origemL, int origemC, int* mov, Edestiny** matrix, char** positions, int* i, int VC);
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
char* OrdenaPositions(char** positions, int npos,int start, int** used, char tipo)
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
						if (positions[k][strlen(positions[k])-1] == '.')
						{
							linha = positions[k][strlen(positions[k])-5] - 1 -'0';
							coluna = (int) getIntColumn(positions[k][strlen(positions[k])-6]);
						}else
						if ((positions[k][strlen(positions[k])-1] == 'N')||(positions[k][strlen(positions[k])-1] == 'B')||(positions[k][strlen(positions[k])-1] == 'R')||(positions[k][strlen(positions[k])-1] == 'Q'))
						{
							linha = positions[k][strlen(positions[k])-2] - 1 -'0';
							coluna = (int) getIntColumn(positions[k][strlen(positions[k])-3]);
						}
						else{
							linha = positions[k][strlen(positions[k])-1] - 1 -'0';
							coluna = (int) getIntColumn(positions[k][strlen(positions[k])-2]);	
						}
					}else{
						linha = positions[k][strlen(positions[k])-1] - 1 -'0';
						coluna = (int) getIntColumn(positions[k][strlen(positions[k])-2]);	
					}
					if ((coluna==j)&&(linha==i))
					{
						(*used)[k] = 1;			
						return positions[k];
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
int MovimentosCheque(peca** copy, int lado, char tipo, int LRei, int CRei)
{
	int j, i, npos, mov, linha, coluna, k;
	Edestiny** matrix;
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
	npos = 0;
	k=0;
	for (i=7; i >= 0; i--)
	{
			for (j=0; j < 8; j++)
			{	
				if((copy[i][j].lado == lado)&&(copy[i][j].tipo==tipo))
				{	
					mov = 0;									
					copy[i][j].function(copy, i, j, &mov, matrix, positions, &npos, 0);							
				}			
			}
	}
	for (k=0 ; k < npos; k++)
	{
		linha = positions[k][strlen(positions[k])-1] - 1 -'0';
		coluna = (int) getIntColumn(positions[k][strlen(positions[k])-2]);
		if ((linha == LRei)&&(coluna == CRei)){					
			return 1;
		}
	}
	return 0;
}
int VerificaCheque(peca** tabuleiro, int origemL, int origemC, int destL,int destC)
{
	int ladoOp , lado, LRei, CRei, i, j;
	peca** copy;
	peca* aux;
	peca* p;
	p = (peca*) malloc(sizeof(peca));
	p->function = tabuleiro[origemL][origemC].function;	
	p->lado = tabuleiro[origemL][origemC].lado;
	p->tipo = tabuleiro[origemL][origemC].tipo;
	lado = tabuleiro[origemL][origemC].lado;
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
				copy[i][j] = *p;
			}else{				
				copy[i][j].function = tabuleiro[i][j].function;
				copy[i][j].lado = tabuleiro[i][j].lado;
				copy[i][j].tipo = tabuleiro[i][j].tipo;
			}					
		}
	}
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
	if (lado == BRANCO)
		ladoOp = PRETO;
	else
		ladoOp = BRANCO;

	if (ladoOp == BRANCO)
	{
		if (MovimentosCheque(copy, ladoOp, 'P', LRei, CRei))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'N', LRei, CRei))	
			return 0;		
		if (MovimentosCheque(copy, ladoOp, 'B', LRei, CRei))		
			return 0;			
		if (MovimentosCheque(copy, ladoOp, 'R', LRei, CRei))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'Q', LRei, CRei))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'K', LRei, CRei))
			return 0;
		return 1;
	}
	else{

		if (MovimentosCheque(copy, ladoOp, 'p', LRei, CRei))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'n', LRei, CRei))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'b', LRei, CRei))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'r', LRei, CRei))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'q', LRei, CRei))
			return 0;
		if (MovimentosCheque(copy, ladoOp, 'k', LRei, CRei))
			return 0;
		return 1;
	}
	
}
void AddToMatrix(Edestiny** matrix, int origemL, int origemC, int destL, int destC, int pos, char tipo, int x)
{
	
	matrix[destL][destC].n++;
	AddToList(&matrix[destL][destC].head, origemL, origemC, destL, destC, pos, tipo, x);
	
}
void AddToPositionsP(char** positions, int *i, int L, int C, int newC, int x, int P)
{
	int j;
	char promo_list[4];
	promo_list[0] = 'N';
	promo_list[1] = 'B';
	promo_list[2] = 'R';
	promo_list[3] = 'Q';
	if (!x)
	{
		if (P)
		{
			for (j=0; j < 4; j++)	
			{
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (L + 1) + '0';
				positions[(*i)][3] = promo_list[j];
				positions[(*i)][4] = '\0';
				(*i)++;				
			}
		}
		else{
			positions[(*i)][0] = getColumn(C);
			positions[(*i)][1] = getColumn(C);
			positions[(*i)][2] = (L + 1) + '0';
			positions[(*i)][3] = '\0';		
			(*i)++;
		}
		
	}else{
		if (P)
		{
			for (j=0; j < 4; j++)
			{
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (L+1)+ '0';
				positions[(*i)][4] = promo_list[j];	
				positions[(*i)][5] = '\0';
				(*i)++;
			}
			
			
		}else{
			positions[(*i)][0] = getColumn(C);
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (L+1)+ '0';
			positions[(*i)][4] = '\0';			
			(*i)++;
		}
	}	
}
void AddToPositions(char** positions, int i, char tipo, int L, int C, int x)
{
	if (!x){
		positions[i][0] = tipo;
		positions[i][1] = getColumn(C);
		positions[i][2] = (L + 1) + '0';
		positions[i][3] = '\0';
	}
	else{
		positions[i][0] = tipo;
		positions[i][1] = 'x';
		positions[i][2] = getColumn(C);
		positions[i][3] = (L + 1) + '0';
		positions[i][4] = '\0';	
	}
	
}
void D(peca** tabuleiro, int L, int C, char** positions, int* m, int* i, Edestiny** matrix, char tipo, int VC)
{
	int newL, newC;

	
	//Diagnoal esquerda inferior
	newL = L - 1;
	newC = C - 1;
	while  ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), tipo,  newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);			
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), tipo, newL, newC, 0);			
			//AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);		
			(*i)++;
		}
		newL--;
		newC--;
	}
	if ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), tipo, newL, newC, 1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;		
			}
		}else{
			AddToPositions(positions, (*i), tipo, newL, newC, 1);		
			(*i)++;		
		}
	}
//	}
	//Diagonal esquerda superior
	newL = L + 1;
	newC = C - 1;
	while  ((newC>=0)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), tipo, newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);		
				(*i)++;
			}	
		}else{
			AddToPositions(positions, (*i), tipo, newL, newC, 0);			
			//AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);		
			(*i)++;
		}
		newC--;
		newL++;
	}
	if ((newC>=0)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), tipo, newL, newC, 1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;		
			}
		}else{
			AddToPositions(positions, (*i), tipo, newL, newC, 1);		
			(*i)++;		
		}						
	}	
	//Diagonal direita inferior
	newL = L - 1;
	newC = C + 1;
	while  ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), tipo, newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);			
				(*i)++;
			}	
		}else{
			AddToPositions(positions, (*i),tipo, newL, newC, 0);			
		//	AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);		
			(*i)++;
		}
		newC++;
		newL--;
	}
	if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), tipo, newL, newC, 1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;		
			}
		}else{
			AddToPositions(positions, (*i), tipo, newL, newC, 1);		
			(*i)++;		
		}
	}
	//Diagonal direita superior
	newL = L + 1;
	newC = C + 1;
	while  ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), tipo, newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);			
				(*i)++;
			}	
		}else{
			AddToPositions(positions, (*i), tipo, newL, newC, 0);			
		//	AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);		
			(*i)++;
		}
		newC++;
		newL++;
	}
	if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), tipo, newL, newC, 1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;		
			}
		}else{
			AddToPositions(positions, (*i), tipo, newL, newC, 1);		
			(*i)++;		
		}
	}		
	*m = *i;
}
void CBDE(peca** tabuleiro, int L, int C, char** positions, int* m, int* i, Edestiny** matrix, char tipo, int VC)
{
	
	int newL, newC;

	//Para esquerda
	newC = C - 1;
	while  ((newC>=0)&&(tabuleiro[L][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				AddToPositions(positions, (*i), tipo, L, newC, 0);				
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);				
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), tipo, L, newC, 0);			
		//	AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);			
			(*i)++;
		}	
		newC--;		
	}
	if ((newC>=0)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				AddToPositions(positions, (*i), tipo, L, newC, 1);									
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 1);
				(*i)++;		
			}
		}
		else{
			AddToPositions(positions, (*i), tipo, L, newC, 1);		
			(*i)++;	
		}					
	}
//	}
	//Para baixo
	newL = L - 1;
	while  ((newL>=0)&&(tabuleiro[newL][C].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				AddToPositions(positions, (*i), tipo, newL, C, 0);
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);				
				(*i)++;			
			}
		}else{
			AddToPositions(positions, (*i), tipo, newL, C, 0);
		//	AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);			
			(*i)++;	
		}
		newL--;		
	}
	if ((newL>=0)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				AddToPositions(positions, (*i), tipo, newL, C, 1);
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 1);
				(*i)++;	
			}
		}
		else{
			AddToPositions(positions, (*i), tipo, newL, C, 1);	
			(*i)++;	
		}					
	}
	//Para cima
	newL = L+1;	
	while  ((newL<8)&&(tabuleiro[newL][C].tipo == '0'))
	{	
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				AddToPositions(positions, (*i), tipo,  newL, C, 0);				
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);				
				(*i)++;
			}	
		}
		else{
			AddToPositions(positions, (*i), tipo, newL, C, 0);				
	//		AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);			
			(*i)++;
		}
		newL++;		
	}
	if ((newL<8)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				AddToPositions(positions, (*i), tipo, newL, C, 1);
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 1);
				(*i)++;	
			}
		}
		else{
			AddToPositions(positions, (*i), tipo, newL, C, 1);	
			(*i)++;	
		}					
	}		

	//Para direita
	newC = C + 1;
	while  ((newC<8)&&(tabuleiro[L][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				AddToPositions(positions, (*i), tipo, L, newC, 0);				
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);				
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), tipo, L, newC, 0);				
	//		AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);			
			(*i)++;
		}
		newC++;
	}
	if ((newC<8)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				AddToPositions(positions, (*i), tipo, L, newC, 1);									
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 1);
				(*i)++;		
			}
		}
		else{
			AddToPositions(positions, (*i), tipo, L, newC, 1);		
			(*i)++;	
		}					
	}
	*m =*i;
}
void CheckMatrix(char** positions, Edestiny** matrix)
{
	int i, j;
	struct list *p;
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
						positions[p->pos] = (char*)malloc(sizeof(char*)*10);					
						if (p->origemC != p->next->origemC)
						{
							positions[p->pos][0] = p->tipo;
							positions[p->pos][1] = getColumn(p->origemC);
							positions[p->pos][2] = getColumn(p->destC);
							positions[p->pos][3] = p->destL + 1 +'0';
							positions[p->pos][4] = '\0';
							
							positions[p->next->pos][0] = p->next->tipo;
							positions[p->next->pos][1] = getColumn(p->next->origemC);
							positions[p->next->pos][2] = getColumn(p->next->destC);
							positions[p->next->pos][3] = p->next->destL + 1 +'0';
							positions[p->next->pos][4] = '\0';				
						}						
						else if (p->origemL != p->next->origemL){
							positions[p->pos][0] = p->tipo;
							positions[p->pos][1] = p->origemL + 1 +'0';
							positions[p->pos][2] = getColumn(p->destC);
							positions[p->pos][3] = p->destL + 1 + '0';
							positions[p->pos][4] = '\0';
							
							positions[p->next->pos][0] = p->next->tipo;
							positions[p->next->pos][1] = p->next->origemL + 1 + '0';
							positions[p->next->pos][2] = getColumn(p->next->destC);
							positions[p->next->pos][3] = p->next->destL + 1 +'0';
							positions[p->next->pos][4] = '\0';
						}else{
							positions[p->pos][0] = p->tipo;
							positions[p->pos][1] = getColumn(p->origemC);
							positions[p->pos][2] = p->origemL + 1 + '0';
							positions[p->pos][3] = getColumn(p->destC);
							positions[p->pos][4] = p->destL+ 1 + '0';
							positions[p->pos][5] = '\0';
							
							positions[p->next->pos][0] = p->next->tipo;
							positions[p->next->pos][1] = getColumn(p->next->origemC);
							positions[p->next->pos][2] = p->next->origemL + 1 + '0';
							positions[p->next->pos][3] = getColumn(p->next->destC);
							positions[p->next->pos][4] = p->next->destL+ 1 + '0';
							positions[p->next->pos][5] = '\0';
						}						
					}
					else{
						if (p->origemC != p->next->origemC)
						{
							positions[p->pos][0] = p->tipo;
							positions[p->pos][1] = getColumn(p->origemC);
							positions[p->pos][2] = 'x';
							positions[p->pos][3] = getColumn(p->destC);
							positions[p->pos][4] = p->destL+ 1 + '0';
							positions[p->pos][5] = '\0';
							
							positions[p->next->pos][0] = p->next->tipo;
							positions[p->next->pos][1] = getColumn(p->next->origemC);
							positions[p->next->pos][2] = 'x';
							positions[p->next->pos][3] = getColumn(p->next->destC);
							positions[p->next->pos][4] = p->next->destL+ 1 + '0';
							positions[p->next->pos][5] = '\0';
						}						
						else if (p->origemL != p->next->origemL){
							positions[p->pos][0] = p->tipo;
							positions[p->pos][1] = p->origemL+ 1 + '0';
							positions[p->pos][2] = 'x';
							positions[p->pos][3] = getColumn(p->destC);
							positions[p->pos][4] = p->destL+ 1 + '0';
							positions[p->pos][5] = '\0';
							
							positions[p->next->pos][0] = p->next->tipo;
							positions[p->next->pos][1] = p->next->origemL+ 1 + '0';
							positions[p->next->pos][2] = 'x';
							positions[p->next->pos][3] = getColumn(p->next->destC);
							positions[p->next->pos][4] = p->next->destL+ 1 + '0';
							positions[p->next->pos][5] = '\0';
						}else{
							positions[p->pos][0] = p->tipo;
							positions[p->pos][1] = getColumn(p->origemC);
							positions[p->pos][2] = p->origemL+ 1 + '0';
							positions[p->pos][3] = 'x';
							positions[p->pos][4] = getColumn(p->destC);
							positions[p->pos][5] = p->destL+ 1 + '0';
							positions[p->pos][6] = '\0';
							
							positions[p->next->pos][0] = p->next->tipo;
							positions[p->next->pos][1] = getColumn(p->next->origemC);
							positions[p->next->pos][2] = p->next->origemL+ 1 + '0';
							positions[p->next->pos][3] = 'x';
							positions[p->next->pos][4] = getColumn(p->next->destC);
							positions[p->next->pos][5] = p->next->destL+ 1 + '0';
							positions[p->next->pos][6] = '\0';
						}	
					}
					
				}
			}
		}
	}
}


void Torre(peca** tabuleiro, int L, int C, int* mov, Edestiny** matrix, char** positions, int* i, int VC)
{
	int m;	

	*mov = 0;

	CBDE(tabuleiro, L, C, positions, &m, i, matrix, 'R', VC);
	*mov += m;
	if(VC)
		CheckMatrix(positions, matrix);
}
void Bispo (peca** tabuleiro, int L, int C, int* mov, Edestiny** matrix, char** positions, int* i, int VC)
{
	
	int  m;

	*mov = 0;

	D(tabuleiro, L, C, positions, &m, i, matrix, 'B', VC);

	*mov += m ;
	if(VC)
		CheckMatrix(positions, matrix);
}
void Cavalo(peca** tabuleiro, int L, int C, int* mov, Edestiny** matrix, char** positions, int* i, int VC)
{
	int newL, newC;
	//Duas para a esquerda uma para baixo
	newL = L - 1;
	newC = C - 2;

	if((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
				(*i)++;
			}
		}else{		
			AddToPositions(positions, (*i), 'N', newL, newC, 0);
		//	AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
			(*i)++;
		}
	}else 
		if ((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
		{	
			if(VC)
			{
				if(VerificaCheque(tabuleiro, L, C, newL, newC))
				{
					AddToPositions(positions, (*i), 'N', newL, newC,1);			
					AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
					(*i)++;
				}
			}else{		
				AddToPositions(positions, (*i), 'N', newL, newC, 1);		
				(*i)++;
			}
		}
//	}
	//Duas para a esquerda uma para cima
	newL = L + 1;
	newC = C - 2;
	if((newL < 8)&&(newC >= 0)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'N', newL, newC, 0);
		//	AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
			(*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				(*i)++;
			}
		}else{		
			AddToPositions(positions, (*i), 'N', newL, newC, 1);		
			(*i)++;
		}
	}

	//Duas para baixo uma para esquerda
	newL = L-2;
	newC = C - 1;
	if((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N',0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'N', newL, newC, 0);
		//	AddToMatrix(matrix, L, C, newL, newC, (*i), 'N',0);
			(*i)++;
		}
	
	}else
	if ((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				(*i)++;
			}
		}else{		
			AddToPositions(positions, (*i), 'N', newL, newC, 1);		
			(*i)++;
		}
	}
	//Duas para cima uma para esquerda
	newL = L + 2;
	newC = C - 1;
	if((newL < 8)&&(newC >=0)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
			}
		}else{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);
		//		AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC >=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				(*i)++;
			}
		}else{		
			AddToPositions(positions, (*i), 'N', newL, newC, 1);		
			(*i)++;
		}
	}
	//Duas para baixo uma para direita
	newL = L-2;
	newC = C + 1;	
	if((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i),'N',0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'N', newL, newC, 0);
	//		AddToMatrix(matrix, L, C, newL, newC, (*i),'N',0);
			(*i)++;
		}		
	}else
	if ((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				(*i)++;
			}
		}else{		
			AddToPositions(positions, (*i), 'N', newL, newC, 1);		
			(*i)++;
		}
	}
	//Duas para cima uma para direita
	newL = L+2;
	newC = C+1;
	if((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'N', newL, newC, 0);
		//	AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
			(*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				(*i)++;
			}
		}else{		
			AddToPositions(positions, (*i), 'N', newL, newC, 1);		
			(*i)++;
		}
	}
//	}
	//Duas para a direita uma para baixo
	newL = L - 1;
	newC = C + 2;
	if((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
			}
		}
		else{
			AddToPositions(positions, (*i), 'N', newL, newC, 0);
	//		AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
			(*i)++;
		}
	}else
	if ((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				(*i)++;
			}
		}else{		
			AddToPositions(positions, (*i), 'N', newL, newC, 1);		
			(*i)++;
		}
	}
	//Duas para a direita uma para cima
	newL = L + 1;
	newC = C + 2;
	if((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;		
			}
		}else{
			AddToPositions(positions, (*i), 'N', newL, newC, 0);
	//		AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
			(*i)++;	
		}		
	}else
	if ((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'N', newL, newC,1);			
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				(*i)++;
			}
		}else{		
			AddToPositions(positions, (*i), 'N', newL, newC, 1);		
			(*i)++;
		}
	}
	*mov = (*i);
	
	if (VC)
		CheckMatrix(positions, matrix);

}
void Rainha(peca** tabuleiro,int L, int C, int* mov, Edestiny** matrix, char** positions, int* i, int VC)
{
	
	int m;	
	*mov = 0;

	CBDE(tabuleiro, L, C, positions, &m, i, matrix, 'Q', VC);
	*mov+=m;
	D(tabuleiro, L, C, positions, &m, i, matrix, 'Q', VC);
	*mov+=m;
	if (VC)
		CheckMatrix(positions, matrix);
}
void Rei(peca** tabuleiro,int L, int C, int* mov, Edestiny** matrix, char** positions, int* i, int VC)
{

	int newL, newC;
	//Diagnoal esquerda inferior
	newL = L - 1;
	newC = C - 1;
	if((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC)){			
				AddToPositions(positions, (*i), 'K', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, newC, 0);
	//		AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
			(*i)++;
		}		
	}else
	if ((newC>=0)&&(newL>=0)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC)){			
				AddToPositions(positions, (*i), 'K', newL, newC, 1);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, newC, 1);
			(*i)++;
		}	
	}
	//Para esquerda
	newC = C - 1;
	if ((newC>=0)&&(tabuleiro[L][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				AddToPositions(positions, (*i), 'K', L, newC, 0);
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', L, newC, 0);
		//	AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
			(*i)++;
		}
		
	}else
	if ((newC>=0)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC)){			
				AddToPositions(positions, (*i), 'K', L, newC, 1);
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', L, newC, 1);
			(*i)++;
		}		
	}
	//Diagonal esquerda superior
	newL = L + 1;
	newC = C - 1;
	if((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'K', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				(*i)++;
			}
		}
		else{
			AddToPositions(positions, (*i), 'K', newL, newC, 0);
	//		AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
			(*i)++;
		}
	}else
	if ((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))			
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC)){			
				AddToPositions(positions, (*i), 'K', newL, newC, 1);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, newC, 1);
			(*i)++;
		}	
	}

	//Para baixo
	newL = L - 1;
	if ((newL>=0)&&(tabuleiro[newL][C].tipo == '0'))
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				AddToPositions(positions, (*i), 'K', newL, C, 0);
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);			
				(*i)++;
			}
		}
		else{
				AddToPositions(positions, (*i), 'K', newL, C, 0);
	//			AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);				
				(*i)++;
		}
	}else
	if ((newL>=0)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C)){			
				AddToPositions(positions, (*i), 'K', newL, C, 1);
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, C, 1);
			(*i)++;
		}	
	}
	//Para cima
	newL = L+1;	
	if((newL<8)&&(tabuleiro[newL][C].tipo == '0'))
	{
		if(VC){
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				AddToPositions(positions, (*i), 'K', newL, C, 0);
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, C, 0);
	//		AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);
			(*i)++;
		}
		
	}else
	if ((newL<8)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C)){			
				AddToPositions(positions, (*i), 'K', newL, C, 1);
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, C, 1);
			(*i)++;
		}	
	}

	//Diagonal direita inferior
	newL = L - 1;
	newC = C + 1;
	if((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'K', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, newC, 0);
	//		AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
			(*i)++;
		}		
	}else
	if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC)){			
				AddToPositions(positions, (*i), 'K', newL, newC, 1);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, newC, 1);
			(*i)++;
		}	
	}

	//Para direita
	newC = C + 1;
	if ((newC<8)&&(tabuleiro[L][newC].tipo == '0'))
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				AddToPositions(positions, (*i), 'K', L, newC, 0);
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', L, newC, 0);
	//		AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
			(*i)++;
		}
	
	}else
	if ((newC<8)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC)){			
				AddToPositions(positions, (*i), 'K', L, newC, 1);
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', L, newC, 1);
			(*i)++;
		}	
	}

	//Diagonal direita superior
	newL = L + 1;
	newC = C + 1;
	if((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				AddToPositions(positions, (*i), 'K', newL, newC, 0);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);		
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, newC, 0);
	//		AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
			(*i)++;
		}
	
	}else
	if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC)){			
				AddToPositions(positions, (*i), 'K', newL, newC, 1);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			AddToPositions(positions, (*i), 'K', newL, newC, 1);
			(*i)++;
		}	
	}
	*mov = (*i);
	if (VC)
		CheckMatrix(positions, matrix);
}
void Peao(peca** tabuleiro,int L, int C, int* mov, Edestiny** matrix, char** positions, int* i, int VC)
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
			if(VerificaCheque(tabuleiro, L, C, newL, C))
			{
				if (((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO)))//Promocao do Peao
				{					
					AddToPositionsP(positions, i, newL, C,  0, 0, 1);				
				}else {				
					AddToPositionsP(positions, i, newL, C,  0, 0, 0);										
				}			
			}	
			newL = L+2;	
			if((L==1)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==BRANCO)){
						
				if(VerificaCheque(tabuleiro, L, C, newL, C))
				{							
					AddToPositionsP(positions, i, newL, C,  0, 0, 0);
				}
			}
			newL = L-2;
			if ((L==6)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==PRETO))
			{
				if(VerificaCheque(tabuleiro, L, C, newL, C))
				{		
					AddToPositionsP(positions, i, newL, C,  0, 0, 0);				
				}
			}
		}		
		else{
			if (((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO)))//Promocao do Peao
			{
				AddToPositionsP(positions, i, newL, C,  0, 0, 1);			
			}else{
				AddToPositionsP(positions, i, newL, C,  0, 0, 0);
			}
			
			newL = L+2;	
			if((L==1)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==BRANCO)){						
				AddToPositionsP(positions, i, newL, C,  0, 0, 0);
			
			}
			newL = L-2;
			if ((L==6)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==PRETO))
			{						
				AddToPositionsP(positions, i, newL, C,  0, 0, 0);
				
			}
		}
		
	}
	//Movimentos Diagonais
	//Diagonal Esquerda
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
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				
				if ((newL<8)&&(newC >= 0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
				{
					if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){	
							AddToPositionsP(positions, i, newL, C,  newC, 1, 1);
					}else{
							AddToPositionsP(positions, i, newL, C,  newC, 1, 0);
						}
				}
			}
		}else{
			if ((newL<8)&&(newC >= 0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
			{
				if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){
						AddToPositionsP(positions, i, newL, C,  newC, 1, 1);			
				}else{
						AddToPositionsP(positions, i, newL, C,  newC, 1, 0);
					}
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
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{			
				if ((newL<8)&&(newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
				{
					if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){	
							AddToPositionsP(positions, i, newL, C,  newC, 1, 1);
					}else{
							AddToPositionsP(positions, i, newL, C,  newC, 1, 0);
						}
				}
			}
		}else{
			if ((newL<8)&&(newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
			{
				if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){
						AddToPositionsP(positions, i, newL, C,  newC, 1, 1);			
				}else{
						AddToPositionsP(positions, i, newL, C,  newC, 1, 0);
					}
			}
		}
	if (tabuleiro[L][C].coluna != '-')
	{
	//	printf("oi");
		positions[(*i)][0] = getColumn(C);
		positions[(*i)][1] = 'x';
		positions[(*i)][2] = tabuleiro[L][C].coluna;
		positions[(*i)][3] = tabuleiro[L][C].linha;
		positions[(*i)][4] = 'e';
		positions[(*i)][5] = '.';
		positions[(*i)][6] = 'p';
		positions[(*i)][7] = '.';
		positions[(*i)][8] = '\0';		
		(*i)++;
	}
	*mov = (*i);	
	if (VC)
		CheckMatrix(positions, matrix);
}

//typedef struct p peca;
//Para cada caractere, salvar na matriz 8x8 a struct correspondente a cada pe�a.
//Para espa�os em branco, a struct � NULL
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
	
					j++;				
				}		
				
			}
			if (!isNumber)
			{
				tabuleiro[i][j] = *pc;			
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
int Movimentos(char tipo, peca** tabuleiro, int lado, char* s)
{
	int mov, i, j, npos;	
	Edestiny** matrix;

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
					tabuleiro[i][j].function(tabuleiro, i, j, &mov, matrix, positions, &npos, 1);	
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
							if ((VerificaCheque(tabuleiro, 0, 4, 0, 6))&&(VerificaCheque(tabuleiro, 0, 4, 0, 5)))
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
							if ((VerificaCheque(tabuleiro, 0, 4, 0, 2))&&(VerificaCheque(tabuleiro, 0, 4, 0, 3)))
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
						if ((tabuleiro[7][1].tipo=='0')&&(tabuleiro[7][2].tipo=='0')&&(tabuleiro[7][3].tipo=='0'))
						{
							if ((VerificaCheque(tabuleiro, 7, 4, 7, 6))&&(VerificaCheque(tabuleiro, 7, 4, 7, 5)))
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
						if ((tabuleiro[7][5].tipo=='0')&&(tabuleiro[7][6].tipo=='0'))
						{
							if ((VerificaCheque(tabuleiro, 7, 4, 7, 2))&&(VerificaCheque(tabuleiro, 7, 4, 7, 3)))
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
void ConstroiString(peca** tabuleiro, char** s, char lado, int origemL, int origemC, int destL, int destC, char elpC, char elpL, int meioturno, int turnos)
{
	int i, j, zeros, k, rBK = 0, rBQ = 0, rpk = 0, rpq = 0, roque = 0;
	int tBK = 1, tBQ = 1, tpk = 1, tpq = 1;
	char str[4];
	k = 0;
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
	//ROQUE
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
		if (MovimentosCheque(tabuleiro, ladoOp, 'P', LRei, CRei))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'N', LRei, CRei))	
			return 0;		
		if (MovimentosCheque(tabuleiro, ladoOp, 'B', LRei, CRei))		
			return 0;			
		if (MovimentosCheque(tabuleiro, ladoOp, 'R', LRei, CRei))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'Q', LRei, CRei))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'K', LRei, CRei))
			return 0;
		return 1;
	}
	else{
	
		if (MovimentosCheque(tabuleiro, ladoOp, 'p', LRei, CRei))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'n', LRei, CRei))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'b', LRei, CRei))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'r', LRei, CRei))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'q', LRei, CRei))
			return 0;
		if (MovimentosCheque(tabuleiro, ladoOp, 'k', LRei, CRei))
			return 0;
		return 1;
	}
}
int main()
{

	char *s;
	char **historico;
	int i, index, k =0;
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

	peca *aux;
	peca *none;
	none = malloc(sizeof(peca));
	aux = malloc(sizeof(peca));
	none->tipo = '0';

	if (lado == BRANCO)
	{
		if (FaltaMaterial(tabuleiro))
			faltamaterial = 1;
		else
		if ((!Movimentos('P', tabuleiro, BRANCO,s))&&(!Movimentos('N', tabuleiro, BRANCO,s))&&(!Movimentos('B', tabuleiro, BRANCO,s))&&(!Movimentos('R', tabuleiro, BRANCO,s))&&(!Movimentos('Q', tabuleiro, BRANCO,s))&&(!Movimentos('K', tabuleiro, BRANCO,s)))
		{		
			if (!VerificaChequeMate(tabuleiro, BRANCO))
				chequemate = 1;
			else{			
				afogamento = 1;
			}					
		}		
	}else{
		if (FaltaMaterial(tabuleiro))
			faltamaterial = 1;
		else
		if ((!Movimentos('p', tabuleiro, PRETO,s))&&(!Movimentos('n', tabuleiro, PRETO,s))&&(!Movimentos('b', tabuleiro, PRETO,s))&&(!Movimentos('r', tabuleiro, PRETO,s))&&(!Movimentos('q', tabuleiro, PRETO,s))&&(!Movimentos('k', tabuleiro, PRETO,s)))
		{			
			if (!VerificaChequeMate(tabuleiro, PRETO))
				chequemate = 1;
			else{			
				afogamento = 1;
			}	
		}	
	}
	if ((!chequemate)&&(!afogamento)&&(!faltamaterial)&&(meioturno < 50))
	{
		scanf("%s", movimento);
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
				printf("Cheque-mate -- Vitoria: PRETO\n");						
			}else{
				printf("Cheque-mate -- Vitoria: BRANCO");
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

	while ((VerificaCheque(tabuleiro, OrigemL, OrigemC, DestL, DestC))&&(!chequemate)&&(meioturno <= 50)&&(!afogamento)&&(!faltamaterial))
	{			
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
			}
			aux->coluna =tabuleiro[OrigemL][OrigemC].coluna;
			aux->function = tabuleiro[OrigemL][OrigemC].function;
			aux->lado = tabuleiro[OrigemL][OrigemC].lado;
			aux->tipo = tabuleiro[OrigemL][OrigemC].tipo;		
			tabuleiro[OrigemL][OrigemC] = *none;
			if (tabuleiro[DestL][DestC].tipo!='0')
				captura = 1;
			tabuleiro[DestL][DestC] = *aux;

			
			//check if was an ElPassant
			if ((DestL == ((elpL - '0') - 1))&&(DestC == getIntColumn(elpC)))
			{
				tabuleiro[DestL+1][DestC].tipo = '0';
				captura = 1;
			}	
			if ((aux->tipo == 'P')||(captura)||(aux->tipo=='p'))
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
					if ((Movimentos('p', tabuleiro, PRETO,s))||(Movimentos('n', tabuleiro, PRETO,s))||(Movimentos('b', tabuleiro, PRETO,s))||(Movimentos('r', tabuleiro, PRETO,s))||(Movimentos('q', tabuleiro, PRETO,s))||(Movimentos('k', tabuleiro, PRETO,s)))
					{
						//Salva tabuleiro atual em s -> qd achar tipo 0, ir somando at� encontrar numero diferente ou final de linha					
						//-> Meio-turno: acrescenta qd o movimento n envolver captura ou pe�o, zerar qd envolver. 
						//Checar quando peao faz o movimento de duas casas - Acrescentar ElPassant					//Verificar roque				
						ConstroiString(tabuleiro, &s, 'b', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);				
						strcpy(historico[index], s);				
						index++;
						scanf("%s", movimento);
						OrigemC = getIntColumn(movimento[0]);
						OrigemL = movimento[1] - '0' - 1;
						DestC = getIntColumn(movimento[2]);
						DestL = movimento[3] - '0' - 1;
	
						
					}else if (!VerificaChequeMate(tabuleiro, PRETO)){						
						ConstroiString(tabuleiro, &s, 'b', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);				
						strcpy(historico[index], s);
						index++;
						chequemate = 1;												
					}else{
						ConstroiString(tabuleiro, &s, 'b', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);				
						strcpy(historico[index], s);
						index++;
						afogamento = 1;
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
					if ((Movimentos('P', tabuleiro, BRANCO,s))||(Movimentos('N', tabuleiro, BRANCO,s))||(Movimentos('B', tabuleiro, BRANCO,s))||(Movimentos('R', tabuleiro, BRANCO,s))||(Movimentos('Q', tabuleiro, BRANCO,s))||(Movimentos('K', tabuleiro, BRANCO,s)))
					{						
						ConstroiString(tabuleiro, &s, 'w', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);
						strcpy(historico[index], s);				
						index++;
						scanf("%s", movimento);
						OrigemC = getIntColumn(movimento[0]);
						OrigemL = movimento[1] - '0' - 1;
						DestC = getIntColumn(movimento[2]);
						DestL = movimento[3] - '0' - 1;									
					}else if (!VerificaChequeMate(tabuleiro, BRANCO)){
						ConstroiString(tabuleiro, &s, 'w', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);
						strcpy(historico[index], s);
						index++;				
						chequemate = 1;					
					}else {
						ConstroiString(tabuleiro, &s, 'w', OrigemL, OrigemC, DestL, DestC, elpC, elpL, meioturno, turno);
						strcpy(historico[index], s);
						index++;
						afogamento = 1;
					}
					
						
					
				}
				if (chequemate)
				{			
					for (i = 0; i < (index); i++)		
						printf("%s\n", historico[i]);
					if (tabuleiro[DestL][DestC].lado == BRANCO)
					{
						printf("Cheque-mate -- Vitoria: BRANCO\n");						
					}else{
						printf("Cheque-mate -- Vitoria: PRETO");
					}
				}
			}
		}
		
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
	free(s);
	free(historico);
	free(tabuleiro);
}
