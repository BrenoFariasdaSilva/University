#include "tad_produto.h"

struct produto
{
    int codigo;
    char descricao[50]; //
    double ultimos_precos[4]; // armazena no máximo os últimos 4 preços praticados
    int qtd_precos; // quantidade de preços armazenados no vetor ultimos_precos
};

// Prototypes

bool InitialiseProduct (Produto* p ,int codigo, char* descricao, double preco);
bool CopyString (Produto* Output, char* Source);
bool InitialiseLastPricesToZero (Produto* Product);
bool ValidStringInput (char* Source);
bool MoveElements (Produto* p);
bool InsertPrice (Produto* p, double preco);
bool IncreaseElementsQuantity (Produto* p);

// Auxiliary Functions.

bool InitialiseProduct (Produto* p ,int codigo, char* descricao, double preco)
{
    if (p == NULL)
    {
        return false;
    }

    p->codigo = codigo;
    
    CopyString (p, descricao);

    p->qtd_precos = 0;
    p->ultimos_precos[p->qtd_precos] = preco;
    InitialiseLastPricesToZero (p);
    IncreaseElementsQuantity(p);

    return true;
}

bool CopyString (Produto* Output, char* Source)
{
    bool StringValidation = ValidStringInput(Source);

    if (StringValidation == false)
    {
        return false;
    }

    int StringSize = strlen (Source) + 1; // StrLen + 1 == String + \0

    for (int i = 0; i < StringSize; i++) 
    {
        Output->descricao[i] = Source[i];
    }

    return true; 
}

bool InitialiseLastPricesToZero (Produto* Product)
{
    for (int i = 1; i < 4; i++)
    {
        Product->ultimos_precos[i] = 0;
    }

    return true;
}

bool ValidStringInput (char* Source)
{
    if (Source[0] == '\0')
    {
        return false;
    }

    return true;
}

bool MoveElements (Produto* p)
{
    for (int i = 0; i < 3; i++)
    {
        p->ultimos_precos[i] = p->ultimos_precos[i + 1];
    }

    return true;
}

bool InsertPrice (Produto* p, double preco) // Desnecessário
{
    if (p->qtd_precos != 4)
    {
        IncreaseElementsQuantity(p);
    }

    p->ultimos_precos[(p->qtd_precos) - 1] = preco;
    
    return true;
}

bool IncreaseElementsQuantity (Produto* p) //Apagaria
{
    p->qtd_precos++;

    return true;
}

// Implementation.

Produto* produto_criar(int codigo, char* descricao, double preco)
{
    Produto* Product = (Produto*) malloc (sizeof (Produto));

    InitialiseProduct (Product, codigo, descricao, preco);

    return Product;
}

void produto_destruir(Produto** endProduto)
{
    free (*endProduto);

    *endProduto = NULL;
}

int produto_codigo(Produto* p)
{
    if (p->codigo == 0)
    {
        return -1;
    }

    return p->codigo;
}

bool produto_descricao(Produto* p, char* saida)
{
    // DataValidation
    if (p->descricao[0] == '\0')
    {
        return false;
    }

    int StringSize = strlen (p->descricao);

    for (int i = 0; i < StringSize + 1; i++)
    {
        saida[i] = p->descricao[i];
    }

    return true;
}

double produto_preco(Produto* p)
{
    if (p->qtd_precos == 0)
    {
        return -1;
    }

    double Price = p->ultimos_precos[(p->qtd_precos) - 1];

    return Price;
}

double produto_media_preco(Produto* p)
{
    if (p->qtd_precos == 0)
    {
        return -1;
    }

    double average = 0;

    for (int i = 0; i < p->qtd_precos; i++)
    {
        average += p->ultimos_precos[i];
    }

    average /= p->qtd_precos;
    
    return average;
    
}

bool produto_altera_preco(Produto* p, double preco)
{
    if (p == NULL || preco == 0)
    {
        return false;
    }

    if (p->qtd_precos == 4)
    {
        MoveElements (p);
    }

    InsertPrice (p, preco);

    return true;
}