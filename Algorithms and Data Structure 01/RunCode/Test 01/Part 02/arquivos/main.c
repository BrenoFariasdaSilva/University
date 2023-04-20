#include "tad_produto.h"
#include <string.h>

int main()
{
    printf("Testes \n");
    
    char string[100] = "Teclado Mtek";
    printf("string: %s \n", string);

    char *produtoDescricao = string;

    Produto* Prod1 = produto_criar (2, produtoDescricao, 100.50);

    printf("Verificando criação do Produto \n");
    printf("Produto->Codigo: %d \n", Prod1->codigo);
    printf("Produto->Descricao: %s \n", Prod1->descricao);
    printf("Produto->UltimosPrecos: %.2lf \n", Prod1->ultimos_precos[Prod1->qtd_precos - 1]);
    printf("Produto->QuantidadePrecos: %d \n\n", Prod1->qtd_precos);

    printf("Verificando a função - produto_codigo: %d \n\n", Prod1->codigo);
    int codigo = produto_codigo (Prod1);

    char resultString[100] = {0};
    char *produtoDescricaoResult = resultString;
    bool result = produto_descricao (Prod1, produtoDescricaoResult);
    printf("Verificando a função - produto_descricao: %s \n\n", resultString);

    double price = produto_preco (Prod1);
    printf("Verificando a função - produto_preco: Price: %.2lf  UltimosPrecos[QTD-1]: %.2lf \n\n", price, Prod1->ultimos_precos[Prod1->qtd_precos - 1]);

    double averagePrice = produto_media_preco (Prod1);
    printf("Verificando a função - produto_media_preco: %.2lf \n\n", averagePrice);
    
    printf("Verificando a função - produto_altera_preco: UltimosPrecos[QTD-1]: %.2lf \n\n", Prod1->ultimos_precos[Prod1->qtd_precos - 1]);
    produto_altera_preco (Prod1, 200.0);
    printf("Verificando a função - produto_altera_preco: UltimosPrecos[QTD-1]: %.2lf \n\n", Prod1->ultimos_precos[Prod1->qtd_precos - 1]);

    produto_destruir(&Prod1);

    return 0;
}