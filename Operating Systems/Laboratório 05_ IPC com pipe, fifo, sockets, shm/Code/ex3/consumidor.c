/* Implemente um exemplo com memória compartilhada que possibilite e a troca de informação usando
uma struct com ao menos dois tipos diferentes de dados (ex: struct Livro {char
titulo[40]; char autor[30]; int num_paginas;}). Pode ser no modelo de produtorconsumidor (um processo produz e outro consome).
*/

/* consumidor.c */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char titulo[40];
    char autor[30];
    int num_paginas;
} Livro;

int main(){
    const char *name = "OS";
	const int SIZE = 4096;

    int shm_fd;
    void *ptr;

    /* Abrir o segmento de memoria compartilhada */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }

    /* Mapear a memoria compartilhada */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }

    /* Ler o livro */
    Livro livro;
    memcpy(&livro, ptr, sizeof(Livro));

    printf("Livro: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Numero de paginas: %d\n", livro.num_paginas);

    return 0;
}