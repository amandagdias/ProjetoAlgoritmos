#
#Nome: Amanda Gonçalves Dias
#NUSP: 10275312
#Turma: Projeto de Algoritmos SCC5900
#Data Entrega: 24/03/2017


all: Gauss-Jordan
Gauss-Jordan: Gauss-Jordan.o main.o       
	gcc -o Gauss-Jordan Gauss-Jordan.o  main.o
Gauss-Jordan.o: Gauss-Jordan.c
	gcc -o Gauss-Jordan.o -c Gauss-Jordan.c -W -Wall -pedantic
main.o: main.c Gauss-Jordan.h
	gcc -o main.o -c main.c -W -Wall -pedantic
clean:
	rm -rf *.o
mrproper: clean
	rm -rf Gauss-Jordan
run: Gauss-Jordan
	./Gauss-Jordan