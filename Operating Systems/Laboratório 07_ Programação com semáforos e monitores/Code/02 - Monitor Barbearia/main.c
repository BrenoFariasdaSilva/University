/*
AUTORES: 
    BRENO FARIAS DA SILVA, 
    FELIPE ARCHANJO DA CUNHA MENDES
    JOAO HENRIQUE GOUVEIA

DESCRIÇÃO:
    Implementação do problema classico de concorrencia barbeiro dorminhoco usando monitores.

*/

#include "resource_monitor.h"

int main(int argc, char const *argv[]){
    // Variaveis de inicialização
    pthread_t barbeiro_t;
    pthread_t clientes_t[QUANT_MAX_CLIENTES];

    // Inicialização do monitor
    initMonitor();

    // Criação das threads
    pthread_create(&barbeiro_t, NULL, barbeiro, NULL);

    for (int i = 0; i < QUANT_MAX_CLIENTES; i++)
    {
        pthread_create(&clientes_t[i], NULL, cliente, NULL);
    }

    // Espera das threads
    pthread_join(barbeiro_t, NULL);

    for (int i = 0; i < QUANT_MAX_CLIENTES; i++)
    {
        pthread_join(clientes_t[i], NULL);
    }

    // Destruição das threads
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_barbeiro);
    pthread_cond_destroy(&cond_cliente);

    return 0;
}