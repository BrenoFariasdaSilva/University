CC=gcc -Wall

PROGS=prod_cons

all:
	gcc -c fila_contigua.c
	gcc main.c fila_contigua.o -o main -lpthread
	./main

clean:
	rm -f *.o $(PROGS)