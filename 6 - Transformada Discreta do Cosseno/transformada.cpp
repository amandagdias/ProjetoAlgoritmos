#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define PI 3.14159265358979323846

void TransformadaCos(int* original,double **cos, int N)
{
	int i, j;
	for (j = 0; j < N; j++)
	{
		for (i=0; i<N;i++)
		{
			(*cos[j]) += original[i] * cos((PI/N)*(i + 1/2)*j);
		}
	}	
}

int* readfromfile(char* str, int* k)
{	
	unsigned char c;
	FILE *file;
	int i;
	int* original;
	file = fopen(str, "rt");
	if (file != NULL) {
		*k = 0;
	
    	while (!feof(file))
		{	
			c = fgetc(file);				
				(*k)++;			
		}
		fclose(file);
	}

	(*k)--;

	original = malloc (*k * sizeof(int) );
	
	file = fopen(str, "rt");	
	if (file != NULL) {
		i = 0;	
    	while (!feof(file))
		{	
			c = fgetc(file);
			if (i < (*k))	{
				original[i] = (int)c;				
				i++;
			}
					
		}
		fclose(file);
	}
	return original;	
}
int main()
{
	int* original;
	double* coss;
	char* str;
	int i, amp_size, k;
	FILE * File;  

	str = malloc(sizeof(char) * 20);
	
	scanf("%s",str);

	
	scanf("%d", &k);
	
	original = readfromfile(str, &amp_size);		
	coss = malloc(sizeof(double) * amp_size);
	for (i = 0; i < amp_size; i++)
		coss[i] = 0.0;
	TransformadaCos(original, &cos, amp_size);
	
	for (i = 0; i < amp_size; i++)
	{
		printf("%lf"cos[i]);
	}
	
	free(original);
	original = NULL;
	free(coss);
	coss = NULL;


}
