/* Implemente um exemplo com memória compartilhada que possibilite e a troca de informação usando
uma struct com ao menos dois tipos diferentes de dados (ex: struct Livro {char
titulo[40]; char autor[30]; int num_paginas;}). Pode ser no modelo de produtorconsumidor (um processo produz e outro consome).
 */

 /* produtor.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>


typedef struct {
    char titulo[40];
    char autor[30];
    int num_paginas;
} Livro;


int main(){
    const int SIZE = 4096;
    const char *name = "OS";

    /* Criando um livro */
    Livro livro;
    strcpy(livro.titulo, "Harry Potter");
    strcpy(livro.autor, "J.K. Rowling");
    livro.num_paginas = 400;

    /* Criando a memória compartilhada */
    int shm_fd;
    void *ptr;

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* Configurando o tamanho da memória compartilhada */
    ftruncate(shm_fd, SIZE);

    /* Mapeando a memória compartilhada */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        return -1;
    }

    /* Escrevendo o livro na memória compartilhada */
    memcpy(ptr, &livro, sizeof(Livro));

    return 0;
}



