#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 3                                  // Niveis da arvore de processos

int main(){
    int fork_id[N];

    for(int i = 0; i < N; i++){              // cria N niveis
        fork_id[i] = fork();                 // cria processo filho
    }

    sleep(10);
    return 0;
}