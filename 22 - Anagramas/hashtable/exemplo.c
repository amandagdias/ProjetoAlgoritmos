#include <stdlib.h>
#include <stdio.h>

int funcao(int a, int b) {
	return a+b;
}

int main(int argc, char *argv[]) {
	int (*p)(int, int);
	p = &funcao;
	printf("%d\n", p(5,6));
	return 0;
}
