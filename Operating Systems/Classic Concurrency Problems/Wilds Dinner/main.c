// Programação com Semáforos / Monitores
// Jantar de Selvagens:
// Restrições de Sincronização:
// - Selvagens podem se servir se tiver comida no caldeirão.
// - Apenas um selvagem pode se servir por vez.
// - Cozinheiro enche o caldeirão quando estiver vazio.
// - Se o caldeirão estiver vazio, o cozinheiro enche o.

// Thread - "Selvagem" (N)
// - serve_caldeirao
// - come

// Thread - "Cozinheiro" (1)
// - enche_caldeirao
// - descansa

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define MAX_PORCOES_CALDEIRAO 5			// caldeirao cheio
#define NUM_SELVAGENS 3

int porcoes;		          // numero de porcoes no caldeirao

sem_t mutex,                  // controla acesso concorrente dos selvagens
      caldeirao_reposto,      // sinaliza caldeirao reposto
      caldeirao_vazio;        // sinaliza caldeirao vazio

 
void* cozinheiro(void* data)
{
	while(1)
	{
		sem_wait(&caldeirao_vazio);

		printf("Cozinheiro: caldeirao vazio\n");
		printf("Cozinheiro: cozinhando porcoes\n");
		sleep(1);
		porcoes = MAX_PORCOES_CALDEIRAO;
		sem_post(&caldeirao_reposto);
	}
}

void* selvagem(void* data)
{
    int *id_selvagem = data;

    while(1)
    {
		sem_wait(&mutex);
		if (porcoes == 0) {
			sem_post(&caldeirao_vazio);
		 	sem_wait(&caldeirao_reposto);
		}

	  printf("Selvagem %d: servindo\n", *id_selvagem);
		sleep(1);
		porcoes--;
		sem_post(&mutex);
    printf("Selvagem %d está comendo \n", *id_selvagem);
	 }
}
 
int main()
{
    pthread_t selvagem_thread[NUM_SELVAGENS],
              cozinheiro_thread;
    int id_selvagem[NUM_SELVAGENS];
    
    porcoes = 0;    // considera-se inicialmente caldeirao vazio

    /* inicializa semáforos */
    sem_init(&mutex, 0, 1);
    sem_init(&caldeirao_vazio, 0, 0);        // quem verifica e avisa vazio sao os selvagens
    sem_init(&caldeirao_reposto, 0, 0);      // quem avisa da reposicao eh o cozinheiro
 
    /* cria as threads dos selvagens */ 
    for (int i=0; i<NUM_SELVAGENS; i++) {
        id_selvagem[i] = i;
        pthread_create(&selvagem_thread[i],NULL,selvagem, &id_selvagem[i]);
    }

    /* cria as threads do cozinheiro */
    pthread_create(&cozinheiro_thread,NULL,cozinheiro,NULL);

    pthread_join(cozinheiro_thread,NULL);
    
    return 0;
}
