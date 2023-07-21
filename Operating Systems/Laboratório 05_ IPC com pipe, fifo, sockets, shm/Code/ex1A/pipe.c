/* Usando PIPES, Faça um programa que lê strings digitadas pelo usuário e envia para outro programa que recebe
essas strings e exibe na tela: a string, o tamanho, o número de consoantes, o número de vogais e o
número de espaços. */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
        printf("Digite uma string: ");
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

        /* Imprime a string */
        printf("String: %s\n", buffer);

        /* Imprime o tamanho da string */
        printf("Tamanho: %d\n", (int)strlen(buffer));

        /* Imprime o número de consoantes */
        int i, consoantes = 0;
        for(i = 0; i < strlen(buffer); i++){
            if(buffer[i] != 'a' && buffer[i] != 'e' && buffer[i] != 'i' && buffer[i] != 'o' && buffer[i] != 'u'){
                consoantes++;
            }
        }
        printf("Número de consoantes: %d\n", consoantes);

        /* Imprime o número de vogais */
        int vogais = 0;
        for(i = 0; i < strlen(buffer); i++){
            if(buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u'){
                vogais++;
            }
        }
        printf("Número de vogais: %d\n", vogais);

        /* Imprime o número de espaços */
        int espacos = 0;
        for(i = 0; i < strlen(buffer); i++){
            if(buffer[i] == ' '){
                espacos++;
            }
        }
        printf("Número de espaços: %d\n", espacos);

        /* Fecha o descritor de leitura do pipe */
        close(mypipe[0]);

        /* Termina o processo filho */
        exit(EXIT_SUCCESS);
    }

    
}