#include "List-DynamicMemory.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void inverte_string(char* str)
{
    int count = 0;

    for(; str[count] != '\0'; count++)
    {
    }

    for (int i = 0, j = count - 1; i < (count / 2); i++, j--)
    {
        char hold = str[i];
        str[i] = str[j];
        str[j] = hold;
    } 

}

int qtde_vogais1(char* str)
{
    int Count = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'A' || str[i] == 'a' || str[i] == 'E' || str[i] == 'e' || str[i] == 'I' || str[i] == 'i' ||str[i] == 'O' || str[i] == 'o' || str[i] == 'U' ||str[i] == 'u')
        {
            Count++;
        }
    }
    
    return Count;
}

void qtde_vogais2(char* str, int* saida)
{
    *saida = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'A' || str[i] == 'a' || str[i] == 'E' || str[i] == 'e' || str[i] == 'I' || str[i] == 'i' ||str[i] == 'O' || str[i] == 'o' || str[i] == 'U' ||str[i] == 'u')
        {
            (*saida)++;
        }
    }
}

char* copia_string(char* str)
{
    int chars = 1;

    for(int i = 0; str[i] != '\0'; i++)
    {
        chars++;
    }

    const int count = (chars * sizeof(char));

    char* CopyStr = (char*) malloc (count * sizeof (char));

    for (int i = 0; i < count; i++)
    {
        CopyStr[i] = str[i];
    }

    return CopyStr;  
}

int* cria_vetor1(int tam, int valor)
{
    if (tam < 1)
    {
        return false;
    } 
        
    int* vet = (int*) malloc (tam * sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        vet[i] = valor;
    }
    
    return vet;
}

bool cria_vetor2(int tam, int valor, int** saida)
{
    if (tam < 1)
    {
        return false;
    } 
    
    int* Vetor = (int*) malloc (tam * sizeof(int));

    *saida = Vetor;

    for (int i = 0; i < tam; i++)
    {
        Vetor[i] = valor;
    }

    return true;
}

int* clone1(int *valor, int tam)
{
    if (tam < 1)
    {
        return false;
    } 

    int* vector = (int*) malloc (tam * sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        vector[i] = valor[i];
    }
    
    return vector;
}

bool clone2(int *valor, int tam, int** saida)
{
    if (tam < 1)
    {
        return false;
    } 
    
    int* Vector = (int*) malloc (tam * sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        Vector[i] = valor[i];
    }

    *saida = Vector;
    
    return true;
}

int* aleatorio1(int tam)
{
    if (tam < 1)
    {
        return false;
    }

    int* vet = (int*) malloc (tam * sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        vet[i] = 1 + rand() % 9;
    }
    
    return vet;
}

bool aleatorio2(int tam, int** saida)
{
    if (tam < 1)
    {
        return false;
    }

    int* vet = (int*) malloc (tam * sizeof(int));

    *saida = vet;

    for (int i = 0; i < tam; i++)
    {
        vet[i] = rand() % 9;
    }
    
    return true;
}

int dobra_tamanho(int** v, int tam)
{
    if (tam < 1)
    {
        return false;
    } 

    int* vet = (int*) malloc ((2 *tam) * sizeof(int));

    for (int i = 0; i < 2 * tam; i++)
    {
        if (i < tam)
        {
            vet[i] = *(*v + i);
        }

        else
        {
            vet[i] = 0;
        }
    }

    free (v);
    *v = vet;

    return (2 * tam);
}

int** cria_matriz(int linhas, int colunas, int valor)
{
    if (linhas < 1 || colunas < 1)
    {
        return false;
    }

    int** vetor = (int**) malloc (linhas * sizeof(int*));
    
    for (int i = 0; i < linhas; i++)
    {
        vetor[i] = (int*) calloc (colunas, sizeof(int));
    }

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            vetor[i][j] = valor;
        }
    }

    return vetor;
}
