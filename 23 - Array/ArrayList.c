/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 04/07/2017
*/
#include "ArrayList.h"
#include<stdio.h>
#include<stdlib.h>
typedef struct NO {
ITEM *list;//lista interna de void
int fimvet;//tamanho ocupado na lista
int tamanho;//tamanho da lista interna
int globalBeginIndex;
struct NO *next;
} NO;
struct ArrayList{
NO *inicio;
};

ArrayList *new_arrayList(){
	printf("To be implemented...");
	return NULL;
}
void add_arrayList(ArrayList **arrayList, ITEM *element){
	NO *p, *q;
	ITEM *aux;
	int added;	
        int i, j;
	p = (NO*) malloc(sizeof(NO));
	aux = (ITEM*) malloc(sizeof(NO));
	q = (NO*) malloc(sizeof(NO));
	if ((*arrayList) == NULL)
	{
		(*arrayList) = (ArrayList*) malloc(sizeof(ArrayList));
		p->fimvet = 0;
		p->tamanho = 10;
		p->globalBeginIndex = 0;
		p->next = NULL;	
		p->list = (ITEM*) malloc(sizeof(ITEM)*(p->tamanho));
		p->list[p->fimvet].chave = element->chave;
		p->list[p->fimvet].valor = element->valor;
		p->fimvet++;		
		(*arrayList)->inicio = p;
		//printf("added %d %d\n", p->list[p->fimvet].chave, p->list[p->fimvet].valor);
		return;
	}
	p = (*arrayList)->inicio;
	added = 0;
	while((p)&&(!added))
	{	
		//printf("new node %d tamanho atual %d\n", element->chave, p->fimvet);
		for (i=0; i < p->tamanho; i++)
		{
			if(p->list[i].chave > element->chave)
			{
				//printf("%d > %d\n", p->list[i].chave, element->chave);
				if(p->fimvet <= (p->tamanho-1))
				{
					//Ainda pode inserir neste no					
					for (j=p->fimvet; j > i; j--)
					{
						p->list[j] = p->list[j-1];
					}
					p->list[i].chave = element->chave;
					p->list[i].valor = element->valor;
				//	printf("added %d %d\n", p->list[i].chave, p->list[i].valor);
					p->fimvet++;
					added = 1;
					break;
				
				}else{
					p->fimvet = p->tamanho-1;
					aux->chave = p->list[p->fimvet].chave;
					aux->valor = p->list[p->fimvet].valor;  					
				//	printf("copying item from last position %d\n", p->fimvet);
					for (j=p->fimvet; j > i; j--)
					{
						p->list[j] = p->list[j-1];
					}
				//	printf ("new last item: %d\n", p->list[p->fimvet].chave);
					p->list[i].chave = element->chave;
					p->list[i].valor = element->valor;
					p->fimvet++;
					add_arrayList(arrayList, aux);
					
					added = 1;					
					break;
				}
			}
			
		}
		if (p->next)
		{
		    if (p->next->list[0].chave > element->chave){
		    	if(p->fimvet <= (p->tamanho-1))
			{
			  //  printf("Inserindo no fina\n");
			    p->list[p->fimvet].chave = element->chave;
		            p->list[p->fimvet].valor = element->valor;
			    p->fimvet++;
			    added = 1;			
			}
                     }
		}
		p = p->next;
	}
	if (!added)
	{
		p = (*arrayList)->inicio;
		while (p->next) p = p->next;		
		//last node
		//printf("Adding to last position %d %d\n", p->fimvet, p->tamanho);
		if (p->fimvet <= (p->tamanho-1))
		{	
			//printf("%d < %d\n", p->fimvet, p->tamanho-1);		
			p->list[p->fimvet].chave = element->chave;
			p->list[p->fimvet].valor = element->valor;
			p->fimvet++;
		}else{
			//printf("Creating new node\n");
			q = (NO*) malloc(sizeof(NO));
			q->fimvet = 0;
			q->tamanho = p->tamanho*2;
			q->next = NULL;
			q->list = (ITEM*) malloc(sizeof(ITEM)*q->tamanho);
			q->list[q->fimvet].chave = element->chave;
			q->list[q->fimvet].valor = element->valor;
			q->globalBeginIndex = p->globalBeginIndex + p->tamanho;
			q->fimvet++;
			p->next = q;
		}
	}
}
int clear_arrayList(ArrayList *arrayList){
	printf("To be implemented...");
	return 1;
}
ArrayList *clone_arrayList(ArrayList *arrayList){
	printf("To be implemented...");
	return NULL;
}
int contains_arrayList(ArrayList *arrayList, int chave){
	NO* p;
	int i;
	p = (NO*) malloc(sizeof(NO));
	if (arrayList == NULL)
	    return 0;	
	p = arrayList->inicio;
	while(p)
	{
	    for (i=0; i < p->fimvet; i++)	
	    {
  		if (p->list[i].chave == chave)
		   return 1;
            }
	    p = p->next;
	}
	return 0;
}
ITEM *get_arrayList(ArrayList *arrayList, int pos){
	NO* p, *q;
	int i, found;	
	ITEM* item;
	p = (NO*) malloc(sizeof(NO));
	q = (NO*) malloc(sizeof(NO));
	item = (ITEM*)malloc(sizeof(ITEM));
	q = (arrayList)->inicio;
	p = (arrayList)->inicio;
	found = 0;
	if (p->next){		
	  	p=p->next;
		if (p->globalBeginIndex > pos)
			p = q;
		else{			
			while((p->next)&&(!found)){
			    if (p->next->globalBeginIndex > pos)
				found = 1;
			     else{
				p = p->next;
				q = q->next;
			     }
			}
		}				
		i = pos - p->globalBeginIndex;		
		if ((i >=0) && (i < p->tamanho))
		{
     		   item->chave = p->list[i].chave;
	           item->valor = p->list[i].valor;
		   return item;
		}
	   		    
		return NULL;
	}
	else{	 
	   i = pos - p->globalBeginIndex;
	   if (i < p->globalBeginIndex)
	      return NULL;
	   if ((i >=0) && (i < p->tamanho))
	   {
     	       item->chave = p->list[i].chave;
	       item->valor = p->list[i].valor;
	       return item;
	    }
	    return NULL;
	}	

}
int indexOf_arrayList(ArrayList *arrayList, int chave){	
	NO* p;
	int i;
	p = (NO*) malloc(sizeof(NO));
	if (arrayList == NULL)
	    return 0;	
	p = arrayList->inicio;
	while(p)
	{
	    for (i=0; i < p->fimvet; i++)	
	    {
  		if (p->list[i].chave == chave)
		   return i + p->globalBeginIndex;
            }
	    p = p->next;
	}
	return -1;
	
}
int isEmpty_arrayList(ArrayList *arrayList){
	if (arrayList == NULL)
	    return 1;
	return 0;
}
ITEM* remove_arrayList(ArrayList **arrayList, int pos){
	int found;	
	int i;
	NO* p, *q;
	ITEM* item, *aux;
	item = (ITEM*) malloc(sizeof(ITEM));
	aux = (ITEM*) malloc(sizeof(ITEM));
	p = (NO*) malloc(sizeof(NO));
	q = (NO*) malloc(sizeof(NO));
	q = (*arrayList)->inicio;
	p = (*arrayList)->inicio;
	found = 0;
	if (p->next){
	  	p=p->next;
		if (p->globalBeginIndex > pos)
			p = q;
		else{
			
			while((p->next)&&(!found)){
			    if (p->next->globalBeginIndex > pos)
				found = 1;
			     else{
				p = p->next;
				q = q->next;
			     }
			}
		}		
		if (p->fimvet - 1 <=0)
		{
		   //libera o no
		   if (p == q){			
				//liberando o primeiro no
				item->chave = p->list[0].chave;
				item->valor = p->list[0].valor;
				(*arrayList)->inicio = (*arrayList)->inicio->next;
				free(q);
				free(p);
        	}else{			
				item->chave = p->list[0].chave;
				item->valor = p->list[0].valor;
	  			q->next = p->next;
				free(p);
		    }
		}else{		     
		     i = pos - p->globalBeginIndex;
	          //   printf("removendo item %d fimvet %d\n", i, p->fimvet);
		     if (i < p->fimvet){
				 item->chave = p->list[i].chave;
				 item->valor = p->list[i].valor;		    
				 for (i; i < p->fimvet-1; i++)
				 {
		  			p->list[i] = p->list[i+1];
			     }		
				 p->fimvet--;
				 if (p->next){							     
		   		     aux = remove_arrayList(arrayList, p->next->globalBeginIndex);				
				     add_arrayList(arrayList, aux);
			  	}	
		     }
		    	     
		}
	}else{
		if (pos < p->tamanho)
		{
		   if (p->fimvet - 1 <= 0)
		   {
				item->chave = p->list[0].chave;
			    item->valor = p->list[0].valor;
	 			free((*arrayList)->inicio);
				(*arrayList) = NULL;
				free(p);
				free(q);
		   }else
		   {			 
			 i = pos - p->globalBeginIndex;			
			 if (i < p->fimvet){
				 item->chave = p->list[i].chave;
				 item->valor = p->list[i].valor;
				 for (i; i < p->fimvet-1; i++)
				 {
		  		    p->list[i] = p->list[i+1];
				 }
				 p->fimvet--;	
			 }
		   } 
		}
	}	
	//printf("removing item %d %d\n", item->chave, item->valor);
	return item;
}
void set_arrayList(ArrayList **arrayList, int pos, ITEM *element){

	remove_arrayList(arrayList, pos);
	add_arrayList(arrayList, element);
	
}
int size_arrayList(ArrayList *arrayList){
	int size = 0;
	NO* p;
	p = (NO*) malloc(sizeof(NO));
	p = arrayList->inicio;
	while(p->next){
	   size+=p->tamanho;
	   p = p->next;  
	}
	size+=p->fimvet;
	return size;
}
ArrayList *subArray_arrayList(ArrayList *arrayList, int beginIndex, int endIndex){
	ArrayList* array = NULL;
	NO* p, *q;
	ITEM* item;	
	int i, found;
	item = (ITEM*) malloc(sizeof(ITEM));
	q = (NO*) malloc(sizeof(NO));
	p = (NO*) malloc(sizeof(NO));
	q = (arrayList)->inicio;
	p = (arrayList)->inicio;
	found = 0;
	if (p->next){
	  	p=p->next;
		if (p->globalBeginIndex > beginIndex)
			p = q;
		else{
			//printf("not in first node\n");
			while((p->next)&&(!found)){
			    if (p->next->globalBeginIndex > beginIndex)
				found = 1;
			     else{
				p = p->next;
				q = q->next;
			     }
			}
		}		
		i= beginIndex - p->globalBeginIndex;
		found = 0;
		while(!found)
		{
  		   if (endIndex - p->globalBeginIndex < p->tamanho)
		   {	
			//same node	
				for (i; i < endIndex-p->globalBeginIndex;i++){
					item->chave = p->list[i].chave;
					item->valor = p->list[i].valor;
					add_arrayList(&array, item);
				}
				found = 1;
		    }else
		     {
	  			for (i; i < p->fimvet; i++)
				{
				   item->chave = p->list[i].chave;
				   item->valor = p->list[i].valor;
				    add_arrayList(&array, item); 
				}
				i = 0;
				p = p->next;
        	}			
		}	      	
	}else{
	    i= beginIndex - p->globalBeginIndex;
	    if (endIndex - p->globalBeginIndex < p->globalBeginIndex)
	    {	
		//same node	
			for (i; i < endIndex-p->globalBeginIndex;i++){
				item->chave = p->list[i].chave;
				item->valor = p->list[i].valor;
				add_arrayList(&array, item);
			}
	     }
	}
	return array;
}
int destruct_arrayList(ArrayList **arrayList){
	printf("To be implemented...");
	return 1;
}
void print_arrayList(ArrayList *arrayList){
	NO *paux;
	int i = 0;
	for(paux = arrayList->inicio; paux != NULL; paux = paux->next){
		for(i=0; i<paux->fimvet; ++i){
			printf("%d: ", paux->globalBeginIndex + i);
			printf("%d/%d\n", paux->list[i].chave,paux->list[i].valor);
			
		}
		printf("\n\n");
	}	
}
