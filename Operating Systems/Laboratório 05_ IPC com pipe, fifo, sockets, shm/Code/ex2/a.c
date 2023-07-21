/* Faça um programa que lê atributos de configuração de inicialização (p. ex.: diretório padrão,
dono, ...) de um arquivo e, ao receber o signal 1 (SIGHUP), refaz a leitura desse arquivo e
modifica as variáveis internas. Para provar que funciona, faça um menu com a opção para imprimir
os atributos carregados na leitura.
 */


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BUFFER 1024

FILE* arquivo;
char buffer[MAX_BUFFER];

// Função que trata o SIGHUP
void SIG_HANDLER(int signo) {
    while (fgets(buffer, MAX_BUFFER, arquivo) != NULL) {
        printf("%s", buffer);
    }

    // Modificar as variáveis internas
    arquivo = fopen("/etc/ssh/ssh_config", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fseek(arquivo, 0, SEEK_END);
    while ( getchar() != '\n' );
    printf("Digite o texto a ser escrito no arquivo: ");
    fgets(buffer, 1024, stdin);
    fprintf(arquivo, "%s", buffer);
    fclose(arquivo);
}

// Função principal
int main() {
    int op;

    signal(SIGHUP, SIG_HANDLER);

    // Exibe o menu
    while(true){
        printf("Escolha uma opção:\n");
        printf("1 - Ler o arquivo\n");
        printf("2 - Escrever no arquivo\n");
        printf("3 - Sair\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                arquivo = fopen("/etc/ssh/ssh_config", "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo\n");
                    exit(1);
                }
                while (fgets(buffer, MAX_BUFFER, arquivo) != NULL) {
                    printf("%s", buffer);
                }
                fclose(arquivo);
                break;
            case 2:
                arquivo = fopen("/etc/ssh/ssh_config", "a");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo\n");
                    exit(1);
                }
                fseek(arquivo, 0, SEEK_END);
                while ( getchar() != '\n' );
                printf("Digite o texto a ser escrito no arquivo: ");
                fgets(buffer, 1024, stdin);
                fprintf(arquivo, "%s", buffer);
                fclose(arquivo);
                break;
            case 3:
                exit(0);
            default:
                printf("Opção inválida\n");
        }

    }
}



