/* Faça um programa que lê uma expressão matemática simples (+, -, *, /) e passe para outro
programa que realiza o cálculo e devolve a resposta. */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int eval(char *str);

/* Programa principal */
int main(){
    pid_t pid;
    int mypipe[2];
    char buffer[100];

    /* Cria um pipe */
    if(pipe(mypipe) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /* Cria um processo filho */
    pid = fork();

    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if(pid > 0){
        /* Fecha o descritor de leitura do pipe */
        close(mypipe[0]);

        /* Lê uma string do teclado */
        printf("Digite uma expressão matemática: ");
        fgets(buffer, 100, stdin);

        /* Envia a string para o processo filho */
        write(mypipe[1], buffer, strlen(buffer));

        /* Fecha o descritor de escrita do pipe */
        close(mypipe[1]);

        /* Espera o processo filho terminar */
        wait(NULL);

        /* Termina o processo pai */
        exit(EXIT_SUCCESS);
    } else {
        /* Fecha o descritor de escrita do pipe */
        close(mypipe[1]);

        /* Lê uma string do pipe */
        read(mypipe[0], buffer, 100);

        /* Imprime o resultado da expressão */
        int resultado = eval(buffer);
        printf("Resultado: %d\n", resultado);
    }
}

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
