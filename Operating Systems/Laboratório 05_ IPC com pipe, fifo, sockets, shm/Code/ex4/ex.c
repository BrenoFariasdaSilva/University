#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

// Alterar: Linhas 22, 175
// Gerar vetor aleatório
int* create_random_array(int size) {
    int* array = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10;
    }
    return array;
}

// Imprimir vetor
void print_array(int* array, int size) {
    printf("Vetor: [");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("]\n");
    printf("\n");
}

// Imprimir matriz
void print_matrix(int** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


// Função main
int main(){
    // Criação de variaveis

    // Recebe o tamanho do vetor e o número de processos
    int numElementos;
    int numProcessos;

    do{
        printf("Digite o número de elementos do vetor: ");
        scanf("%d", &numElementos);

        printf("Digite o número de processos: ");
        scanf("%d", &numProcessos);
    } while(numElementos < numProcessos);

    // Criação do vetor aleatório
    int* vetor = create_random_array(numElementos);
    print_array(vetor, numElementos);

    // Criação da matriz de resultados
    int** matriz = (int**) malloc(numProcessos * sizeof(int*));
    for (int i = 0; i < numProcessos; i++) {
        matriz[i] = (int*) malloc((numElementos/numProcessos)/2 * sizeof(int));
    }

    //Cria um vetor de pipes
    int** pipes = (int**) malloc(numProcessos * sizeof(int*));

    // Criação dos pipes
    for (int i = 0; i < numProcessos; i++) {
        pipes[i] = (int*) malloc(2 * sizeof(int));
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    int resultado[numProcessos][numElementos/numProcessos/2];
    int status[numElementos/numProcessos/2];
    int arrayPai[numElementos];

    // printf("sizeof struct: %d, sizeof instance: %d\n", sizeof(SharedMemory), sizeof(sharedMemory));

    //Pai cria os filhos;
    pid_t pid;
    for(int i = 0; i < numProcessos; i++){
        pid = fork();
        if(pid && i == 0){
            //Pai escreve no pipe de cada filho o intervalo em que eles devem trabalhar;
            for(int i = 0; i < numProcessos; i++){

                int buffer[2];

                int intervalo = numElementos / numProcessos;
                buffer[0] = intervalo * i;
                buffer[1] = intervalo + buffer[0];

                write(pipes[i][1], buffer, sizeof(buffer));

            }
        } else if(pid == 0){

            //Filhos bloqueiam aguardando dados no pipe;
            close(pipes[i][1]);
            int success = 1;

            //Lê um vetor do pipe (bloqueia);
            int buffer[2];
            read(pipes[i][0], buffer, sizeof(buffer));
            printf("Filho %d: %d - %d\n", i, buffer[0], buffer[1]);

            // Acessa a memória compartilhada
            const int SIZE = sizeof(status) + sizeof(resultado);
            const char *name = "OS";

            int shm_fd;
            void *ptr;

            shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

            // Configurando o tamanho da memória compartilhada
            ftruncate(shm_fd, SIZE);

            // Alocando a memória compartilhada
            ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

            // Copiando a struct para a memória compartilhada
            memcpy(ptr, &status, sizeof(status));
            memcpy(ptr+sizeof(status), &resultado, sizeof(resultado));
            int inicio = buffer[0];
            int fim = buffer[1];

            // Criar vetor filho
            int* vetorFilho = vetor[inicio];
            print_array(vetorFilho, fim - inicio);
            int interval = numElementos/numProcessos/2;
            int* vetorA = &vetorFilho[0];
            int* vetorB = &vetorFilho[interval];
            printf("\n--------------\n");
            print_array(vetorA, interval);
            print_array(vetorB, interval);
            printf("\n--------------\n");

            //Soma os dois vetores
            int vetorC[interval];
            for(int i=0; i<interval; i++){
                vetorC[i] = vetorA[i] + vetorB[i];
            }
            printf("Soma:");
            print_array(vetorC, interval);
            for(int j=0; j<interval; j++){
                ptr[numElementos/numProcessos/2+i][j] = vetorC[j];
            }
            ptr[i] = success;
            // o SIZEOF tem que retornar o tamanho completo dos dados (não só dos ponteiros)
          
            // ptr->status[i] = 1;
            printf("-->%d<--", ptr[i]);
            
            exit(1);
          }
    }

    // if(pid){
    //     //reabre a memória para leitura do conteudo que os filhos alteraram
    //     int shm_fd = shm_open("OS", O_RDONLY, 0666);
    //     SharedMemory* ptr = mmap(NULL, sizeof(SharedMemory), PROT_READ, MAP_SHARED, shm_fd, 0);
    //     while(1){
    //         //Constantemente copia da memória compartilhada para a struct para poder ter os dados mais atualizados
    //         sleep(1);
    //         print_array(ptr->status, numProcessos);
    //         // print_matrix(ptr->resultado, numProcessos, numElementos/numProcessos/2);
    //         //imprime a matriz de status
    //         int sum=0;
    //         for(int k=0; k<numProcessos; k++){
    //             sum += ptr->status[k];
    //         }
    //         if(sum == numProcessos){
    //             printf("\n\n-------RESULTADO FINAL-------\n\n");
    //             print_matrix(sharedMemory.resultado, numProcessos, numElementos/numProcessos/2);
    //             break;
    //         }
    //     }
    // }
    

    //Filhos avisam pai que acabaram e encerram;
    //Pai aguarda todos acabarem, imprime o resultado e finaliza.

    
}