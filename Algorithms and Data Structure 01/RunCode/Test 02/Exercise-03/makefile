all:
	gcc -c ex03.c
	gcc main.c *.o -o main
	./main
	rm -f *.o
	rm -f main

runcodes:
	gcc -c  ex03.c
	gcc main-runcodes.c *.o -o main
	main < 3.in
	del *.o
	del main

clean:
	rm -f *.o
	rm -f main
