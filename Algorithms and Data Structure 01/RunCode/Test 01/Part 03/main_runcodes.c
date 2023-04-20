#include "tad_estoque.h"

int main()
{
    Estoque* Estoque = estoque_criar("estoque 01");

    // Teste Para as Funções:
    // estoque_anexar
    // estoque_imprimir
    
    int quantidade = 0;
    scanf("[%d] ", &quantidade);

    for (int i = 0; i < quantidade; i++)
    {
        int codigo = 0;
        char descricao[100] = {0};
        float preco = 0.0;

        scanf("%d %f %s", &codigo, &preco, descricao);
        Produto* Produto = produto_criar(codigo, descricao, preco);
        estoque_anexar(Estoque, Produto);
    }

    estoque_imprimir(Estoque);
    printf("\n");

    // Teste Para as Funções:
    // estoque_remover_elemento
    // estoque_imprimir
    // estoque_destruir

    scanf("[%d] ", &quantidade);

    for (int i = 0; i < quantidade; i++)
    {
        char descricao[100] = {0};
        scanf("%s", descricao);
        estoque_remover_elemento(Estoque, descricao);
    }

    estoque_imprimir(Estoque);

    estoque_destruir(&Estoque);
    
    return 0;
}