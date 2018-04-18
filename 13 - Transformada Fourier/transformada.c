/*
Nome: Amanda Goncalves Dias
NUSP: 10275312
Turma: Projeto de Algoritmos SCC5900
Data Entrega: 30/05/2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>
#include<string.h>

#define PI 3.14159265358979323846
#define e 2.71828182845904523536

typedef struct coef{
	int frequencia;
	double magnitude;
	double complex coeficiente;
}COEF;
void OrdenaDecrescente(COEF* c, int N, int C, int* mag, int *M)
{
	int i, j;
    COEF* aux;
    aux = (COEF*) malloc(sizeof(COEF));
    //Ordena de forma decrescente
	for (i = 0; i < (N/2 + 1); i++)
	{
		for (j=i; j < (N/2 + 1); j++)
		{
			if (c[i].magnitude < c[j].magnitude)
			{		
				aux->coeficiente = c[i].coeficiente;
				aux->frequencia = c[i].frequencia;
				aux->magnitude = c[i].magnitude;
				c[i] = c[j];
				c[j] = *aux;				
			}
		}		
	}
	(*M)=0;
	for (i = 0; i < (N/2 + 1); i++)
		{
		
		if (c[i].magnitude > 0.1)
		{
			
			mag[(*M)] = (int)(c[i].magnitude);		
			(*M)++;
		}
		
	}	
	//Zera os coeficientes com indices maiores do que C
	for (i = C; i < (N/2 + 1); i++)
	{
		c[i].coeficiente = 0.0;	
	}
	//Reordena 
	int m;
	for (i = 0; i < (N/2 + 1); i++)
	{
		
			if (i!=c[i].frequencia)
			{
				m = c[i].frequencia;
				aux->coeficiente = c[i].coeficiente;
				aux->frequencia = c[i].frequencia;
				aux->magnitude = c[i].magnitude;
				c[i] = c[m];
				c[m] = *aux;			
				i=0;
			}
				
	}	
	
}
COEF* calcCoeficientes(int* x, int N)
{
	COEF* c = malloc(sizeof(COEF)* ((N/2 + 1)));

	int k, t;
	double d, E;
	double complex som = 0.0 *I;
	double complex power;
	for (k=0; k < ((N/2 + 1)); k++)
	{
		if (k == 0)
			E = 1.0;
		else
			E = 2.0;
		som = 0.0 * I;
		for (t=0; t < N; t++)
		{
			d = (double)t/N;
			power = (double complex ) -1.0*I*k*2.0*PI*d;
			som += (double complex) x[t] * cpow(e, power);	
			
		}
		c[k].coeficiente = (double complex) E/N * som;	
		c[k].magnitude = csqrt(creal(c[k].coeficiente)*creal(c[k].coeficiente) + cimag(c[k].coeficiente)*cimag(c[k].coeficiente));	
		
		c[k].frequencia = k;
	}
	return c;
}
int readBinaryFile(char str[10], int** x){
	
	FILE *file;
	int N = 0;
	unsigned char c;
	int a;
	file = fopen(str, "rb");
	if (file)
	{	
		while(fread(&c, 1, 1, file) > 0)
		{	
			N++;
			
		}
	}
	else{
		printf("no file found");
	}
	fclose(file);	
	(*x) = (int*) malloc(sizeof(int)*N);
	a = 0;
	file = fopen(str, "rb");	
	if (file)
	{
		while(fread(&c, 1, 1, file) > 0)
		{
			(*x)[a] = (int)c;	
			a++;	
				
		}
	}
	fclose(file);
	return N;	
}
void Fourrier(int* x, int N, COEF* c)
{
	int t, k;	
	double complex som = 0.0 *I;
	double complex power;
	double d;
	for (t = 0 ; t < N; t++)
	{
		som = 0.0 * I;
		for (k=0; k < (N/2 + 1); k++)
		{
			d = (double)t/N;
			power = (double complex) I*k*2.0*PI*d;
			som += (double complex) c[k].coeficiente * cpow(e, power);
		}
		x[t] = (int) round(som);		
	}
}
int main()
{
	char str[10];
	int C, N, M, i;
	int* x;
	COEF* c;
	int* mag;
	
	scanf("%s",str);
	scanf("%d", &C);
	
	N = readBinaryFile(str, &x);
	mag = (int*) malloc(sizeof(int)*((N/2 + 1)));
	c = calcCoeficientes(x, N);
	
	OrdenaDecrescente(c, N, C, mag, &M);
	
	Fourrier(x, N, c);

	printf("%d\n", N);
	printf("%d\n", M);
	for (i=0; i < C; i++)
	{
		printf("%d ", mag[i]);
	}
	printf("\n");
	for(i=0; i < N; i++)
	{
		if (x[i] < 0)
		{
			x[i] = 256 + x[i];
		}
		if (x[i]>256)
		{
			x[i]-=256;
		}
		printf("%d\n", x[i]);
	}
	free(x);
	free(mag);
	free(c);
}
