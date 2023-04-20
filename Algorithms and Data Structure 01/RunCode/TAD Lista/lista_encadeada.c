#include "lista.h"
#include <string.h>	

/*------------------------------------------------
Especificação dos dados
-------------------------------------------------*/

typedef struct no
{
	TipoElemento dado;
	struct no *ant;
	struct no *prox;
} No;

struct lista
{
	No *inicio;
	No *fim;
	int qtde;
};

// ---------------- Prototypes ----------------- //

bool InitializeList (Lista* List);
No* CreateNewNode (Lista * List,TipoElemento element);
bool DeallocateNode (Lista* List, No* CurrentNode);
No* ListFromBeginning (Lista* List, int position);
No* ListFromEnd (Lista* List, int position);
int SearchElement (Lista* List, TipoElemento Element, No** CurrentNode);

// ------------- Auxiliary Functions ---------- //

bool InitializeList (Lista* List)
{
	if (List == NULL) return false;

	List->inicio = NULL;
	List->fim = NULL;
	List->qtde = 0;

	return true;
}

No* CreateNewNode (Lista * List,TipoElemento element)
{
	No* NewNode = (No*) malloc (sizeof (No));
	NewNode->dado = element;
	NewNode->ant = NULL;
	NewNode->prox = NULL;

	List->qtde++;

	return NewNode;
}

bool DeallocateNode (Lista* List, No* CurrentNode)
{
	if (List == NULL || CurrentNode == NULL) return false;

	if(List->inicio == List->fim)
	{
		List->fim = List->inicio = NULL;
	}

	else if (List->inicio == CurrentNode)
	{
		List->inicio = CurrentNode->prox;
	}

	else if (List->fim == CurrentNode)
	{
		List->fim = CurrentNode->ant;
	}

	else
	{
		(CurrentNode->ant)->prox = CurrentNode->prox;
		(CurrentNode->prox)->ant = CurrentNode->ant;
	}

    free (CurrentNode);
	CurrentNode = NULL;

    List->qtde--;

    return true;
}

No* ListFromBeginning (Lista* List, int position)
{
	if (List == NULL || position >List->qtde || List->qtde == 0) return false;

	No* Node = List->inicio;

	for (int i = 0; i < position; i++)
	{
		Node = Node->prox;
	}

	return Node;
}

No* ListFromEnd (Lista* List, int position)
{
	if (List == NULL || position > List->qtde || List->qtde == 0) return false;

	No* Node = List->fim;

	for (int i = List->qtde-1; position < i; i--)
	{
		Node = Node->ant;
	}

	return Node;
}

int SearchElement (Lista* List, TipoElemento Element, No** CurrentNode)
{
	if (List == NULL || (*CurrentNode) == NULL || List->qtde == 0) return false;

	for (int i = 0; i < List->qtde; i++)
	{
		if ((*CurrentNode)->dado == Element)
		{
			return i;
		}

		*CurrentNode = (*CurrentNode)->prox;
	}

	return -1; // Element not found
}

bool PrintList (Lista* List)
{
	No* Node = List->inicio;

	for (int i = 0; i < List->qtde; i++)
	{
		printf("%d ", Node->dado);
		Node = Node->prox;
	}

	printf("\n");

	return true;
}

/*------------------------------------------------
Implementação das funções
-------------------------------------------------*/

Lista* lista_criar()
{
	Lista* List = (Lista*) malloc (sizeof (Lista));
	InitializeList (List);

	return List;
}

void lista_destruir(Lista** endereco)
{
	if (*endereco == NULL) return;

	while ((*endereco)->qtde != 0)
	{
		No* CurrentNode = (*endereco)->inicio;
		DeallocateNode (*endereco, CurrentNode);
	}
}

bool lista_anexar(Lista* l, TipoElemento elemento)
{
	if (l == NULL) return false;

	No* NewLastNode = CreateNewNode (l, elemento);

	if (l->qtde == 1) 
	{
		l->inicio = NewLastNode;
	}
	
	else
	{
		(l->fim)->prox = NewLastNode;	
		NewLastNode->ant = l->fim; 
	}

	l->fim = NewLastNode;
	
	return true;
}

