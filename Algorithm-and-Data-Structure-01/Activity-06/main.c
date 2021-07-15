#include <stdio.h>
#include "tad_timer.h"

int main()
{
    Timer* t1 = timer_criar();

    long int soma = 0;
    double divisao = 1;
        
    int interacoes = 1000000000;

    printf("Executando %d de operacoes\n", interacoes);

    // Medir tempo para realizar operacoes

    timer_start(t1);

    for (int i = 0; i < interacoes; i++)
    {
        soma += i;
        divisao /= 2;
    }

    timer_stop(t1);

    printf("Tempo decorrido: %.2f\n\n", timer_resultado(t1));
     
    // Medir tempo para percorrer uma matriz

    long int linhas = 100000;
    long int colunas = 100000;
    
    printf("Executando %ld de operacoes\n", linhas*colunas);

    timer_reset(t1);
    timer_start(t1);

    for(long int i = 0; i < linhas; i++)
    {
        for(long int j = 0; j < colunas; j++)
        {
        }
    }

    timer_stop(t1);
    
    printf("Tempo decorrido: %.2f\n", timer_resultado(t1));
    
    timer_desalocar(&t1);

    return 0;
}