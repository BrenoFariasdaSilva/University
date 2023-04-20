#include "lista_incidencia.h"

Lista* lista_criar (int nos);
void lista_destruir (Lista** enderecoLista);
bool lista_temCaminho (Lista* l, int a, int b);
bool lista_inserirCaminho (Lista* l, int a, int b);
bool lista_removerCaminho (Lista* l, int a, int b);

// Auxiliary Functions.

No* CreateNode (int element);
bool ClearVectorPointers (Lista* List);
bool SearchNode (No* head, int element);
bool InsertNode (No**head, int data);
bool RemoveNode  (No**head, int element);
void DestroyNode (No* node);

No* CreateNode (int element)
{
	No* Node = (No*) malloc (sizeof(No));
	Node->dado = element;
	Node->prox = NULL;

	return Node;
}

bool ClearVectorPointers (Lista* List)
{
	if (!List) return false;

	for (int i = 0; i < List->nos; i++)
	{
		List->vetor[i] = NULL;
	}

	return true;
}

bool SearchNode (No* head, int element)
{
	if (!head) return false;

	No* AuxNode = head;

	while (AuxNode != NULL)
	{
		if(AuxNode->dado == element) return true;

		AuxNode = AuxNode->prox;
	}

	return false;
}

bool InsertNode (No** head, int data)
{
	No * node = CreateNode(data);

	if (!node) return false;

	// First element of the List.
	if(*head == NULL)
	{
		*head = node;
		return true;
	}

	node->prox = *head;
	*head = node;

	return true;
}

bool RemoveNode (No** head, int element)
{
	if (*head == NULL) return false;

	No* AuxNode = *head;
	No* NodeToRemove = NULL;

	if (AuxNode->dado == element)
	{
		*head = AuxNode->prox;
		NodeToRemove = AuxNode;
		DestroyNode (NodeToRemove);	
		return true;
	}
	
	while (AuxNode->prox->dado != element)
	{
		AuxNode = AuxNode->prox;
	}

	NodeToRemove = AuxNode->prox;
	AuxNode->prox = NodeToRemove->prox;

	DestroyNode (NodeToRemove);

	return true;
}

void DestroyNode (No* node)
{
	free(node);
	node = NULL;
}

// Exercise

Lista * lista_criar (int nos)
{
	if (nos <= 0) return NULL;

	Lista* List = (Lista*) malloc (sizeof (Lista));

	List->vetor = (No**) malloc (nos * sizeof(No*));

	ClearVectorPointers (List);

	List->nos = nos;
	
	return List;
}

bool lista_inserirCaminho (Lista* l, int a, int b)
{
	if (!l || a < 0 || b < 0 || a >= l->nos || b >= l->nos) return false;

	InsertNode (&l->vetor[a], b);
	InsertNode (&l->vetor[b], a);
	
	return true;
}

bool lista_temCaminho (Lista* l, int a, int b)
{
	if (!l || a < 0 || b < 0 || a >= l->nos || b >= l->nos || l->nos == 0) return false;

	return SearchNode (l->vetor[a], b);
}

bool lista_removerCaminho (Lista* l, int a, int b)
{
	if (!l || a < 0 || b < 0 || a >= l->nos || b >= l->nos || l->nos == 0) return false;

	if (lista_temCaminho (l, a, b) == false) return false;

	RemoveNode (&l->vetor[a], b);
	RemoveNode (&l->vetor[b], a);

	return true;
}

void lista_destruir (Lista **enderecoLista)
{
	if (*enderecoLista == NULL) return;

	for (int i = 0; i < (*enderecoLista)->nos; i++)
	{
		No* CurrentNode = (*enderecoLista)->vetor[i];

		while (CurrentNode != NULL) // Deallocate Node
		{
			No* AuxNode = CurrentNode->prox;
			DestroyNode (CurrentNode);
			// falta: CurrentNode=Aux;
			(*enderecoLista)->vetor[i] = CurrentNode;
		}
		
		(*enderecoLista)->vetor[i] = NULL;
	}
	
	free ((*enderecoLista)->vetor); // Deallocate Vector
	free (*enderecoLista); // Deallocate List

	(*enderecoLista) = NULL; // List aims to NULL
}

void lista_toString (Lista* l, char* saida)
{
	if (l == NULL) return;

    saida[0] = '\0';
    char string[100];

    for(int i=0; i < l->nos; i++)
	{
        sprintf(string, "[%d] ", i);
        strcat(saida, string);

        for(int j=0; j < l->nos; j++)
		{
            if (lista_temCaminho(l, i, j))
			{
                sprintf(string, "%d ", j);
                strcat(saida, string);
            }
        }

        strcat(saida, "\n");        
    }
}
