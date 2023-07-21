/* Usando FIFO, Faça um programa que lê strings digitadas pelo usuário e envia para outro programa que recebe
essas strings e exibe na tela: a string, o tamanho, o número de consoantes, o número de vogais e o
número de espaços. */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>
#include <string.h>

#define SERVER_FIFO "/tmp/server_fifo"


/* Programa principal */
int main(){
    int fd, bytes_read;
    char buffer[512];

    /* Cria um fifo */
    if(mkfifo(SERVER_FIFO, 0666) == -1){
        if(errno != EEXIST){
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    /* Abre o fifo para escrita */
    if((fd = open(SERVER_FIFO, O_WRONLY)) == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Lê uma string do teclado */
    fgets(buffer, 512, stdin);

    /* Envia a string para o fifo */
    bytes_read = write(fd, buffer, strlen(buffer));
    if(bytes_read == -1){
        perror("write");
        exit(EXIT_FAILURE);
    }

    /* Fecha o fifo */
    close(fd);

    /* Termina o processo */
    exit(EXIT_SUCCESS);

    return 0;
}




