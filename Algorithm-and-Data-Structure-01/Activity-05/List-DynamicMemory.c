#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Exercise 01
void inverte_string(char* str);
//Exercise 02
int qtde_vogais1(char* str);
void qtde_vogais2(char* str, int* saida);
//Exercise 03
char* copia_string(char* str);
//Exercise 04
int* cria_vetor1(int tam, int valor);
bool cria_vetor2(int tam, int valor, int** saida);
//Exercise 05
int* clone1(int tam, int valor);
bool clone2(int tam, int valor, int** saida);
//Exercise 06
int* aleatorio1(int tam);
bool aleatorio2(int tam, int** saida);
//Exercise 07
int dobra_tamanho(int** v, int tam);
//Exercise 08
int** cria_matriz(int linhas, int colunas, int valor);

/***********************************************
* FUNCOES AUXILIARES
************************************************/
void imprimir_vetor(int* v, int tam){
    printf("[");
    for (int i=0; i < tam; i++){
        printf("%d", v[i]);
        if(i<tam-1) printf(",");
    }
    printf("]");
}

void toString_vetor(int* v, int tam, char* saida){
    saida[0] = '\0';
    strcat(saida, "[");
    
    char elemento[20];
    for (int i=0; i < tam; i++){
        sprintf(elemento, "%d", v[i]);
        strcat(saida, elemento);
        if(i<tam-1) strcat(saida, ",");
    }
    strcat(saida, "]");
}

/***********************************************
* IMPLEMENTACAO
************************************************/

void inverte_string(char* str)
{
    int count = sizeof(str) + 1;

    char* AuxStr = (char*) malloc (count * sizeof (char));

    for (int i = 0; i < count; i++)
    {
        AuxStr[i] = str[i];
    } 

    printf("AuxStr %s \n", AuxStr);

    for (int i = 0, j = count - 2; i < count; i++, j--)
    {
        str[i] = AuxStr[j];
    } 

    str[count - 1] = '\0';

    free (AuxStr);
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
    int chars = 0;

    for(int i = 0; str[i] != '\0'; i++)
    {
        chars++;
    }

    const int Count = (chars * sizeof(char) + 1);

    printf("Count: %d \n", Count);

    char* CopyStr = (char*) malloc (Count * sizeof (char));

    for (int i = 0; i < Count; i++)
    {
        CopyStr[i] = str[i];
    }

    return CopyStr;  
}

int* cria_vetor1(int tam, int valor)
{
    if (tam < 1) return false;

    int* vet = (int*) malloc (tam * sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        vet[i] = valor;
    }
    
    return vet;
}

bool cria_vetor2(int tam, int valor, int** saida)
{
    if (tam < 1) return false;
    
    int* Vetor = (int*) malloc (tam * sizeof(int));

    *saida = Vetor;

    for (int i = 0; i < tam; i++)
    {
        Vetor[i] = valor;
    }
    
    return true;
}

int* vetor_cloneA(int valor, int tam)
{
    if (tam < 1) return false;

    int* vetor = valor;

    int* vet = (int*) malloc (tam * sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        vet[i] = vetor[i];
    }
    
    return vet;
}

bool vetor_cloneB(int valor, int tam, int** saida)
{
    if (tam < 1) return false;
    
    int* vector = valor;

    int* Vetor = (int*) malloc (tam * sizeof(int));

    *saida = Vetor;

    for (int i = 0; i < tam; i++)
    {
        Vetor[i] = vector[i];
    }
    
    return true;
}

int* aleatorio1(int tam)
{
    if (tam < 1) return false;

    int* vet = (int*) malloc (tam * sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        vet[i] = 1 + rand() % 10;
    }
    
    return vet;
}

bool aleatorio2(int tam, int** saida)
{
    if (tam < 1) return false;

    int* vet = (int*) malloc (tam * sizeof(int));

    *saida = vet;

    for (int i = 0; i < tam; i++)
    {
        vet[i] = 1 + rand() % 10;
    }
    
    return true;
}

int dobra_tamanho(int** v, int tam)
{
    if (tam < 1) return false;

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

    *v = vet;

    free (v);

    return (2 * tam);
}

int** cria_matriz(int linhas, int colunas, int valor)
{
    if (linhas < 1 || colunas < 1) return false;

    int** vetor;
    vetor = (int**) calloc (2, sizeof(int*));
    vetor[0] = (int*) calloc (linhas, sizeof(int));
    vetor[1] = (int*) calloc (colunas, sizeof(int));

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            vetor[i][j] = valor;
        }
    }

    return vetor;
}

