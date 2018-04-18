/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 04/07/2017
*/
#include "ArrayList.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	ITEM *item;
	//FILE* file;
	char str[50];
	int valor, pos, index;
	ArrayList*  array, *array_aux;	
	array = NULL;
	item = (ITEM*) malloc(sizeof(ITEM));
	//file = fopen("Casos_FILES/1.in","r");
	
	while(strcmp(str, "sair")!=0) {
		scanf("%s", str);		
		if (strcmp(str, "add")==0)
		{
		   scanf("%d %d", &item->chave, &item->valor);
		   add_arrayList(&array, item);     
		}else
		     if (strcmp(str, "print")==0)
		         print_arrayList(array);
		     else 
			 	if (strcmp(str, "tamanho")==0)
			   		printf("%d\n", size_arrayList(array));
		     	else 
				 	if (strcmp(str, "sub") == 0)
			  		{
					    scanf("%d %d", &item->chave, &item->valor);
		 			    array_aux = subArray_arrayList(array, item->chave, item->valor);
					    print_arrayList(array_aux);
					    free(array_aux);
                    }
			  		else 
					  	if (strcmp(str, "set") ==0)
			       		{
	         			   	scanf("%d %d %d", &item->chave, &item->valor, &valor);
				           	pos = item->chave;
					   		item->chave = item->valor;
					   		item->valor = valor;				   
					   		set_arrayList(&array, pos, item);
						}
						else 
							if (strcmp(str, "vazia")==0)
							{ 
			 				    printf("%d\n", isEmpty_arrayList(array));
							}
							else
								if (strcmp(str, "contem")==0){
								    scanf("%d", &item->chave);
								    printf("%d\n", contains_arrayList(array, item->chave));
								}
								else 
									if (strcmp(str, "indice")==0){	
									    scanf("%d", &item->chave);	 		
									    index =  indexOf_arrayList(array, item->chave);
									    if (index !=-1)
									    	printf("%d\n",index);
									}
									else 
										if (strcmp(str, "get") ==0)
										{
										    scanf("%d", &item->chave);
										    item = get_arrayList(array, item->chave);
										    if (item!=NULL)
											    printf("%d/%d\n", item->chave, item->valor);
											else{
												item = (ITEM*) malloc(sizeof(ITEM));
											}
						                }
										else 
											if (strcmp(str,"remover")==0)
											{
											    scanf("%d", &item->chave);
											    remove_arrayList(&array, item->chave);
											}
				
	}		
}
