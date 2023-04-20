#ifndef _TAD_ESTOQUE_
#define _TAD_ESTOQUE_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tad_produto.h"

/********************************************
 * DADOS
********************************************/
typedef struct estoque Estoque;

/********************************************
 * OPERAÇÕES
********************************************/

/**
 * Cria dinamicamente um estoque de produtos e preenche seus atributos 
 * Parâmetro descricao: Descrição do estoque a ser criado
 * RETORNO: endereço da struct Estoque criada
 */
Estoque* estoque_criar(char* descricao);

/**
 * Desaloca a struct Estoque criada
 * Parâmetro endEstoque: Endereço da variável que contém o ponteiro para o Estoque a ser desalocado. 
 * A função também deve limpar o lixo de memória no endereço da variável recebido por parâmetro
 */
void estoque_destruir(Estoque** endEstoque);

// struct estoque
// {
//     char descricao[50];
//     Produto* vetor[TAM];
//     int qtde;
// };

/**
 * Insere um produto no final do vetor 
 * Parâmetro e: Ponteiro para a struct Estoque
 * Parâmetro p: Ponteiro para a struct Produto
 * RETORNO: true se a inserção ocorreu com sucesso e false caso contrário
 */
bool estoque_anexar(Estoque* e, Produto* p);

/**
 * Remove um produto com a descricao especificada 
 * Parâmetro e: Ponteiro para a struct Estoque
 * Parâmetro descricao: Descrição do produto a ser removido
 * RETORNO: índice do produto removido ou -1 caso contrário
 */
int estoque_remover_elemento(Estoque* e, char* descricao);

/**
 * Imprime a lista de produtos no estoque com o seguinte padrao
 * [(1,produtoA,5.5),(2,produtoB,7.7),(3,produtoC,2.1)]
 * Parâmetro e: Ponteiro para a struct Estoque
 */
void estoque_imprimir(Estoque* e);

#endif