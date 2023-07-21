/* Faça um programa que recebe o signal 2 (SIGINT) e dispara um alarme para finalizar sua
execução dentro de 10 segundos. Nesse intervalo, o programa deve ficar exibindo na tela uma
contagem regressiva de 1 em 1 segundo. */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void catch_alarm(int sig) {
    puts("Alarme!");
    exit(EXIT_SUCCESS);
}

void contagem(){
    int i = 10;
    printf("\n");
    while(i > 0){
        printf("%d\n", i);
        sleep(1);
        i--;
    }
}

void do_stuff(void) {
    printf("Fazendo alguma coisa...\n");
    sleep(1);
}

void sig_handle(int sig){
    signal(SIGALRM, catch_alarm);
    alarm(10);
    contagem();
    exit(0);
}

int main(){

    signal(SIGINT, sig_handle);

    while(true){
        do_stuff();
    }


    return EXIT_SUCCESS;
}