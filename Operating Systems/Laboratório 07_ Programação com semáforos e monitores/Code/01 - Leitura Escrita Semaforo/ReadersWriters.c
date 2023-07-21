/*
AUTORES: 
    BRENO FARIAS DA SILVA, 
    FELIPE ARCHANJO DA CUNHA MENDES
    JOAO HENRIQUE GOUVEIA

DESCRIÇÃO:
    Implementação do problema classico de concorrencia leitores/escritores usando semaforos. Note que Leitores podem ler simultaneamente, mas os escritores devem escrever apenas quando nao ha leitores ou outros escritores.

*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define N_LEITORES 5 // Numero de leitores
#define N_ESCRITORES 5 // Numero de escritores
#define MAX_ESCRITORES 1 // Nao pode haver mais de um escritor

int contadorDeLeitores = 0; // Contador de leitores
int contadorDeEscritores = 0; // Contador de escritores

sem_t sem_escritores; // Semaforo para controle de escritores
sem_t mutex;

// Controle de leitores
void *leitor(void *arg) {
    int id = *(int *)arg; // Recebe o id do leitor
    printf("Leitor %d entrou\n", id);

    sem_wait(&mutex); // Espera o mutex
    ++contadorDeLeitores;
    if (contadorDeLeitores == 1) // Se for o primeiro leitor, entra no semaforo de escritores
        sem_wait(&sem_escritores);
    sem_post(&mutex); // Libera o mutex
        
    printf("Leitor %d está lendo: %d, %d\n", id, contadorDeLeitores, contadorDeEscritores);   
    sleep(1); // Simula o tempo de leitura

    sem_wait(&mutex); // Espera o mutex
    contadorDeLeitores--; // Se o contador de leitores - 1 for igual a zero, libera o escritor
    if (contadorDeLeitores == 0) // Se o contador de leitores - 1 for igual a zero, libera o escritor
        sem_post(&sem_escritores);
    sem_post(&mutex); // Libera o mutex

    printf("Leitor %d saiu\n", id);

    pthread_exit(NULL); // Sai do leitor
}

// Controle de escritores
void *escritor(void *arg) {
    int id = *(int *)arg; // Recebe o id do escritor
  
    printf("Escritor %d entrou\n", id);

    sem_wait(&sem_escritores); // Espera o semaforo de escritores
    ++contadorDeEscritores; 
    printf("Escritor %d está escrevendo: %d, %d\n", id, contadorDeLeitores, contadorDeEscritores);
    sleep(1); // Simula o tempo de escrita
    --contadorDeEscritores; 
    sem_post(&sem_escritores); // Libera o semaforo de escritores

    printf("Escritor %d saiu\n", id); 
    
    pthread_exit(NULL); // Sai do escritor
}

int main() {
    int i;
    pthread_t leitores[N_LEITORES], escritores[N_ESCRITORES];
    int ids[N_LEITORES];

    sem_init(&mutex, 0, 1);                                    // inicializacao do semaforo de leitores
    sem_init(&sem_escritores, 0, MAX_ESCRITORES);               // inicializacao do semaforo de escritores

    for (i = 0; i < N_LEITORES; i++) {
        ids[i] = i;
        pthread_create(&leitores[i], NULL, leitor, &ids[i]);
    }

    for (i = 0; i < N_ESCRITORES; i++) {
        pthread_create(&escritores[i], NULL, escritor, &ids[i]);
    }

    for (i = 0; i < N_LEITORES; i++) {
        pthread_join(leitores[i], NULL);
    }

    for (i = 0; i < N_ESCRITORES; i++) {
        pthread_join(escritores[i], NULL);
    }

    sem_destroy(&sem_escritores);                               // destruir semaforo de escritores
    sem_destroy(&mutex);                                        // destruir semaforo do mutex

    return 0;
}