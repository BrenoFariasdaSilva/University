#include "pilha.h"

#define TAM_INICIAL 5

struct pilha {
    int qtde;
    int tam;
    TipoElemento* vetor;
};

void verifica_aumenta(Pilha* p);
void verifica_diminui(Pilha* p);
bool pilha_valida(Pilha* p){
    return (p != NULL ? true : false);
}

/**************************************
* PROTÓTIPOS
**************************************/
Pilha* pilha_criar(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->vetor = (TipoElemento*) calloc(TAM_INICIAL, sizeof(TipoElemento));
    p->tam = TAM_INICIAL;
    p->qtde = 0;
    return p;
}


void pilha_destruir(Pilha** endereco){
    Pilha* p = *endereco;
    if(!pilha_valida(p)) return;

    free(p->vetor);
    free(p);
    *endereco = NULL;
}

bool pilha_empilhar(Pilha* p, TipoElemento elemento){
    if(!pilha_valida(p)) return false;

    // verifica_aumenta(p);
    p->vetor[p->qtde++] = elemento;
    return true;
}

bool pilha_desempilhar(Pilha* p, TipoElemento* saida){
    if(!pilha_valida(p)) return false;

    // verifica_diminui(p);
    *saida = p->vetor[p->qtde-1];
    p->qtde--;
    return true;
}


bool pilha_topo(Pilha* p, TipoElemento* saida){
    if(!pilha_valida(p)) return false;

    *saida = p->vetor[p->qtde-1];
    return true;
}

bool pilha_vazia(Pilha* p){
    if(!pilha_valida(p)) return false;
    return (p->qtde == 0 ? true : false);
}

void pilha_toString(Pilha* p, char* saida){
    if(!pilha_valida(p)) return;

    saida[0] = '\0';
    strcat(saida, "[");
    for (int i=p->qtde-1; i >= 0; i--){
        char elemento[200];
        sprintf(elemento, "%d", p->vetor[i]);
        strcat(saida, elemento);
        if(i > 0) strcat(saida, ",");
    }
    strcat(saida, "]");
}