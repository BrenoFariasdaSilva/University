all:
	gcc -c *.c
	gcc ./*.o -o main
	./main
	rm -f *.o
	rm -f main

runcodes:
	gcc -c *.c
	gcc ./*.o -o main
	./main < 1.in
	rm -f *.o
	rm -f main

clean:
	rm -f *.o
	rm -f main