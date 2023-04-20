#include "pilha.h"

typedef struct no
{
	TipoElemento dado;
	struct no *prox;
} No;

struct pilha
{
	int qtde;
	No *topo;
};

// Prototypes

No* CreateNode (TipoElemento element);
bool DeallocateNode (Pilha* Stack);

// Auxiliary Functions

No* CreateNode (TipoElemento element)
{
	No* Node = (No*) malloc (sizeof(No));
	Node->dado = element;
	Node->prox = NULL;

	return Node;
}

bool DeallocateNode (Pilha* Stack)
{
	if (Stack->topo == NULL)
	{
		return false;
	}

	No* Node = Stack->topo;
	Stack->topo = Stack->topo->prox;
	free (Node);

	return true;
}

/**************************************
* Main Functions
**************************************/

Pilha* pilha_criar()
{
	Pilha* Stack = (Pilha*) malloc (sizeof(Pilha));
	Stack->qtde = 0;
	Stack->topo = NULL;

	return Stack;
}

void pilha_destruir(Pilha** endereco)
{
	No* CurrentData = (*endereco)->topo->prox;

	for (int i = 0; i < (*endereco)->qtde; i++)
	{
		No* NextData = CurrentData->prox;
		free(CurrentData);
	}

	free (*endereco);
	*endereco = NULL;
}

bool pilha_empilhar(Pilha* p, TipoElemento elemento)
{
	if (p == NULL)
	{
		return false;
	}

	No* NewNode = CreateNode (elemento);
	NewNode->prox = p->topo;
	p->topo = NewNode;
	p->qtde++;

	return true;
}

bool pilha_desempilhar(Pilha* p, TipoElemento* saida)
{
	if (p == NULL || p->qtde == 0)
	{
		return false;
	}

	*saida = p->topo->dado;
	DeallocateNode (p); 
	
	p->qtde--;

	return true;
}

bool pilha_topo(Pilha* p, TipoElemento* saida)
{
	if (p == NULL)
	{
		return false;
	}

	*saida = p->topo->dado;

	return true;
}

bool pilha_vazia(Pilha* p)
{
	if (p == NULL)
	{
		return false;
	}

	return (p->qtde == 0 ? true : false);
}

void pilha_toString(Pilha* p, char* saida)
{
	if (p == NULL)
	{
		return;
	}

	saida[0] = '\0';
	No* auxNode = p->topo;

    strcat(saida, "[");
    for (int i = 0; i < p->qtde; i++)
	{
        char elemento[200];
        printf(elemento, "%d", auxNode->dado);
        strcat(saida, elemento);

        if (i < p->qtde - 1)
		{
			strcat(saida, ",");
		} 

		auxNode = auxNode->prox;
    }
    strcat(saida, "]");

	return;
}