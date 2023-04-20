#ifndef _PILHA_H
#define _PILHA_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef char TipoElemento;
/**************************************
* DADOS
**************************************/
typedef struct pilha Pilha;

/**************************************
* PROTÃ“TIPOS
**************************************/
Pilha* pilha_criar();
void pilha_destruir(Pilha** endereco);
bool pilha_empilhar(Pilha* p, TipoElemento elemento);
bool pilha_desempilhar(Pilha* p, TipoElemento* saida);
bool pilha_topo(Pilha* p, TipoElemento* saida);
bool pilha_vazia(Pilha* p);
void pilha_toString(Pilha* p, char* saida);

#endif

