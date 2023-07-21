#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "matriz.h"

// Defines
#define NUM_THREADS 5

// Variaveis Globais
int** matriz;

int rows = 6;
int cols = 8;

float* medias;
int* medianas;

// Estrutura
typedef struct {
    int id;
    int quantidade;
} Dados;

// Protótipos
void* thread_media(void* param);
void selectionSort(int* vetor, int tamanho);
void* thread_mediana(void* param);


// Função Principal
int main(){
    printf("---------- Exercicio 03 ----------\n\n");

    //Declaração de variáveis
    int op;

    pthread_t threads[NUM_THREADS];
    Dados dados[NUM_THREADS];

    // Receber a opção do usuário
    do{
        printf("Digite:\n[1] - Gerar Matriz\n[2] - Carregar Matriz\n");
        scanf("%d", &op);
    } while(op != 1 && op != 2);


    // Gerar ou cvetoregar a matriz
    if (op == 1){

        printf("Digite o número de linhas: ");
        scanf("%d", &rows);
        printf("Digite o número de colunas: ");
        scanf("%d", &cols);

        matriz = create_matrix(rows, cols);
        srand(time(NULL));
        generate_elements(matriz, rows, cols, 99);

        printf("\nMatriz %dx%d criada com sucesso!\n", rows, cols);

    } else{

        matriz = read_matrix_from_file("data_matrix.in", &rows, &cols);

        printf("\nMatriz carregada com sucesso!\n");
    }

    // Inicio da contagem de tempo
    clock_t start = clock();

    // Output
    printf("\nNumero de Threads: %d\n", NUM_THREADS);
    printf("\nMatriz [%d x %d]\n\n", rows, cols);


    /*  ---------------------------------------------
                TRABALHANDO COM A MÉDIA
    -------------------------------------------------*/
    printf("-------- MEDIA --------\n");
    // Inicializar o vetor do resultado das médias
    float resultado_medias[cols];
    for(int i = 0; i < cols; i++){
        resultado_medias[i] = 0;
    }
    medias = resultado_medias;

    // Divisao das colunas em "cols" partes
    int quant = cols / NUM_THREADS;
    int qnt_aux = cols % NUM_THREADS;
    int aux = 0;

    for(int i = 0; i < NUM_THREADS; i++){
        if(i < qnt_aux){
            dados[i].quantidade = quant + 1;
        } else{
            dados[i].quantidade = quant;
        }
        dados[i].id = i;

        printf("Thread %d: %d colunas\n", i, dados[i].quantidade);
    }
    printf("\n");

    print_matrix(matriz, rows, cols);

    // Criar as threads para a média
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, thread_media, (void*) &dados[i]);
    }
    
    // Esperar as threads terminarem
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }



    /*  ---------------------------------------------
                TRABALHANDO COM A MEDIANA
    -------------------------------------------------*/
    printf("\n-------- MEDIANA --------\n");
    // Divisão das linhas em "rows" partes
    quant = rows / NUM_THREADS;
    qnt_aux = rows % NUM_THREADS;
    aux = 0;

    for(int i = 0; i < NUM_THREADS; i++){
        if(i < qnt_aux){
            dados[i].quantidade = quant + 1;
        } else{
            dados[i].quantidade = quant;
        }
        dados[i].id = i;

        printf("Thread %d: %d linhas\n", i, dados[i].quantidade);
    }

    // Criação de uma copia da matriz principal
    int matriz_copia[rows][cols];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matriz_copia[i][j] = matriz[i][j];
        }
    }

    // Ordenando as linhas da matriz principal
    for(int i = 0; i < rows; i++){
        selectionSort(matriz[i], cols);
    }
    print_matrix(matriz, rows, cols);

    // Inicializar o vetor do resultado das medianas
    int resultado_medianas[rows];
    for(int i = 0; i < rows; i++){
        resultado_medianas[i] = 0;
    }
    medianas = resultado_medianas;

    // Criar as threads para a mediana
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, thread_mediana, (void*) &dados[i]);
    }

    // Esperar as threads terminarem
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    // Imprimir os resultados
    
    printf("\nMediana: ");
    for(int i=0; i<rows;i++){
        printf(" [%d]", resultado_medianas[i]);
    }
    printf("\n");

    printf("\nMedia: ");
    for(int i=0; i<cols;i++){
        printf(" [%.2f]", medias[i]);
    }
    printf("\n");

    // Salvanr os resultados num arquivo
    FILE* arq_result = fopen("results.txt", "w");

    fprintf(arq_result, "Mediana: ");
    for(int i=0; i<rows;i++){
        fprintf(arq_result, " [%d]", resultado_medianas[i]);
    }
    fprintf(arq_result, "\n");

    fprintf(arq_result, "Media: ");
    for(int i=0; i<cols;i++){
        fprintf(arq_result, " [%.2f]", medias[i]);
    }
    fprintf(arq_result, "\n");

    printf("\nResultados salvos em results.txt com sucesso!\n");

    fclose(arq_result);

    // Fim da contagem de tempo
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nTempo gasto: %f segundos\n", time_spent);

    return 0;
}




// Função de média
void *thread_media(void *param){
    Dados *dados = (Dados*) param;

    int inicio = dados->id * dados->quantidade;
    int fim = inicio + dados->quantidade;

    for(int i = inicio; i < fim; i++){
        for(int j = 0; j < rows; j++){
            medias[i] += (float)matriz[j][i]/ (float)rows;
        }
        //printf("Coluna %d: %f\n", i, medias[i]);
    }
}


// Função de mediana
void selectionSort(int vetor[], int n){
    int i, j, min_idx;
    for (i = 0; i < n-1; i++){
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (vetor[j] < vetor[min_idx]) min_idx = j;
        // Swap 
        vetor[min_idx] = vetor[min_idx] + vetor[i]-(vetor[i]=vetor[min_idx]);
    }
}

void *thread_mediana(void *param){
    Dados *dados = (Dados*)param;

    int inicio = dados->id * dados->quantidade;
    int fim = inicio + dados->quantidade;


    for(int i = inicio; i < fim; i++){
        medianas[i] = matriz[i][(int)ceil(cols/2)];
        //printf("Linha %d: %d\n", i, medianas[i]);
    }
    
}