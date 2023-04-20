all:
	gcc -c tad_estoque.c
	gcc main_runcodes.c tad_estoque.o tad_produto.o -o main
	./main < 1.in
	rn ./main.o