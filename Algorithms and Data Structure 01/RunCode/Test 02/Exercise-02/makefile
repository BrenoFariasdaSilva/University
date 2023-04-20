all:
	gcc -c  ex02_fila_pilha.c pilha_implementacao.c
	gcc main.c *.o -o main
	./main
	rm -f *.o
	rm -f main

runcodes:
	gcc -c  ex02_fila_pilha.c pilha_implementacao.c
	gcc main-runcodes.c *.o -o main
	main < 1.in
	main < 2.in
	rm -f *.o
	rm -f main

clean:
	rm -f *.o
	rm -f main