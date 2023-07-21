/* Usando FIFO, Faça um programa que lê uma expressão matemática simples (+, -, *, /) e passe para outro
programa que realiza o cálculo e devolve a resposta. */

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

    /* Cria o fifo */
    if(mkfifo(SERVER_FIFO, 0666) == -1){
        if(errno != EEXIST){
            perror("Erro ao criar o fifo");
            exit(EXIT_FAILURE);
        }
    }

    /* Lê uma string do teclado */
    printf("Digite uma expressão matemática: ");
    fgets(buffer, 512, stdin);

    /* Abre o fifo para escrita */
    if((fd = open(SERVER_FIFO, O_WRONLY)) == -1){
        perror("Erro ao abrir o fifo");
        exit(EXIT_FAILURE);
    }

    /* Envia uma string para o fifo */
    bytes_read = write(fd, buffer, strlen(buffer));
    if(bytes_read == -1){
        perror("Erro ao enviar a string para o fifo");
        exit(EXIT_FAILURE);
    }

    /* Fecha o fifo */
    close(fd);

    /* Termina o processo */
    exit(EXIT_SUCCESS);

    return 0;
}
