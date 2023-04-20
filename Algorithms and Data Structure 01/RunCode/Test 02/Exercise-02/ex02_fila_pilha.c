#include "fila.h"
#include "pilha.h"
#include "string.h"

/**************************************
* DADOS
**************************************/

struct fila
{
    Pilha* p1;
    Pilha* p2;    
    int qtde;
};

// Prototypes

bool MoveStack (Fila* Queue);

// Auxiliary Functions

bool MoveStack (Fila* Queue)
{
    if (Queue == NULL) return false;

    TipoElemento element;

    if (pilha_vazia(Queue->p1) != 0)
    {
        for (int i = 0; i < Queue->qtde; i++) 
        {
            pilha_desempilhar (Queue->p2, &element);
            pilha_empilhar (Queue->p1, element);
        }
    }
    
    else
    {
        for (int i = 0; i < Queue->qtde; i++) 
        {
            pilha_desempilhar (Queue->p1, &element);
            pilha_empilhar (Queue->p2, element);
        }
    }

    return true;
}

/**************************************
* Exercício
**************************************/

Fila* fila_criar()
{
    Fila* Queue = (Fila*) malloc (sizeof(Fila));
    Queue->p1 = pilha_criar();
    Queue->p2 = pilha_criar();
    Queue->qtde = 0;

    return Queue;
}

bool fila_inserir(Fila* f, TipoElemento elemento)
{
    if (f == NULL)
	{
		return false;
	}

	pilha_empilhar (f->p1, elemento);
	f->qtde++;
	return true;
}

void fila_destruir(Fila** enderecoFila)
{
    if (*enderecoFila == NULL)
	{
		return;
	}

    pilha_destruir (&(*enderecoFila)->p1);
    pilha_destruir (&(*enderecoFila)->p2);
    (*enderecoFila)->qtde = 0;
	free (*enderecoFila);
	*enderecoFila = NULL;
}

bool fila_remover(Fila* f, TipoElemento* saida) // estratégia do scanf
{
    if (f == NULL || f->qtde == 0 || saida == NULL)
	{
		return false;
	}

    MoveStack (f);
    pilha_desempilhar (f->p2, saida);
	f->qtde--;
    MoveStack (f);

	return true;
}

bool fila_primeiro(Fila* f, TipoElemento* saida) // estratégia do scanf
{
    if (f == NULL || f->qtde == 0 || saida == NULL)
	{
		return false;
	}

    MoveStack (f);
    pilha_topo (f->p2, saida);
    MoveStack (f);

	return true;
}

bool fila_vazia(Fila* f)
{
    if (f == NULL)
	{
		return false;
	}

	return (f->qtde == 0 ? true : false);
}

bool fila_toString(Fila* f, char* saida)
{
    if (f == NULL || saida == NULL)
    {
 		return false;
 	}

	TipoElemento elementoPilha;
    MoveStack (f);

    // Tentar usar o PilhaToString do Professor.
    // pilha_toString(f->p1, saida);
	
	saida[0] = '\0';
    strcat(saida, "[");

    for (int i = 0; i < f->qtde; i++)
    {
        char elemento[200];

        pilha_desempilhar(f->p2, &elementoPilha);

        //printf(elemento, "%d", elementoPilha);
        //memcpy(elemento,elementoPilha, sizeof(elementoPilha));
        sprintf(elemento, "%d", elementoPilha);
        strcat(saida, elemento);

        if (i < f->qtde - 1)
        {
            strcat(saida, ",");
        } 

        pilha_empilhar(f->p1, elementoPilha);
    }
    strcat(saida, "]");

 	return true;
}