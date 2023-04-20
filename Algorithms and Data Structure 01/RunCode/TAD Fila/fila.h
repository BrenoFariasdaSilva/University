#ifndef _FILA_H_
#define _FILA_H_

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef int TipoElemento;

/**************************************
* DADOS
**************************************/
typedef struct fila Fila;

/**************************************
* PROTÓTIPOS
**************************************/
Fila* fila_criar();
void fila_destruir(Fila** enderecoFila);
bool fila_inserir(Fila* f, TipoElemento elemento);
bool fila_remover(Fila* f, TipoElemento* saida); // estratégia do scanf
bool fila_primeiro(Fila* f, TipoElemento* saida); // estratégia do scanf
bool fila_vazia(Fila* f);
void fila_toString(Fila* f, char* saida);

#endif