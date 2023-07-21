CC=gcc -Wall

PROGS=consumidor produtor

all: $(PROGS)

clean:
	rm -f $(PROGS)

produtor:	produtor.c
	$(CC) produtor.c -o produtor -lrt

consumidor:	consumidor.c
	$(CC) consumidor.c -o consumidor -lrt
