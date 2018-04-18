#include <stdlib.h>
#include <stdio.h>
#include "matriz_esparsa.h"
typedef struct CELULA {
	int linha;
	int coluna;
	int valor;
	struct CELULA *direita;
	struct CELULA *abaixo;
} CELULA;
struct matriz_esparsa {
	CELULA **linhas;
	CELULA **colunas;
	int nr_linhas;
	int nr_colunas;
};
MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas) {
	MATRIZ_ESPARSA *mat = (MATRIZ_ESPARSA *) malloc(sizeof (MATRIZ_ESPARSA));
	if (mat != NULL) {
		int i;
		mat->nr_colunas = nr_colunas;
		mat->nr_linhas = nr_linhas;
		mat->colunas = (CELULA **) malloc(sizeof (CELULA *) * nr_colunas);
		mat->linhas = (CELULA **) malloc(sizeof (CELULA *) * nr_linhas);
		if (mat->colunas != NULL && mat->linhas != NULL) {
			for (i = 0; i < nr_colunas; i++) {
				mat->colunas[i] = (CELULA *) malloc(sizeof (CELULA));
				mat->colunas[i]->abaixo = NULL;
			}
			for (i = 0; i < nr_linhas; i++) {
				mat->linhas[i] = (CELULA *) malloc(sizeof (CELULA));
				mat->linhas[i]->direita = NULL;
			}
		}
	}
	return mat;
}
void apagar_matriz(MATRIZ_ESPARSA **matriz) {
	int i;
	for (i = 0; i < (*matriz)->nr_linhas; i++) {
		CELULA *paux = (*matriz)->linhas[i]->direita;
		while (paux != NULL) {
			CELULA *prem = paux;
			paux = paux->direita;
			free(prem);
		}
		free((*matriz)->linhas[i]);
	}
	free((*matriz)->linhas);
	free((*matriz)->colunas);
	free((*matriz));
	*matriz = NULL;
}
int set_matriz(MATRIZ_ESPARSA *matriz, int lin, int col, int val) {
	if (lin < matriz->nr_linhas && col < matriz->nr_colunas) {		
		CELULA *paux = matriz->linhas[lin];
		while (paux->direita != NULL && paux->direita->coluna <= col) {
			paux = paux->direita;
		}
		if (paux->coluna == col) {
			paux->valor = val;
			paux->direita = NULL;
		} else {
			CELULA *pnovo = (CELULA *) malloc(sizeof (CELULA));
			if (pnovo != NULL) {
				pnovo->linha = lin;
				pnovo->coluna = col;
				pnovo->valor = val;
				pnovo->direita = paux->direita;
				paux->direita = pnovo;
				paux = matriz->colunas[col];
				while (paux->abaixo != NULL && paux->abaixo->linha <= lin) {
					paux = paux->abaixo;
				}
				pnovo->abaixo = paux->abaixo;
				paux->abaixo = pnovo;
			}
		}
		return 1;
	}
	return 0;
}
int get_matriz(MATRIZ_ESPARSA *matriz, int lin, int col) {
	if (lin < matriz->nr_linhas && col < matriz->nr_colunas) {
		CELULA *paux = matriz->linhas[lin];
		while (paux->direita != NULL && paux->direita->coluna <= col) {
			paux = paux->direita;
		}
		if (paux->coluna == col) {
			return paux->valor;
		}
	}
	return 0;
}
MATRIZ_ESPARSA *multiplicar_matriz(MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2) {
	MATRIZ_ESPARSA* C;
	int i,j, r; 
	int valor = 0;
	C = criar_matriz(m1->nr_linhas, m2->nr_colunas);
	
	for (i=0; i < m1->nr_linhas; i++)
	{		
		for (j=0; j <  m2->nr_colunas; j++)
		{
			valor = 0;
			for (r=0; r <  m1->nr_colunas; r++)
			{				
				valor += get_matriz(m1, i ,r)*get_matriz(m2, r, j);
			}
			if (valor != 0)
			{			
				set_matriz(C, i, j, valor);
			}
			
		}
	}	
	return C;
}
MATRIZ_ESPARSA *somar_matriz(MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2) {
	int i, j;
	int valor;
	MATRIZ_ESPARSA* C;

	C = criar_matriz(m1->nr_linhas, m1->nr_colunas);

	for (i=0; i < m1->nr_linhas; i++)
	{
		for (j=0; j < m1->nr_colunas; j++)
		{
			valor = get_matriz(m1, i, j) + get_matriz(m2, i, j);
			if (valor!=0)
			{
				set_matriz(C, i, j, valor);
			}
		}
	}
	return C;
}
void imprimir_matriz(MATRIZ_ESPARSA *matriz) {
	int i;
	CELULA *paux;
	printf("-1 %d %d\n", matriz->nr_linhas, matriz->nr_colunas);
	for (i = 0; i < matriz->nr_linhas; i++) {
		for (paux = matriz->linhas[i]; paux != NULL; paux = paux->direita) {
			printf("%d %d %d\n", paux->linha, paux->coluna, paux->valor);
		}
	}
}
