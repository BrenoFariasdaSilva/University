#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**************************************
* DADOS
**************************************/

typedef struct no
{
    int dado;
    struct no* prox;
} No;

typedef struct
{
    No* *vetor;
    int nos;
} Lista;


/**************************************
* FUNÇÕES
**************************************/

Lista* lista_criar(int nos);
bool lista_temCaminho(Lista* l, int a, int b);
bool lista_inserirCaminho(Lista* l, int a, int b);
bool lista_removerCaminho(Lista* l, int a, int b);
void lista_destruir (Lista** enderecoLista);
void lista_toString(Lista* l, char* saida);