bool lista_inserir(Lista* l, TipoElemento elemento, int posicao)
{
	if (l == NULL || posicao > l->qtde) return false;

	if (posicao < 0)
	{
		posicao = l->qtde + posicao;
	}

	if (posicao == l->qtde) 
	{
		lista_anexar (l, elemento);
		return true;
	}

	No* NewNode = CreateNewNode (l,elemento);

	if(posicao == 0)
	{
		NewNode->prox = l->inicio;
		l->inicio->ant = NewNode;
		l->inicio = NewNode;

		return true;
	}
	
	No* CurrentNode = NULL;

	if (posicao <= l->qtde / 2)
	{
		CurrentNode = ListFromBeginning (l, posicao);
	}

	else
	{
		CurrentNode = ListFromEnd (l, posicao);
	}

	NewNode->ant = CurrentNode->ant;
	NewNode->prox = CurrentNode;

	CurrentNode->ant->prox = NewNode;
	CurrentNode->ant = NewNode;

	return true;
}

bool lista_removerPosicao(Lista* l, int posicao, TipoElemento* endereco)
{
	if (l == NULL || posicao > l->qtde) return false;

	No* CurrentNode = NULL;

	if (posicao <= l->qtde / 2)
	{
		CurrentNode = ListFromBeginning (l, posicao);
	}

	if (posicao > l->qtde / 2)
	{
		CurrentNode = ListFromEnd (l, posicao);
	}

	*endereco = CurrentNode->dado;
	DeallocateNode(l, CurrentNode);

	return true;
}

int lista_removerElemento(Lista* l, TipoElemento elemento)
{
	if (l == NULL) return false;

	No* CurrentNode = l->inicio;
	int Position = SearchElement (l, elemento, &CurrentNode);

	DeallocateNode(l, CurrentNode);

	return Position;
}

bool lista_substituir(Lista* l, int posicao, TipoElemento novoElemento)
{
	if (l == NULL) return false;

	No* CurrentNode = NULL;

	if (posicao < l->qtde / 2)
	{
		CurrentNode = ListFromBeginning (l, posicao);
	}

	if (posicao > l->qtde / 2)
	{
		CurrentNode = ListFromEnd (l, posicao);
	}

	CurrentNode->dado = novoElemento;

	return true;
}

int lista_posicao(Lista* l, TipoElemento elemento)
{
	if (l == NULL) return false;

	int index = SearchElement (l, elemento, &(l->inicio));

	return index;
}

bool lista_buscar(Lista* l, int posicao, TipoElemento* endereco)
{
	if (l == NULL) return false;

	if (posicao < 0)
	{
		posicao = l->qtde + posicao + 1;
	}

	No* CurrentNode = NULL;

	if (posicao < l->qtde / 2)
	{
		CurrentNode = ListFromBeginning (l, posicao);
	}

	if (posicao > l->qtde / 2)
	{
		CurrentNode = ListFromEnd (l, posicao);
	}

	*endereco = CurrentNode->dado;

	return true;
}

int lista_tamanho(Lista* l)
{
	if (l == NULL) return false;

	return (l->qtde);
}

bool lista_vazia(Lista* l)
{
	if (l == NULL || l->qtde != 0) return false;

	if (l->qtde == 0) return true;
}

bool lista_toString(Lista* l, char* str)
{
	if (l == NULL) return false;

    str[0] = '\0';

    strcat(str, "[");
    char element[20];
    No* CurrentNode = l->inicio;
    
    for (int i = 0; i < l->qtde; i++)
    {
        sprintf(element,"%d", CurrentNode->dado);

        if (i < l->qtde - 1)
        {
            strcat(str, ",");    
        }

        No* CurrentNode = CurrentNode->prox;
    }
    
    strcat(str, "]");

	return true;
}
