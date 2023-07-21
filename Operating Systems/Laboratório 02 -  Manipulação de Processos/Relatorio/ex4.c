#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wordexp.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 100

int main(){
    char* params[MAX_LINE_LENGTH/2 + 1];             //Vetor de parâmetros
    char cmd[MAX_LINE_LENGTH];                       //Vetor de comando
    int saida= 0;                                    //Variável de controle de saída
    int espera = 1;                                  //Variável de controle de espera
    int i;                                           //Variável de controle de laço
    int status;                                      //Variável de controle de status
    wordexp_t aux;                                   //Variável auxiliar

    do{                                                                 
        printf("shell> ");                           //Prompt
        fflush(stdout);                              //Limpa o buffer de saída
        fgets(cmd, MAX_LINE_LENGTH, stdin);          //Recebe o comando

        if(strcmp(cmd, "exit") == 0){                //Verifica se o comando é exit
            saida = 1;                                                  
        } else{                                      //Caso não seja exit
            if(cmd[strlen(cmd)-2] == '&'){           //Verifica se o comando é em segundo plano
                cmd[strlen(cmd)-2] = '\0';           //Remove o & do comando
                espera = 0;                          //Não espera o retorno do comando
            }else{
                cmd[strlen(cmd)-1] = '\0';           //Remove o \n do comando
            }

            wordexp(cmd, &aux, 0);                   //Expande o comando
            for(i = 0; i < aux.we_wordc; i++){       //Percorre o vetor de parâmetros
                params[i] = aux.we_wordv[i];         //Copia o parâmetro para o vetor de parâmetros
            }
            params[i] = NULL;                        //Finaliza o vetor de parâmetros

            pid_t pid = fork();                      //Cria um processo filho
            if(pid == 0){
                execvp(params[0], params);           //Executa o comando
                exit(0);                             //Finaliza o processo filho
            }

            if(espera == 1){                         //Verifica se o comando é em segundo plano
                waitpid(pid, &status, 0);            //Espera o retorno do comando
            } else{
                espera = 1;                          //Reinicia a variável de controle de espera
            }

        }

    } while(!saida);

    return 0;
}