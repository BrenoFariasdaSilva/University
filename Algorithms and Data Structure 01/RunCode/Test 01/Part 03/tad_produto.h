#ifndef _TAD_PRODUTO_
#define _TAD_PRODUTO_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 100

/********************************************
 * DADOS
********************************************/
typedef struct estoque Produto;

/********************************************
 * OPERAÇÕES
********************************************/

/**
 * Cria dinamicamente o produto e preenche os atributos 
 * Parâmetro codigo: Código do produto a ser criado
 * Parâmetro descricao: Descrição do produto a ser criado
 * Parâmetro preco: Preço do produto a ser criado
 * RETORNO: endereço do Produto criado
 */
Produto* produto_criar(int codigo, char* descricao, double preco);

/**
 * Desaloca o Produto criado
 * Parâmetro endProduto: Endereço da variável que contém o ponteiro para o Produto a ser desalocado. 
 * A função também deve limpar o lixo de memória no endereço da variável recebido por parâmetro
 */
void produto_destruir(Produto** endProduto);

/**
 * Como os atributos do Produto estão encapsulados, essa função tem como objetivo prover o acesso
 * ao código do produto p. Portanto, a função devolve o código do produto p.
 * Parâmetro p: Ponteiro para a struct Produto.
 * RETORNO: o código do Produto p ou -1 em caso de erro.
 */
int produto_codigo(Produto* p);

/**
 * Como os atributos do Produto estão encapsulados, essa função tem como objetivo prover o acesso
 * a descrição do Produto p. Portanto, a função devolve a descrição do produto p.
 * A função deve usar a estratégia do scanf, copiando a string no endereço "saida" recebido por parâmetro.
 * Parâmetro p: Ponteiro para a struct Produto.
 * Parâmetro saida: Endereço de memória em a função deve copiar a string correspondente a descrição do produto.
 * RETORNO: true se a cópia foi realizada com sucesso ou false caso contrário. 
 */
bool produto_descricao(Produto* p, char* saida);

/**
 * Como os atributos do Produto estão encapsulados, essa função tem como objetivo prover o acesso
 * ao preço do produto p. Portanto, a função devolve o preço atual do produto p.
 * Parâmetro v: Ponteiro para a struct Produto.
 * RETORNO: o código do Produto p ou -1 em caso de erro.
 */
double produto_preco(Produto* p);

/**
 * Calcula a média dos últimos preços praticados (vetor ultimos_precos). Lembrando que o produto pode ter,
 * no máximo, os últimos 4 preços do produto. 
 * Parâmetro v: Ponteiro para a struct Produto.
 * RETORNO: a média dos preços ou -1 em caso de erro.
 */
double produto_media_preco(Produto* p);

/**
 * Altera o preço do produto. A alteração implica na manipulação do vetor ultimos_precos. Esse vetor pode
 * armazenar no máximo 4 valores. A função deve garantir que nesse vetor seja mantido sempre os últimos preços atribuídos ao produto.
 * Portanto, faça o gerenciamento correto desse vetor.
 * Parâmetro v: Ponteiro para a struct Produto.
 * Parâmetro preco: Preço a ser atribuído ao produto.
 * RETORNO: true caso a atribuição ocorra com sucesso e false caso contrário.
 */
bool produto_altera_preco(Produto* p, double preco);

#endif