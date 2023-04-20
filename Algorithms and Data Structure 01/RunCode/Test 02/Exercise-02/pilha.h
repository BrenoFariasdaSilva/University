#ifndef _PILHA_H
#define _PILHA_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef int TipoElemento;
/**************************************
* DADOS
**************************************/
typedef struct pilha Pilha;

/**************************************
* PROTÓTIPOS
**************************************/

Pilha* pilha_criar();
void pilha_destruir(Pilha** endereco);
bool pilha_empilhar(Pilha* p, TipoElemento elemento);
bool pilha_desempilhar(Pilha* p, TipoElemento* saida);
bool pilha_topo(Pilha* p, TipoElemento* saida);
bool pilha_vazia(Pilha* p);
int pilha_tamanho(Pilha* p);
// bool pilha_toString(Pilha* p, char* saida);

#endif