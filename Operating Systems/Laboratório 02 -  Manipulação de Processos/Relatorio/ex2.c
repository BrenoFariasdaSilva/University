#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
    pid_t pid;

    char *comando = "ls";
    char *argumentos[] = {"ls", "-l", NULL};

    pid = fork();

    if(pid == 0){
        execvp(comando, argumentos);
    }
    else{
        wait(NULL);
    }

    printf("Fim do processo pai!\n");
    return 0;
}