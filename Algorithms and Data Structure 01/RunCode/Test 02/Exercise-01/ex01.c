#include "fila.h"
#include "string.h"

/**************************************
* FUNÇÕES AUXILIARES
**************************************/

No* CreateNode (TipoElemento element);
bool filaAnexar (Fila* f, No* NewNode);
bool InserirElementoUnico (Fila* f, No* NewNode);
bool InserirInicio (Fila* f, No* NewNode);
bool InserirMeio (Fila* f, No* NewNode, No* PreviousNode);

// Auxiliary Functions

No* CreateNode (TipoElemento element)
{
	No* Node = (No*) malloc (sizeof(No));
	Node->dado = element;
	Node->prox = NULL;

	return Node;
}

bool InserirElementoUnico (Fila* f, No* NewNode)
{
    if (f == NULL || NewNode == NULL) return false;

    f->inicio = f->fim = NewNode;
    f->qtde++; 
    
    return true;
}

bool filaAnexar (Fila* f, No* NewNode)
{
    if (f == NULL) return false;

    if (f->qtde == 0)
    {
       return (InserirElementoUnico (f, NewNode));
    }

    f->fim->prox = NewNode; 
    f->fim = NewNode;
    f->qtde++;

    return true;
} 

bool InserirInicio (Fila* f, No* NewNode)
{
    if (f == NULL) return false;

    if (f->qtde == 0)
    {
       return (InserirElementoUnico (f, NewNode));
    }

    NewNode->prox = f->inicio;
    f->inicio = NewNode;
    f->qtde++;

    return true;  
}

bool InserirMeio (Fila* f, No* NewNode, No* PreviousNode)
{
    if (f == NULL) return false;

    if (f->qtde == 0)
    {
       return (InserirElementoUnico (f, NewNode));
    }

    NewNode->prox = PreviousNode->prox;
    PreviousNode->prox = NewNode;
    f->qtde++;

    return true;  
}

bool fila_ehValida(Fila* f){
    return (f != NULL? true: false);   
}

/**************************************
* Exercício
**************************************/

Fila* fila_criar(int ordem)
{
    Fila* Queue = (Fila*) malloc (sizeof(Fila));
    Queue->inicio = NULL;
    Queue->fim = NULL;
    Queue->qtde = 0;
    Queue->ordem = ordem;

    return Queue;
}

bool fila_inserir(Fila* f, TipoElemento elemento)
{
    if (f == NULL)
	{
		return false;
	}

    No* NewNode = CreateNode (elemento);

    if (f->qtde == 0)
    {
        return (InserirElementoUnico (f, NewNode));
    }

    if (f->ordem == 1) // crescente
    {
        No* AuxiliaryNode = f->inicio;

        for (int i = 0; i < f->qtde; i++)
        {
            if (AuxiliaryNode->prox == NULL)
            {
                if (AuxiliaryNode->dado <= NewNode->dado)
                {
                    return (filaAnexar (f, NewNode));
                }

                return (InserirInicio (f, NewNode));
            }

            if (AuxiliaryNode->dado <= NewNode->dado && AuxiliaryNode->prox->dado >= NewNode->dado)
            {
                if (i == f->qtde - 1)
                {
                   filaAnexar (f, NewNode);
                }

                else
                {
                    InserirMeio (f, NewNode, AuxiliaryNode);
                }

                return true;
            }

            AuxiliaryNode = AuxiliaryNode->prox;
        }
    }

    if (f->ordem == -1) // decrescente
    {
        No* AuxiliaryNode = f->inicio;

        for (int i = 0; i < f->qtde; i++)
        {
            if (AuxiliaryNode->prox == NULL) 
            {
                if (AuxiliaryNode->dado <= NewNode->dado)
                {
                    return (InserirInicio (f, NewNode));
                }

                return (filaAnexar (f, NewNode));
            }

            if (AuxiliaryNode->dado >= NewNode->dado && AuxiliaryNode->prox->dado <= NewNode->dado)
            {
                if (i == f->qtde - 1)
                {
                   filaAnexar (f, NewNode);
                }

                else
                {
                    InserirMeio (f, NewNode, AuxiliaryNode);
                }

                return true;
            }

            AuxiliaryNode = AuxiliaryNode->prox;
        }
    }

    return true;
}