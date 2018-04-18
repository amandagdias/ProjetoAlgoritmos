/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 30/06/2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef struct caminhos{
	int index;
	float x;
	float y;
	int nemp;
	struct caminhos* next;
	struct caminhos* prev;	
	
}CAMINHOS;
typedef struct{
	CAMINHOS* cam;
	int num;
	int dist;
}SOLUCAO;
typedef struct pilha{
	int index;
	struct pilha* next;
	
}PILHA;
typedef struct{
	float x;
	float y;
}PONTO;
typedef struct{
	int v;
	int n; 
	int o;
	
}CAMARA;
typedef struct{
	int b;
	int e;
	float d;
}SEGMENTOS;
float Distancia(CAMINHOS* P1, CAMINHOS* P2)
{
   float dist;
   dist = powf((P2->x - P1->x),2) + powf((P2->y - P1->y), 2);
   dist = sqrtf(dist);
   return dist;
}
void swap(SOLUCAO* sol,int i, int j)
{ 
   SOLUCAO* aux; 
   CAMINHOS *p, *q;
   p = (CAMINHOS*) malloc(sizeof(CAMINHOS));
   q = (CAMINHOS*) malloc(sizeof(CAMINHOS));
   aux = (SOLUCAO*)malloc(sizeof(SOLUCAO));
   aux->cam = (CAMINHOS*) malloc (sizeof(CAMINHOS)); 
   aux->dist = sol[j].dist;
   aux->num = sol[j].num;
   //printf("troca %d %d\n",j, i);
   p = (sol[j].cam);
   aux->cam->index = p->index;
   aux->cam->x = p->x; 
   aux->cam->y = p->y;
   aux->cam->next = p->next;
   aux->cam->prev = p->prev;
   q = aux->cam;
   p=p->next;
  // printf("lista:\n");
   while (p)
   {
	q->next = (CAMINHOS*) malloc(sizeof(CAMINHOS));
	//printf("%d ", p->index+1);
	q->next->index = p->index;
	q->next->x = p->x;
	q->next->y = p->y;
	q->next->next = p->next;
	q->next->prev = p->prev;		
	p=p->next;
	q = q->next;		
    }  
    //printf("\n");   
    sol[j] = sol[i];
    sol[i] = *aux;
}
void Ordenar_Solucao(SOLUCAO* sol, int nsol)
{
   int i, j;
   
   CAMINHOS *p, *q;
   p = (CAMINHOS*) malloc(sizeof(CAMINHOS));
   q = (CAMINHOS*) malloc(sizeof(CAMINHOS));
   for (i=0; i < nsol; i++)
   {
      for (j=i+1;j<nsol;j++)
      {
	  
          if(sol[j].dist < sol[i].dist)
	  {
	    swap(sol, i, j);
	   
          }else if (sol[j].dist == sol[i].dist){
	      if(sol[j].num < sol[i].num) 
	      {
		  swap(sol, i, j);
              }else if(sol[j].num == sol[i].num) 
		{
		   p = sol[j].cam;
		   q = sol[i].cam;
	           while((p)&&(q))
		   {
                      if (p->index < q->index)
		      {
			  swap(sol, i, j);
			  break;
                      }
		      p=p->next;
		      q=q->next;
		   }
		}
	   }
      }
   }
}
void Mostrar_Solucao(SOLUCAO* sol, int nsol)
{
   int i=0;
   CAMINHOS* p;
   p = (CAMINHOS*) malloc(sizeof(CAMINHOS));
   Ordenar_Solucao(sol, nsol);
   for (i=0; i < nsol; i++)
   {
        p = sol[i].cam;
	printf("%d ",sol[i].num);
	while (p)
	{
		printf("%d ", p->index+1);
		p=p->next;		
	}
	printf("%d ",sol[i].dist);
	printf("\n");
   }
 	
}
void Salvar_Solucao(CAMINHOS* head, SOLUCAO* sol, int index, CAMINHOS** sol_head)
{
	CAMINHOS* p;
	CAMINHOS* q;
	float dist;
	p = (CAMINHOS*) malloc(sizeof(CAMINHOS));	
	q = (CAMINHOS*)malloc(sizeof(CAMINHOS));	
	p = head;
	
	(*sol_head)->index = p->index;
	(*sol_head)->x = p->x;
	(*sol_head)->y = p->y;
	(*sol_head)->next = p->next;
	(*sol_head)->prev = p->prev;	    
	q = (*sol_head);
	dist = 0.0;
	if (p->next!=NULL)
		dist+= Distancia(p, p->next);
	sol[index].num++;	
	p=p->next;		
	while (p)
	{
		q->next = (CAMINHOS*) malloc(sizeof(CAMINHOS));
	//	printf("%d ", p->index+1);
		q->next->index = p->index;
		q->next->x = p->x;
		q->next->y = p->y;
		q->next->next = p->next;
		q->next->prev = p->prev;
		if (p->next!=NULL)
			dist+= Distancia(p, p->next);
		p=p->next;
		q = q->next;		
		sol[index].num++;
		
	}	
	sol[index].dist = (int)(dist);	
}
void push(PILHA** head, int index)
{
	PILHA* p;
	p = (PILHA*) malloc(sizeof(PILHA));
	p->index = index;
	p->next = NULL;
	if ((*head)==NULL)
	{
	//   printf("head is null\n");	
	   (*head) = p;
	  // printf("head = %d\n", (*head)->index);
	   return;
	}
	p->next = *head;
	*head = p;	
//	printf("head = %d\n", (*head)->index);
	
}
int pop(PILHA** head)
{
	int value;
	value = (*head)->index;
	*head = (*head)->next;
	return value;	
}
int isCamara(int index, CAMARA* c, int ncamara)
{
	int i;
	for (i=0; i < ncamara; i++)
	{
		if (c[i].v == index)
			return i;
	}
	return -1;
}
int push_children(int index, PILHA** pilha, SEGMENTOS* s, int nseg, int* visitados){
	int i;
	int count;
	count = 0;
	for (i =0; i < nseg; i++)	
	{
		if (s[i].b == index)
		{
			if ((s[i].e >= 0)&&(visitados[(s[i].e)]==0))
			{
	//			printf("Adding %d\n", s[i].e+1);
				push(pilha, s[i].e);
				count++;
			}
		}
		if (s[i].e == index){
			if ((s[i].b >= 0)&&(visitados[(s[i].b)] ==0))
			{
	//		       printf("Adding %d\n", s[i].b+1);
				push(pilha, s[i].b);
				count++;
			}
		}
	}
	return count;
}
int push_childrenS(int index, PILHA** pilha, SEGMENTOS* s, int nseg, int* visitados, CAMARA* c, int ncamara){
	int i;
	int count;
	count = 0;
	for (i =0; i < nseg; i++)	
	{
		if (s[i].b == index)
		{
			if ((s[i].e >= 0)&&(visitados[(s[i].e)]==0)&&(isCamara(s[i].e, c, ncamara)!=-1))
			{
	//			printf("Adding %d\n", s[i].e+1);
				push(pilha, s[i].e);
				count++;
			}
		}
		if (s[i].e == index){
			if ((s[i].b >= 0)&&(visitados[(s[i].b)] ==0)&&(isCamara(s[i].b, c, ncamara)!=-1))
			{
	//		       printf("Adding %d\n", s[i].b+1);
				push(pilha, s[i].b);
				count++;
			}
		}
	}
	return count;
}
void AddToPath(CAMINHOS** head,CAMINHOS** tail, CAMINHOS* p_aux){
	CAMINHOS* temp, *p;
		
	temp = (CAMINHOS*) malloc(sizeof(CAMINHOS));
	p = (CAMINHOS*) malloc(sizeof(CAMINHOS));
	temp->index = p_aux->index;
	temp->x = p_aux->x;
	temp->y = p_aux->y;
	temp->nemp = p_aux->nemp;
	temp->next = NULL;
	temp->prev = NULL;

	if ((*head)==NULL)
	{         
	   (*head) = temp;
	   (*tail) = temp;
	   return;
	}
	p = *head;				
	while(p->next!=NULL){
	 
	   p=p->next;
	}
	p->next = temp;
	temp->prev = p;
	*tail = temp;
	
}
void Find_Paths(CAMARA* c, PONTO* p, SEGMENTOS* s, SOLUCAO* sol, int ncamara, int nponto, int nseg, int Cs)
{
	CAMINHOS* head = NULL, *tail = NULL, *p_aux;
	int* visitados, *saidas;
	int index, cam_index, nsol, saida, nemp, stop;
 	PILHA *pilha =  NULL;
	visitados = (int*) calloc(nponto, sizeof(int));	
	saidas = (int*) calloc(ncamara, sizeof(int));	
	p_aux = (CAMINHOS*) malloc(sizeof(CAMINHOS));
	p_aux->index = Cs;	
	p_aux->x = p[Cs].x;
	p_aux->y = p[Cs].y;
	p_aux->next = NULL;
	p_aux->prev = NULL;
	
	AddToPath(&head,&tail, p_aux);	
	//printf("adding cs\n");
	
	
	//printf("head %d\n", head->index+1);
	//push(&pilha, Cs);
	head->nemp = push_children(Cs, &pilha, s, nseg, visitados);
	visitados[Cs] = 1;
	nsol=0;	
	sol[nsol].cam = (CAMINHOS*) malloc(sizeof(CAMINHOS));
	//printf("solucao %d\n", nsol+1);
	
	Salvar_Solucao(head, sol, nsol, &sol[nsol].cam);	
	nsol++;
	while(pilha!=NULL)
	{
		index = pop(&pilha);
	//	printf("poped %d\n", index+1);
		visitados[index] = 1;
		cam_index = isCamara(index, c, ncamara);
		saida =0;
		
		if (cam_index!=-1)
		{
			
			if ((c[cam_index].o==1)&&(saidas[cam_index] ==0))
			{
				//eh saida				
				p_aux->index = index;
				p_aux->x = p[index].x;
				p_aux->y = p[index].y;
			 	p_aux->next = NULL;
				p_aux->nemp = push_childrenS(index, &pilha, s, nseg, visitados, c, ncamara );
				
				if (p_aux->nemp !=0){				   
				    saidas[cam_index] = 1;	
				}
				AddToPath(&head,&tail, p_aux);							
	//			printf("solucao %d\n", nsol+1);
			        sol[nsol].cam = (CAMINHOS*) malloc(sizeof(CAMINHOS));
				Salvar_Solucao(head, sol,nsol, &sol[nsol].cam);
				nsol++;
				stop =0;
				while((tail!=NULL)&&(!stop)&&(p_aux->nemp==0))
				{
					if (tail->nemp <=1){
	//					printf("removing %d\n", tail->index+1);
						if (tail->index!=Cs)
							visitados[tail->index] = 0;						
					}else {					
					  stop=1;
					}
					if (!stop)
						tail = tail->prev;
											
				}
				
				if (tail!=NULL){
	//			printf("decreasing nemp %d %d\n",tail->index+1, tail->nemp);					
					tail->nemp--;
					tail->next = NULL;					
				
				}		
				saida = 1;				
			}						
		}
		if (!saida)
		{
			
			nemp = push_children(index, &pilha, s, nseg, visitados);
			if (nemp==0)			
			{
	//			printf("sem caminho\n");
				//tail->nemp--;
				stop = 0;
				while((tail!=NULL)&&(!stop))
				{
					if (tail->nemp<=1){
	//					printf("removing %d\n", tail->index+1);
						if (tail->index!=Cs)
							visitados[tail->index] = 0;
									
					}else
					    stop=1;
					if (!stop)
						tail = tail->prev;					
				}
				if (tail!=NULL){
					tail->nemp--;
					tail->next = NULL;	
				}				
			}else{
					
 				p_aux->index = index;
				p_aux->x = p[index].x;
				p_aux->y = p[index].y;
			 	p_aux->next = NULL;
				p_aux->nemp = nemp;
				AddToPath(&head, &tail, p_aux);			
				
						
			}
		}
		//if ((head!=NULL)&&(tail!=NULL))
	//		printf("head: %d tail %d\n", head->index+1, tail->index+1);		
	}
	Mostrar_Solucao(sol, nsol);
	//printf("mostrou solucao\n");
}
int main(){
	PONTO* ponto;
	CAMARA* camara;
	SEGMENTOS* seg;
	SOLUCAO* sol;
	
	int nseg, ncamara, nponto;
	int i, Cs;
        scanf("%d", &nponto);
        ponto = (PONTO*) malloc(sizeof(PONTO)*nponto);
	for (i=0; i < nponto; i++)
	{
		scanf("%f %f", &ponto[i].x, &ponto[i].y);		
	}
	scanf("%d", &ncamara);
	camara = (CAMARA*) malloc(sizeof(CAMARA)*ncamara);
	for (i=0; i < ncamara; i++)
	{
		scanf("%d %d", &camara[i].v, &camara[i].o);
		camara[i].v--;
	}
	scanf("%d", &nseg);
	seg = (SEGMENTOS*) malloc(sizeof(SEGMENTOS)*nseg);
	for (i=0; i < nseg; i++)
	{
		scanf("%d %d", &seg[i].b, &seg[i].e);
		if (seg[i].b > 0)
			seg[i].b--;
		else
			seg[i].b++;			
		if (seg[i].e > 0)
			seg[i].e--;
		else
			seg[i].e++;		
	}	
	scanf("%d", &Cs);
	Cs--;
	/*FILE* file;
	
	file = fopen("2.in", "r");
	fscanf(file, "%d", &nponto);
	
	ponto = (PONTO*) malloc(sizeof(PONTO)*nponto);
	for (i=0; i < nponto; i++)
	{
		fscanf(file, "%f %f", &ponto[i].x, &ponto[i].y);		
	}
	fscanf(file, "%d", &ncamara);
	camara = (CAMARA*) malloc(sizeof(CAMARA)*ncamara);
	for (i=0; i < ncamara; i++)
	{
		fscanf(file, "%d %d", &camara[i].v, &camara[i].o);
		camara[i].v--;
	}
	fscanf(file, "%d", &nseg);
	seg = (SEGMENTOS*) malloc(sizeof(SEGMENTOS)*nseg);
	for (i=0; i < nseg; i++)
	{
		fscanf(file, "%d %d", &seg[i].b, &seg[i].e);
		if (seg[i].b > 0)
			seg[i].b--;
		else
			seg[i].b++;			
		if (seg[i].e > 0)
			seg[i].e--;
		else
			seg[i].e++;		
	}	
	fscanf(file, "%d", &Cs);
	Cs--;*/
	sol = (SOLUCAO*) malloc(sizeof(SOLUCAO)*500);

	//fclose(file);	
	Find_Paths(camara, ponto, seg, sol, ncamara, nponto, nseg, Cs );
	
	free(camara);
	free(ponto);
	free(seg);
}

