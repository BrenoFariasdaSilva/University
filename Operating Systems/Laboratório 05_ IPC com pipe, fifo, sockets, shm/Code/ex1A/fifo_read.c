/* fifo_read.c */

/* Usando FIFO, Faça um programa que lê strings digitadas pelo usuário e envia para outro programa que recebe
essas strings e exibe na tela: a string, o tamanho, o número de consoantes, o número de vogais e o
número de espaços. */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
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

    /* Abre o fifo para leitura */
    if((fd = open(SERVER_FIFO, O_RDONLY)) == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Lê uma string do fifo */
    bytes_read = read(fd, buffer, 512);

    /* Exibe a string */
    printf("String: %s\n", buffer);

    /* calcula o tamanho da string */
    printf("Tamanho: %d\n", (int)strlen(buffer));

    /* calcula o número de consoantes */
    int i, consoantes = 0;
    for(i = 0; i < strlen(buffer); i++){
        if(buffer[i] != 'a' && buffer[i] != 'e' && buffer[i] != 'i' && buffer[i] != 'o' && buffer[i] != 'u' && buffer[i] != 'A' && buffer[i] != 'E' && buffer[i] != 'I' && buffer[i] != 'O' && buffer[i] != 'U'){
            consoantes++;
        }
    }
    printf("Número de consoantes: %d\n", consoantes);

    /* calcula o número de vogais */
    int vogais = 0;
    for(i = 0; i < strlen(buffer); i++){
        if(buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u' || buffer[i] == 'A' || buffer[i] == 'E' || buffer[i] == 'I' || buffer[i] == 'O' || buffer[i] == 'U'){
            vogais++;
        }
    }
    printf("Número de vogais: %d\n", vogais);

    /* calcula o número de espaços */
    int espacos = 0;
    for(i = 0; i < strlen(buffer); i++){
        if(buffer[i] == ' '){
            espacos++;
        }
    }
    printf("Número de espaços: %d\n", espacos);

    /* Fecha o fifo */
    close(fd);

    /* Termina o processo */
    exit(EXIT_SUCCESS);

    return 0;
}