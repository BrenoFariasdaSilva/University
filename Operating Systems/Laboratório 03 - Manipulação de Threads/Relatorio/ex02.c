#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

// Define a quantidade de threads e o tamanho do vetor
#define N 2
#define TV 30
#define TVR 10

// Estrutura para passar os parametros para as threads
struct parametros {
    int *vetor;
    int *vetor_resposta;
    int inicio;
    int fim;
    int id;
    int tam_vetor;
};

// Função para imprimir o vetor
void imprimir_vetor(int *vetor, int tam_vetor) {
    int i;
    printf("[ ");
    for (i = 0; i < tam_vetor; i++) {
        printf("%d ", vetor[i]);
    }
    printf("]\n\n");
}

// Função para gerar um vetor com valores aleatórios
void gerar_vetor(int *vetor, int tam_vetor) {
    int i;
    for (i = 0; i < tam_vetor; i++) {
        vetor[i] = rand() % 10;
    }
}

// Inicializar o vetor com zeros
void inicializar_vetor(int *vetor, int tam_vetor) {
    int i;
    for (i = 0; i < tam_vetor; i++) {
        vetor[i] = 0;
    }
}

// Função que busca um valor no vetor
void *busca(void *parametros) {
    struct parametros *p = (struct parametros *) parametros;
    int i;
    int *vetor = p->vetor;
    int *vetor_resposta = p->vetor_resposta;
    int inicio = p->inicio;
    int fim = p->fim;
    int id = p->id;
    int tam_vetor = p->tam_vetor;

    printf("----- Thread %d -----\n", id);
    // Imprime o subvetor que a thread irá buscar
    imprimir_vetor(vetor + inicio, fim - inicio);

    for (i = inicio; i < fim; i++) {
        p->vetor_resposta[p->vetor[i]]++;
    }

    return NULL;
}

// Função para exibir as frequecias de 0 a 9
void exibir_frequencia(int *vetor_resposta, int tam_vetor) {
    int i;
    for (i = 0; i < tam_vetor; i++) {
        printf("A frequencia do numero %d eh %d\n", i, vetor_resposta[i]);
    }
}

// Função principal
int main(){
    printf("---------- Exercicio 02 ----------\n\n");

    // Alocação do vetor
    int *vetor = (int *) malloc(TV * sizeof(int));
    int *vetor_resposta = (int *) malloc(TV * sizeof(int));

    // Geração do vetor
    gerar_vetor(vetor, TV);
    inicializar_vetor(vetor_resposta, TVR);

    // Impressão do vetor
    printf("Vetor: ");
    imprimir_vetor(vetor, TV);

    // Alocação do vetor de threads
    pthread_t threads[N];

    // Alocação do vetor de parametros
    struct parametros parametros[N];

    //Calculo da parte do vetor recebida pelas threads
    int quant = TV / N;
    int qnt_aux = TV % N;

    // Alocação do vetor de threads
    int i;
    for (i = 0; i < N; i++) {
        parametros[i].vetor = vetor;
        parametros[i].vetor_resposta = vetor_resposta;
        parametros[i].inicio = i * (TV / N);

        //A thread recebe sua parte do vetor
        if(i < qnt_aux){
            parametros[i].tam_vetor = quant + 1;
        } else{
            parametros[i].tam_vetor = quant;
        }

        parametros[i].fim = parametros[i].inicio + parametros[i].tam_vetor;
        parametros[i].id = i;
        parametros[i].tam_vetor = TV;

        // Criação da thread
        pthread_create(&threads[i], NULL, busca, (void *) &parametros[i]);
    }

    // Aguarda as threads terminarem
    for (i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Impressão do vetor de resposta
    printf("Vetor de resposta: ");
    imprimir_vetor(vetor_resposta, TVR);

    exibir_frequencia(vetor_resposta, TVR);

    // Liberação da memória
    free(vetor);

    return 0;

}

