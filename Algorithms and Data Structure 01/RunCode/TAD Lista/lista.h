#ifndef _LISTA_H_
#define _LISTA_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int TipoElemento;
#define FORMATO "%d"

/*-----------------------------------------------
DADOS
-------------------------------------------------*/
typedef struct lista Lista;

/*------------------------------------------------
PROTÓTIPOS
-------------------------------------------------*/

// Imprime a lista, simplesmente.
bool PrintList (Lista* List);

/**
 * @brief Cria e inicializa a lista
 *
 * @return Lista*: Endereço da lista criada
 */
Lista* lista_criar();

/**
 * @brief Desaloca a lista e limpa o lixo de memória
 *
 * @param endereco: Endereço de memória onde está o ponteiro da lista a ser desalocada
 */
void lista_destruir(Lista** endereco);

/**
 * @brief Insere o elemento no final da lista
 *
 * @param l: endereço para a lista
 * @param elemento: elemento a ser inserido
 * @return bool: 'true' quando o elemento for inserido com sucesso e false caso contrário
 */
bool lista_anexar(Lista* l, TipoElemento elemento);

/**
 * @brief Insere um elemento na lista em uma posição específica
 * Cenários que devem ser considerados na inserção
 * (a) inserção na lista está vazia
 * (b) inserção na primeira posição
 * (c) inserção na última posição
 * (d) inserção no meio
 *
 * @param l: endereço para a lista
 * @param elemento: elemento a ser inserido
 * @param posicao: posição na qual o elemento deve ser inserido na lista
 * @return bool: true se a inserção ocorreu corretamente e false caso contrário
 */
bool lista_inserir(Lista* l, TipoElemento elemento, int posicao);

/**
 * @brief Remove o elemento que ocupa uma posição específica da lista.
 * Cenários que devem ser considerados na remoção
 * (a) remoção na lista com um único elemento
 * (b) remoção da primeira posição
 * (c) remoção da última posição
 * (d) remoção do meio
 *
 * @param l: endereço para a lista
 * @param posicao: posição a ser removida
 * @param endereco: endereço de memória em que o elemento removido deve ser armazenado (devolvido)
 * @return bool: true se a remoção ocorreu corretamente e false caso contrário
 */
bool lista_removerPosicao(Lista* l, int posicao, TipoElemento* endereco);

/**
 * @brief Remove a primeira ocorrência do elemento na lista
 *
 * @param l: endereço para a lista
 * @param elemento: elemento a ser removido
 * @return int: índice do elemento que foi removido
 */
int lista_removerElemento(Lista* l, TipoElemento elemento);

/**
 * @brief Substitui o elemento que ocupa uma posição na lista.
 *
 * @param l: endereço da lista
 * @param posicao: posição a ser substituida
 * @param novoElemento: novo elemento que ocupará a posição
 * @return bool: true se a substituição ocorrer com sucesso e false caso contrário.
 */
bool lista_substituir(Lista* l, int posicao, TipoElemento novoElemento);

/**
 * @brief Devolve o índice que um elemento ocupa na lista
 *
 * @param l: endereço da lista
 * @param elemento: elemento a ser encontrado
 * @return int: posição que o elemento ocupa na lista ou -1 caso o elemento não seja encontrado.
 */
int lista_posicao(Lista* l, TipoElemento elemento);

/**
 * @brief Devolve o elemento que ocupa uma determinada posição da lista.
 *
 * @param l: endereço da lista
 * @param posicao: posição desejada
 * @param endereco: endereço de memória no qual será armazenado (devolvido) o elemento que ocupa a posição especificada
 * @return bool: true caso a posição exista e false caso contrário.
 */
bool lista_buscar(Lista* l, int posicao, TipoElemento* endereco);

/**
 * @brief Devolve a quantidade elementos da lista
 *
 * @param l: endereço da lista
 * @return int: quantidade de elementos
 */
int lista_tamanho(Lista* l);

/**
 * @brief Verifica se a lista está vazia.
 *
 * @param l: endereço da lista
 * @return bool: true caso a lista esteja vazia e false caso contrário.
 */
bool lista_vazia(Lista* l);

/**
 * @brief Devolve uma versão da lista no formato de string. O formato utilizado deve ser: [elem1,elem2,...,elemn]
 *
 * @param l: endereço da lista
 * @param str: endereço no qual a versão string será armazenada
 * @return bool: se a string for copiada ou false caso contrário.
 */
bool lista_toString(Lista* l, char* str);

#endif