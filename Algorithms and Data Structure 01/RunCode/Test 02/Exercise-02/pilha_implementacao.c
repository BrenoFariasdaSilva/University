#include "pilha.h"
#include <string.h>

typedef struct no{
	TipoElemento dado;
	struct no    *prox;
}No;

struct pilha{
	int qtde;
    No *topo;
};

/**************************************
* FUNÇÕES AUXILIARES
**************************************/

bool pilha_ehValida(Pilha* p){
    return (p != NULL? true: false);
}

No* criar_no(TipoElemento elemento, No* proximoNo){
    No* no = (No*) malloc(sizeof(No));
    no->dado = elemento;
    no->prox = proximoNo;
    return no;
}


/**************************************
* PROTÓTIPOS
**************************************/
Pilha* pilha_criar(){
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
    p->qtde = 0;
    return p;
}

void pilha_destruir(Pilha** endereco){
    Pilha* p = *endereco;
    if(!pilha_ehValida(p)) return;

    No* aux;
    while(p->topo != NULL){
        aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }

    free(p);
    *endereco = NULL;
}

bool pilha_empilhar(Pilha* p, TipoElemento elemento)
{
    if(!pilha_ehValida(p)) return false;

    No* novo = criar_no(elemento, NULL);
    novo->prox = p->topo;
    p->topo = novo;
    p->qtde++;
    
    return true;
}

bool pilha_desempilhar(Pilha* p, TipoElemento* saida)
{
     if(!pilha_ehValida(p)) return false;
    if(pilha_vazia(p)) return false;

    No* noRemovido = p->topo;
    p->topo = p->topo->prox;
    noRemovido->prox = NULL;
    p->qtde--;
    *saida = noRemovido->dado;
    free(noRemovido);

    return true;
}

bool pilha_topo(Pilha* p, TipoElemento* saida){
    if(!pilha_ehValida(p)) return false;
    if(pilha_vazia(p)) return false;

    *saida = p->topo->dado;
    return true;
}

bool pilha_vazia(Pilha* p){
    return p->qtde == 0;
}

int pilha_tamanho(Pilha* p){
    return p->qtde;
}

bool pilha_toString(Pilha* p, char* saida){
    if (!pilha_ehValida(p)) return false;

    saida[0] = '\0';
    strcat(saida, "[");
    char elemento[20];

    No* aux = p->topo;
    while(aux != NULL){
        sprintf(elemento,"%d", aux->dado);
        strcat(saida, elemento);
        if (aux->prox != NULL) strcat(saida, ",");
        aux = aux->prox;
    }
    strcat(saida, "]");
    return true;
}