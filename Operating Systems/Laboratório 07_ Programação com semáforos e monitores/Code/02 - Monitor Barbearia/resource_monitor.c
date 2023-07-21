#include "resource_monitor.h"

void initMonitor(){
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_barbeiro, NULL);
    pthread_cond_init(&cond_cliente, NULL);

    cadeiras_ocupadas = 0;
    cadeiras_vazias = QUANT_CADEIRAS;
    clientes_atendidos = 0;
}

void destroyMonitor(){
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_barbeiro);
    pthread_cond_destroy(&cond_cliente);
}

void *barbeiro(void *arg)
{
    while (true)
    {
        pthread_mutex_lock(&mutex);

        while (cadeiras_ocupadas == 0)
        {
            pthread_cond_wait(&cond_barbeiro, &mutex);
        }

        printf("Barbeiro cortando o cabelo de alguem...\n");
        sleep(1);
        cadeiras_ocupadas--;
        cadeiras_vazias++;

        pthread_mutex_unlock(&mutex);
        printf("Barbeiro terminou de cortar!\n");
    }
}

void *cliente(void *arg)
{
    pthread_mutex_lock(&mutex);
    sleep(1);

    while (cadeiras_vazias == 0)
    {
        printf("Cliente viu que a barbearia estava cheia e foi embora...\n");
        //sleep(1);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    printf("Cliente entra na barbearia\n");
    //sleep(1);
    cadeiras_ocupadas++;
    cadeiras_vazias--;
    pthread_cond_signal(&cond_barbeiro);

    pthread_mutex_unlock(&mutex);

    return NULL;
}