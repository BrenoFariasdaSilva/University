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

/* Crie uma função que receba uma string de uma expressao matematica e resolva */
int eval(char *str){
    int result = 0;
    char op = ' ';
    char num1 = ' ';
    char num2 = ' ';

    /* Pega o primeiro número */
    for(int i = 0; i < strlen(str); i++){

        if(str[i] == ' '){
            continue;
        }

        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
            op = str[i];
            continue;
        }

        if(str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != ' '){
            if(num1 == ' '){
                num1 = str[i];
            } else if(num2 == ' '){
                num2 = str[i];
            }
        }
    }

    /* Converte os números para inteiros */
    int num1_int = num1 - '0';
    int num2_int = num2 - '0';

    /* Realiza o cálculo */
    if(op == '+'){
        result = num1_int + num2_int;
    } else if(op == '-'){
        result = num1_int - num2_int;
    } else if(op == '*'){
        result = num1_int * num2_int;
    } else if(op == '/'){
        result = num1_int / num2_int;
    }

    return (int)result;
}

/* Programa principal */
int main(int argc, char *argv[]){
    /* Cria o fifo */
    if(mkfifo(SERVER_FIFO, 0666) == -1){
        if(errno != EEXIST){
            perror("Erro ao criar o fifo");
            exit(EXIT_FAILURE);
        }
    }

    /* Abre o fifo para leitura */
    int fifo_fd = open(SERVER_FIFO, O_RDONLY);
    if(fifo_fd == -1){
        perror("Erro ao abrir o fifo");
        exit(EXIT_FAILURE);
    }

    /* Aloca memória para a string */
    char *buffer = (char *)malloc(sizeof(char) * 100);
    if(buffer == NULL){
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    /* Lê uma string do pipe */
    read(fifo_fd, buffer, 100);

    /* Imprime o resultado da expressão */
    int resultado = eval(buffer);
    printf("Resultado: %d\n", resultado);

    /* Fecha o fifo */
    close(fifo_fd);

    /* Remove o fifo */
    if(unlink(SERVER_FIFO) == -1){
        perror("Erro ao remover o fifo");
        exit(EXIT_FAILURE);
    }

    return 0;
}