#include "fila.h"
#include <string.h>

/**************************************
* DADOS
**************************************/

typedef struct no
{
    int dado;
    struct no* prox;
} No;

struct fila
{
    No* inicio;
    No* fim;
    int qtde;
};

// Prototypes

No* CreateNode (TipoElemento element);
bool DeallocateQueue (Fila* Queue);

// Auxiliary Functions

No* CreateNode (TipoElemento element)
{
	No* Node = (No*) malloc (sizeof(No));
	Node->dado = element;
	Node->prox = NULL;

	return Node;
}

bool DeallocateQueue (Fila* Queue)
{
    No* CurrentNode = Queue->inicio;
    Queue->inicio = Queue->inicio->prox;
    Queue->qtde--;
    free (CurrentNode);

    return true;
}

/**************************************
* IMPLEMENTAÇÃO
**************************************/

Fila* fila_criar()
{
    Fila* Queue = (Fila*) malloc (sizeof(Fila));
    Queue->inicio = NULL;
    Queue->fim = NULL;
    Queue->qtde = 0;

    return Queue;
}

void fila_destruir(Fila** enderecoFila)
{
    if (*enderecoFila == NULL)
	{
		return;
	}  

    for (int i = 0; i < (*enderecoFila)->qtde; i++)
	{
		DeallocateQueue (*enderecoFila);
	}

	free (*enderecoFila);
	*enderecoFila = NULL;
}

bool fila_inserir(Fila* f, TipoElemento elemento)
{
    if (f == NULL)
	{
		return false;
	}


	No* NewNode = CreateNode (elemento);
    f->fim->prox = NewNode; 
	f->qtde++;

    if (f->qtde == 0)
    {
        f->inicio = NewNode;
    }
    
    return true;
}

bool fila_remover(Fila* f, TipoElemento* saida)
{
    if (f == NULL || f->qtde == 0)
	{
		return false;
	}

    *saida = f->inicio->dado;
    No* Node = f->inicio;
    f->inicio = f->inicio->prox;
    free (Node);  
    f->qtde--; 

    return true;
}

bool fila_primeiro(Fila* f, TipoElemento* saida)
{
    if (f == NULL)
	{
		return false;
	}

    *saida = f->inicio->dado;

    return true;
}

bool fila_vazia(Fila* f)
{
    if (f == NULL || f->qtde == 0)
    {
        return false;
    }

    return false;
}

void fila_toString(Fila* f, char* saida)
{
    if (f == NULL)
	{
		return;
	}

    saida[0] = '\0';

    strcat(saida, "[");
    char element[20];
    No* CurrentNode = f->inicio;
    
    for (int i = 0; i < f->qtde; i++)
    {
        sprintf(element,"%d", CurrentNode->dado);

        if (i < f->qtde - 1)
        {
            strcat(saida, ",");    
        }

        No* CurrentNode = CurrentNode->prox;
    }
    
    strcat(saida, "]");
}