#include "tad_teste.h"
#include <stdlib.h>
#include <stdbool.h>

struct teste_criar
{
    //O QUE A STRUCT TEM QUE FAZER? 
};

Teste* teste_criar(char* descricao)
{
    printf("%s \n", descricao);
}

void teste_verificar(Teste* t, int condicao, char *mensagem)
{
    if (condicao == true)
    {
        printf("[OK]: Mensagem recebida por parametro \n");
    }

    else
    {
        printf("Erro: Mensagem recebida por parametro \n");
    }
}

void teste_relatorio(Teste* t)
{

}

void teste_desalocar(Teste** t)
{

}