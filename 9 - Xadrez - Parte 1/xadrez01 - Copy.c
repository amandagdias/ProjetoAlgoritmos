/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 09/05/2017
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
					for (k=0 ; k < mov; k++)
					{
							linha = positions[k][strlen(positions[k])-1] - 1 -'0';
							coluna = (int) getIntColumn(positions[k][strlen(positions[k])-2]);
							
							if ((linha == LRei)&&(coluna == CRei)){					
								return 1;
							}
					}
					npos=0;
								
				}			
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
		if (MovimentosCheque(copy, ladoOp, 'N', LRei, CRei)){		
			return 0;
		}
		if (MovimentosCheque(copy, ladoOp, 'B', LRei, CRei)){		
			return 0;
		}			
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
void D(peca** tabuleiro, int L, int C, char** positions, int* m, int* i, Edestiny** matrix, char tipo, int VC)
{
	int newL, newC;

	
	//Diagnoal esquerda inferior
	newL = L - 1;
	newC = C - 1;
	if (VC)
	{
		while  ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);
				newC--;
				newL--;
				(*i)++;
			}				
		}
		if ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;
			}			
		}
	}else{
		while  ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
		{
		
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);
				newC--;
				newL--;
				(*i)++;
							
		}
		if ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
		{
			
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;
						
		}
	}
	//Diagonal esquerda superior
	newL = L + 1;
	newC = C - 1;
	if (VC)
	{
		while  ((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);
				newC--;
				newL++;
				(*i)++;
			}
		
		}
		if ((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;
			}			
		}
	}else{
		while  ((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL + 1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);
			newC--;
			newL++;
			(*i)++;
		}
		if ((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
			(*i)++;
		}
	}
	
	//Diagonal direita inferior
	newL = L - 1;
	newC = C + 1;
	if (VC)
	{
		while  ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);
				newC++;
				newL--;
				(*i)++;
			}
			
		}
		if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;
			}			
		}
	}else{
		while  ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].tipo == '0'))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL + 1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);
			newC++;
			newL--;
			(*i)++;
		}
		if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
			(*i)++;
		}
	}
	

	//Diagonal direita superior
	newL = L + 1;
	newC = C + 1;
	if (VC)
	{
		while  ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);
				newC++;
				newL++;
				(*i)++;
			}
		}
		if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
				(*i)++;
			}
		
		}
	}else{
		while  ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].tipo == '0'))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL + 1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 0);
			newC++;
			newL++;
			(*i)++;
		}
		if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, newC, (*i), tipo, 1);
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
	if (VC)
	{
		while  ((newC>=0)&&(tabuleiro[L][newC].tipo == '0'))
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (L+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);
				newC--;
				(*i)++;
			}
		}
		if ((newC>=0)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{				
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (L + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 1);
				(*i)++;
			}		
		}
	}else{
		while  ((newC>=0)&&(tabuleiro[L][newC].tipo == '0'))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (L+1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);
			newC--;
			(*i)++;
		}
		if ((newC>=0)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (L + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 1);
			(*i)++;
		}
	}
	
	//Para baixo
	newL = L - 1;
	if (VC)
	{
		while  ((newL>=0)&&(tabuleiro[newL][C].tipo == '0'))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);
				newL--;
				(*i)++;			
			}
			
		}
		if ((newL>=0)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(C);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 1);
				(*i)++;
			}
		}
	}else{
		while  ((newL>=0)&&(tabuleiro[newL][C].tipo == '0'))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = getColumn(C);
			positions[(*i)][2] = (newL + 1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);
			newL--;
			(*i)++;
		}
		if ((newL>=0)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(C);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 1);
			(*i)++;
		}
	}


	//Para cima
	newL = L+1;	
	if (VC)
	{
		while  ((newL<8)&&(tabuleiro[newL][C].tipo == '0'))
		{	if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);
				newL++;
				(*i)++;
			}
			
		}
		if ((newL<8)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(C);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 1);
				(*i)++;
			}
		}
	}else{
		while  ((newL<8)&&(tabuleiro[newL][C].tipo == '0'))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = getColumn(C);
			positions[(*i)][2] = (newL + 1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 0);
			newL++;
			(*i)++;
		}
		if ((newL<8)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(C);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, C, (*i), tipo, 1);
			(*i)++;
		}
	}

	//Para direita
	newC = C + 1;
	if(VC)
	{
		while  ((newC<8)&&(tabuleiro[L][newC].tipo == '0'))
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (L + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);
				newC++;
				(*i)++;
			}
		}
		if ((newC<8)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{				
				positions[(*i)][0] = tipo;
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (L + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 1);
				(*i)++;
			}
		
		}
	}else{
		while  ((newC<8)&&(tabuleiro[L][newC].tipo == '0'))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (L + 1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 0);
			newC++;
			(*i)++;
		}
		if ((newC<8)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))
		{
			positions[(*i)][0] = tipo;
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (L + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, L, newC, (*i), tipo, 1);
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
				positions[(*i)][0] =  'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
				(*i)++;
			}
		}else{		
			positions[(*i)][0] =  'N';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL + 1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
			(*i)++;
		}
	}else
	if ((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
				(*i)++;
			}
		}
		else{
			positions[(*i)][0] = 'N';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 1);
			(*i)++;
		}
	}
	//Duas para a esquerda uma para cima
	newL = L + 1;
	newC = C - 2;
	if((newL < 8)&&(newC >= 0)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'N';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL + 1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i),  'N', 0);
			(*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);	
				(*i)++;
			}
		}
		else{
			positions[(*i)][0] = 'N';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);	
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
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1)+ '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N',0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'N';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL + 1)+ '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'N',0);
			(*i)++;
		}
	
	}else
	if ((newL >= 0)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'N';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
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
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
			}
		}else{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC >=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
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
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i),'N',0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i),'N',0);
				(*i)++;
		}
			
		
	}else
	if ((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
				(*i)++;			
			}
		}else{
			positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
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
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1)+ '0';
				positions[(*i)][3] = '\0';
			//	printf("\n p: %d\n", i);
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'N';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL + 1)+ '0';
			positions[(*i)][3] = '\0';
		//	printf("\n p: %d\n", i);
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
			(*i)++;
		}
		
	}else
	if ((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
					positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
				(*i)++;
			}
		}else{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
				(*i)++;
		}
	
	}
	//Duas para a direita uma para baixo
	newL = L - 1;
	newC = C + 2;
	if((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].tipo=='0'))
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
			}
		}
		else{
			positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;
		}
	}else
	if ((newL >= 0)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{	
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{	
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
				(*i)++;			
			}
		}else{
			positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
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
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;		
			}
		}else{
			positions[(*i)][0] = 'N';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 0);
				(*i)++;	
		}
		
	}else
	if ((newL < 8)&&(newC < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if(VerificaCheque(tabuleiro, L, C, newL, newC))
			{
					positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
				(*i)++;		
			}
		}else{
				positions[(*i)][0] = 'N';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'N', 1);
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
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL+1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
			(*i)++;
		}
		
		
	}else
	if ((newC>=0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)			
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC)){
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
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
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (L+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (L+1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
			(*i)++;
		}
		
	}else
	if ((newC>=0)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (L + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 1);
				(*i)++;
			}
		}
		else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (L + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 1);
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
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				(*i)++;
			}
		}
		else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL+1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
			(*i)++;
		}
	}else
	if ((newC >= 0)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
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
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);
				newL--;
				(*i)++;
			}
		}
		else{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);
				newL--;
				(*i)++;
		}
	}else
	if ((newL>=0)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))	
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(C);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 1);
				(*i)++;
			}
		}else{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(C);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 1);
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
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1) + '0';
				positions[(*i)][3] = '\0';	
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = getColumn(C);
			positions[(*i)][2] = (newL+1) + '0';
			positions[(*i)][3] = '\0';	
			AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 0);
			(*i)++;
		}
		
	}else
	if ((newL<8)&&(tabuleiro[newL][C].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, C))
			{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(C);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(C);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, C, (*i), 'K', 1);
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
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (newL+1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
			(*i)++;
		}
		
	}else
	if ((newC < 8)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (newL + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
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
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (L+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = getColumn(newC);
			positions[(*i)][2] = (L+1) + '0';
			positions[(*i)][3] = '\0';
			AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 0);
			(*i)++;
		}
	
	}else
	if ((newC<8)&&(tabuleiro[L][newC].lado != tabuleiro[L][C].lado))	
	{
		if (VC)
		{
			if (VerificaCheque(tabuleiro, L, C, L, newC))
			{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (L + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
			positions[(*i)][1] = 'x';
			positions[(*i)][2] = getColumn(newC);
			positions[(*i)][3] = (L + 1) + '0';
			positions[(*i)][4] = '\0';	
			AddToMatrix(matrix, L, C, L, newC, (*i), 'K', 1);
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
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
		
				(*i)++;
			}
		}else{
			positions[(*i)][0] = 'K';
				positions[(*i)][1] = getColumn(newC);
				positions[(*i)][2] = (newL+1) + '0';
				positions[(*i)][3] = '\0';
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 0);
		
				(*i)++;
		}
	
	}else
	if ((newC < 8)&&(newL < 8)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado))	
	{
		if(VC)
		{
			if (VerificaCheque(tabuleiro, L, C, newL, newC))
			{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
				(*i)++;
			}
		}else{
				positions[(*i)][0] = 'K';
				positions[(*i)][1] = 'x';
				positions[(*i)][2] = getColumn(newC);
				positions[(*i)][3] = (newL + 1) + '0';
				positions[(*i)][4] = '\0';	
				AddToMatrix(matrix, L, C, newL, newC, (*i), 'K', 1);
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
					positions[(*i)][0] = getColumn(C);
					positions[(*i)][1] = getColumn(C);
					positions[(*i)][2] = (newL + 1) + '0';
					positions[(*i)][3] = 'N';
					positions[(*i)][4] = '\0';
					(*i)++;
					positions[(*i)][0] = getColumn(C);
					positions[(*i)][1] = getColumn(C);
					positions[(*i)][2] = (newL+1)+ '0';
					positions[(*i)][3] = 'B';
					positions[(*i)][4] = '\0';
					(*i)++;
					
					positions[(*i)][0] = getColumn(C);
					positions[(*i)][1] = getColumn(C);
					positions[(*i)][2] = (newL+1)+ '0';
					positions[(*i)][3] = 'R';
					positions[(*i)][4] = '\0';
					(*i)++;
					
					positions[(*i)][0] = getColumn(C);
					positions[(*i)][1] = getColumn(C);
					positions[(*i)][2] = (newL+1)+ '0';
					positions[(*i)][3] = 'Q';
					positions[(*i)][4] = '\0';
					(*i)++;
				}else {				
					positions[(*i)][0] = getColumn(C);
					positions[(*i)][1] = getColumn(C);
					positions[(*i)][2] = (newL+1)+ '0';
					positions[(*i)][3] = '\0';
					(*i)++;					
					
				}
			
			}	
			newL = L+2;	
			if((L==1)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==BRANCO)){
						
				if(VerificaCheque(tabuleiro, L, C, newL, C))
				{							
					positions[(*i)][0] = getColumn(C);
					positions[(*i)][1] = getColumn(C);
					positions[(*i)][2] = (newL+1)+ '0';
					positions[(*i)][3] = '\0';
					(*i)++;
				}
			}
			newL = L-2;
			if ((L==6)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==PRETO))
			{
				if(VerificaCheque(tabuleiro, L, C, newL, C))
				{		
					positions[(*i)][0] = getColumn(C);
					positions[(*i)][1] = getColumn(C);
					positions[(*i)][2] = (newL+1)+ '0';
					positions[(*i)][3] = '\0';
					(*i)++;
				}
			}
		}		
		else{
			if (((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO)))//Promocao do Peao
			{
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL + 1) + '0';
				positions[(*i)][3] = 'N';
				positions[(*i)][4] = '\0';
				(*i)++;
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1)+ '0';
				positions[(*i)][3] = 'B';
				positions[(*i)][4] = '\0';
				(*i)++;
					
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1)+ '0';
				positions[(*i)][3] = 'R';
				positions[(*i)][4] = '\0';
				(*i)++;
					
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1)+ '0';
				positions[(*i)][3] = 'Q';
				positions[(*i)][4] = '\0';
				(*i)++;
			}else{
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1)+ '0';
				positions[(*i)][3] = '\0';
				(*i)++;
			}
			
			newL = L+2;	
			if((L==1)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==BRANCO)){						
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1)+ '0';
				positions[(*i)][3] = '\0';
				(*i)++;
			
			}
			newL = L-2;
			if ((L==6)&&(tabuleiro[newL][C].tipo=='0')&&(tabuleiro[L][C].lado==PRETO))
			{						
				positions[(*i)][0] = getColumn(C);
				positions[(*i)][1] = getColumn(C);
				positions[(*i)][2] = (newL+1)+ '0';
				positions[(*i)][3] = '\0';
				(*i)++;
				
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
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';
							positions[(*i)][4] = 'N';	
							positions[(*i)][5] = '\0';
							(*i)++;
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';
							positions[(*i)][4] = 'B';	
							positions[(*i)][5] = '\0';
							(*i)++;
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';
							positions[(*i)][4] = 'R';	
							positions[(*i)][5] = '\0';
							(*i)++;
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';
							positions[(*i)][4] = 'Q';	
							positions[(*i)][5] = '\0';
							(*i)++;
						}else{
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';								
							positions[(*i)][4] = '\0';
							(*i)++;
						}
				}
			}
		}else{
			if ((newL<8)&&(newC >= 0)&&(newL>=0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
			{
				if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){			
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = 'N';	
						positions[(*i)][5] = '\0';
						(*i)++;
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = 'B';	
						positions[(*i)][5] = '\0';
						(*i)++;
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = 'R';	
						positions[(*i)][5] = '\0';
						(*i)++;
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = 'Q';	
						positions[(*i)][5] = '\0';
						(*i)++;
					}else{
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';							
						positions[(*i)][4] = '\0';
						(*i)++;
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
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';
							positions[(*i)][4] = 'N';	
							positions[(*i)][5] = '\0';
							(*i)++;
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';
							positions[(*i)][4] = 'B';	
							positions[(*i)][5] = '\0';
							(*i)++;
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';
							positions[(*i)][4] = 'R';	
							positions[(*i)][5] = '\0';
							(*i)++;
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';
							positions[(*i)][4] = 'Q';	
							positions[(*i)][5] = '\0';
							(*i)++;
						}else{
							positions[(*i)][0] = getColumn(C);
							positions[(*i)][1] = 'x';
							positions[(*i)][2] = getColumn(newC);
							positions[(*i)][3] = (newL+1)+ '0';								
							positions[(*i)][4] = '\0';
							(*i)++;
						}
				}
			}
		}else{
			if ((newL<8)&&(newC >= 0)&&(tabuleiro[newL][newC].lado != tabuleiro[L][C].lado)&&(tabuleiro[(newL)][newC].tipo!='0'))
			{
				if(((newL == 7)&&(tabuleiro[L][C].lado==BRANCO))||((newL == 0)&&(tabuleiro[L][C].lado==PRETO))){			
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = 'N';	
						positions[(*i)][5] = '\0';
						(*i)++;
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = 'B';	
						positions[(*i)][5] = '\0';
						(*i)++;
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = 'R';	
						positions[(*i)][5] = '\0';
						(*i)++;
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = 'Q';	
						positions[(*i)][5] = '\0';
						(*i)++;
					}else{
						positions[(*i)][0] = getColumn(C);
						positions[(*i)][1] = 'x';
						positions[(*i)][2] = getColumn(newC);
						positions[(*i)][3] = (newL+1)+ '0';
						positions[(*i)][4] = '\0';
						(*i)++;
					}
			}
		}	
	*mov = (*i);	
	if (VC)
		CheckMatrix(positions, matrix);
}

