#include "tad_vetor.h"

/***********************************************
* AUXILIARY FUNCTIONS
************************************************/

bool initializeQuantity (Vetor* v, int quantity)
{
    if (v == NULL || quantity < 0)
    {
        return false;
    }

    v->qtd = quantity;

    return true;
}

bool merge(Vetor* v1, Vetor* v2, Vetor* v3)
{
    Vetor* start = v1;
    Vetor* end = v2;

    if (v1->vet[0] > v2->vet[0])
    {
        start = v2; 
        end = v1;
    }

    for (int i = 0, j = 0; i < v3->tam; i++)
    {
        if (i < start->tam)
        {
            v3->vet[i] = start->vet[i];
        }

        else
        {
            v3->vet[i] = end->vet[j];
            j++;
        }
    }

    return true;
}

bool interperse (Vetor* v1, Vetor* v2, Vetor* v3)
{
    for (int i = 0, j = 0, k = 0; i < v3->qtd; i++)
    {
        if (((j < v1->qtd) && (v1->vet[j] < v2->vet[k])) || (k == v2->qtd))
        {
            v3->vet[i] = v1->vet[j];
            j++;
        }

        else
        {
            v3->vet[i] = v2->vet[k];
            k++;
        }
    }

    return true;
}

/***********************************************
* TEST 
************************************************/

Vetor* vet_concatena(Vetor* v1, Vetor* v2)
{
    Vetor* v3 = vet_criar((v1->qtd + v2->qtd)); 
    initializeQuantity (v3, (v1->qtd + v2->qtd));

    merge(v1, v2, v3); 

    return v3;
}

Vetor* vet_intercala(Vetor* v1, Vetor* v2)
{
    Vetor* v3 = vet_criar((v1->qtd + v2->qtd));
    initializeQuantity (v3, (v1->qtd + v2->qtd));
    
    interperse(v1, v2, v3);

    return v3;
}