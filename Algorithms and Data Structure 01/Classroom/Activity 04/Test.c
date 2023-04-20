#include <stdio.h>

typedef struct produto
{
    int codigo; //#100
    char descricao[12]; //#104
    float preco; //#116
} Produto;

int main() 
{
    Produto prod = {10, "Teclado", 98.50};

    Produto* p = &prod;
    int* pi = &prod.codigo;
    char* pc = prod.descricao;
    float* pf = &prod.preco;

    printf("%.2f \n", prod.preco);
    
    prod.preco = 10;
    p->preco = 10;
    *(pf) = 10;

    *(pi + 4) = (int) 10;  // Why is not working?
    //*(pc + 12) = 10;

    printf("%.2f \n", prod.preco);

    return 0;
}

