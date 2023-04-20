all:
	gcc -cpp Classes.cpp
	gcc main.cpp Classes.o -o main
	./main
	rm ./main

clean:
	rm -f *.o main