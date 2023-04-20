#include "tad_estoque.h"

#define TAM 100

struct estoque
{
    char descricao[50];
    Produto* vetor[TAM];
    int qtde;
};

// Prototypes

bool InitialiseProduct (Estoque* Products, char* Name);
bool CopyString (Estoque* Output, char* Source);
bool IncreaseElementsQuantity (Estoque* Products);
bool DecreaseElementsQuantity (Estoque* Products);
bool SortVector (Estoque* Products, const int startValue);

// Auxiliary Functions.

bool InitialiseProduct (Estoque* Products, char* Name)
{
    CopyString (Products, Name);

    Products->qtde = 0;

    return true;
}

bool CopyString (Estoque* Output, char* Source)
{
    int StringSize = strlen (Source) + 1;

    for (int i = 0; i < StringSize; i++) 
    {
        Output->descricao[i] = Source[i];
    }

    return true; 
}

bool IncreaseElementsQuantity (Estoque* Products)
{
   Products->qtde++; 

   return true; 
}

bool DecreaseElementsQuantity (Estoque* Products)
{
   Products->qtde--; 

   return true; 
}

bool SortVector (Estoque* Products, const int startValue)
{
    if (Products == NULL || startValue < 0)
    {
        return false;
    }

    for (int i = startValue; i < Products->qtde; i++) 
    {
        Products->vetor[i] = Products->vetor[i + 1]; //1 0 2 3 - 1 2 3 0
    }

    return true;
}

// Implementation.

Estoque* estoque_criar(char* descricao)
{
    Estoque* Product = (Estoque*) malloc(sizeof(Estoque));

    InitialiseProduct (Product, descricao);

    return Product;
}

void estoque_destruir(Estoque** endEstoque)
{
    free (*endEstoque);
    *endEstoque = NULL;
}

bool estoque_anexar(Estoque* e, Produto* p)
{
    if (e == NULL || p == NULL)
    {
        return false;
    }

    e->vetor[e->qtde] = p;

    IncreaseElementsQuantity(e); 

    return true;
}

int estoque_remover_elemento(Estoque* e, char* descricao)
{
    char String[TAM] = {0};

    for (int i = 0; i < e->qtde; i++)
    {
        produto_descricao(e->vetor[i], String);

        if (strcmp (descricao, String) == 0)
        {
            produto_destruir (&(e->vetor[i]));
            DecreaseElementsQuantity(e);
            SortVector(e, i);
            return i;
        }
    }

    return -1;
}

void estoque_imprimir(Estoque* e)
{
    printf("[");

    for (int i = 0; i < e->qtde; i++)
    {
        char String[TAM] = {0};
        produto_descricao(e->vetor[i], String);

        double Price = produto_preco (e->vetor[i]);

        int Code = produto_codigo (e->vetor[i]);

        printf("(%d,%s,%.2f)", Code, String, Price);

        if (i != e->qtde - 1)
        {
            printf(",");
        }
    }

    printf("]");
}