//typedef struct p peca;
//Para cada caractere, salvar na matriz 8x8 a struct correspondente a cada peça.
//Para espaços em branco, a struct é NULL
//Salvar quem joga
void PreencherTabuleiro(peca** tabuleiro, char* s)
{
	peca *pc;
	int i, j, k, n;
	i = 7;
	j=0;
	k= 0;
	int isNumber = 0;
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
			}
			else if (s[k]=='P')
			{
				pc->tipo = 'P';
				pc->lado = BRANCO;
				pc->function = &Peao;
			}
			else{
				//it is a number
				isNumber = 1;
				pc->tipo = '0';
		//		printf("s: %c", s[k]);
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
void Movimentos(char tipo, peca** tabuleiro, int lado, char* s)
{
	int mov, i, j, npos, k;
	int* used;
	int* npos_array;
	int c, start;
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
	c=0;
	npos_array = (int*) malloc(sizeof(int)*100);
	npos=0;
		for (j=0; j < 8; j++)
		{
			for (i=0; i < 8; i ++)
			{
	
				if((tabuleiro[i][j].lado == lado)&&(tabuleiro[i][j].tipo==tipo))
				{
					mov = 0;
					tabuleiro[i][j].function(tabuleiro, i, j, &mov, matrix, positions, &npos, 1);
					if(c==0)
						npos_array[c] = mov;
					else
						npos_array[c] = abs(npos_array[c-1] - mov);
					c++;
					if ((tipo=='B')||(tipo=='Q')||(tipo=='b')||(tipo=='q')||(tipo=='p')||(tipo=='P')){									
						used = (int*) calloc(npos, sizeof(int));
						for (k=0; k < npos; k++)	
						{									
							printf("%s\n", OrdenaPositions(positions, npos, 0, &used, tipo));											
						}		
						npos = 0;
					}	
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
						if (VerificaCheque(tabuleiro, 0, 4, 0, 6))
						{
							if ((tabuleiro[0][5].tipo=='0')&&(tabuleiro[0][6].tipo=='0'))
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
							if (VerificaCheque(tabuleiro, 0, 4, 0, 2))
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
							if (VerificaCheque(tabuleiro, 7, 4, 7, 6))
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
							if (VerificaCheque(tabuleiro, 7, 4, 7, 2))
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
			used = (int*) calloc(npos, sizeof(int));
			for (i=0; i < npos; i++)
				printf("%s\n", OrdenaPositions(positions, npos, 0 , &used, tipo));
		}else
		if ((tipo=='R')||(tipo=='r'))
		{
			start = 0;
			
			for(i=0; i < c; i++)
			{		
			
				used = (int*) calloc(npos, sizeof(int));
		
				for (j=0; j < npos_array[i]; j++){					
					printf("%s\n", OrdenaPositions(positions, npos_array[i] + start, start , &used, tipo));
				}
					
				start+=npos_array[i];
			}
			
		}else if ((tipo!='B')&&(tipo!='Q')&&(tipo!='b')&&(tipo!='q')&&(tipo!='P')&&(tipo!='p')){	
	
			for (i=0; i < npos; i++){
				printf("%s\n", positions[i]);
			}	
		}
	
}
int main()
{

	char s[100];
	int i;
	peca **tabuleiro;

	int lado;

	tabuleiro = (peca**) malloc(sizeof(peca*)*8);
	
	for (i = 0; i < 8; i++)
	{
		tabuleiro[i] = (peca*) malloc(sizeof(peca)*8);
	}
	scanf(" %[^\n]", s);

	PreencherTabuleiro(tabuleiro, s);
	i=0;
	while(s[i]!=' ')
		i++;
	i++;
	if (s[i]=='w')
		lado = BRANCO;
	else
		lado = PRETO;
	i+=2;

	i++;

	if (lado == BRANCO)
	{
		Movimentos('P', tabuleiro, lado,s);
		Movimentos('N', tabuleiro, lado,s);
		Movimentos('B', tabuleiro, lado,s);	
		Movimentos('R', tabuleiro, lado,s);
		Movimentos('Q', tabuleiro, lado,s);
		Movimentos('K', tabuleiro, lado,s);
	}
	else{
		Movimentos('p', tabuleiro, lado,s);
		Movimentos('n', tabuleiro, lado,s);
		Movimentos('b', tabuleiro, lado,s);	
		Movimentos('r', tabuleiro, lado,s);
		Movimentos('q', tabuleiro, lado,s);
		Movimentos('k', tabuleiro, lado,s);
	}
	

	
}
