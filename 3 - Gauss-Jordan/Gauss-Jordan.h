/*
Nome: Amanda Gonçalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 24/03/2017
*/

#ifndef _H_GaussJordan 	
#define _H_GaussJordan 

double* GaussJordan(double** M, double* B, int kA);
void trocar_linhas(double **A, int linhaVelha, int linhaNova, int kA, int kB);
void readfromfile(double** A, double* B, int kA);

#endif
