all:
	gcc -g -c ilist.c
	gcc -g -c hashtable_ea.c
	gcc -g main.c -o main ilist.o hashtable_ea.o
	./main
	rm -f *.o
	rm -f ./main