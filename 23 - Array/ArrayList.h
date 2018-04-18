/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 04/07/2017
*/
#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include "item.h"
typedef struct ArrayList ArrayList;
//Cria a ArrayList e aloca toda mem´oria necessaria
ArrayList *new_arrayList();
//adiciona elemento ao arraylist
void add_arrayList(ArrayList **arrayList, ITEM *element);
//verifica no arraylist se existe um elemento com a chave informada
int contains_arrayList(ArrayList *arrayList, int chave);
//recupera um ITEM na posicao informada
ITEM *get_arrayList(ArrayList *arrayList, int pos);
//retorna qual a posicao do primeiro elemento com a chave informada
int indexOf_arrayList(ArrayList *arrayList, int chave);
//verifica se o arraylist esta vazio
int isEmpty_arrayList(ArrayList *arrayList);
//remove um elemento do arraylist
ITEM* remove_arrayList(ArrayList **arrayList, int pos);
//modifica um elemento do arraylist
void set_arrayList(ArrayList **arrayList, int pos, ITEM *element);
//retorna o tamanho total do arraylist
int size_arrayList(ArrayList *arrayList);
//recupera um novo subarray no intervalo [beginIndex, endIndex[
ArrayList *subArray_arrayList(ArrayList *arrayList, int beginIndex,
int endIndex);
//desaloca memoria alocada pelo arraylist
int destruct_arrayList(ArrayList **arrayList);
//imprime toda a lista
void print_arrayList(ArrayList *arrayList);
#endif
