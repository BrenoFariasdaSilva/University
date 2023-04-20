#ifndef _TAD_VETOR_
#define _TAD_VETOR_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/********************************************
* DADOS
*******************************************/

struct vetor
{
    int* vet;
    int tamanho_vetor;
    int quantidade_elementos;
};

typedef struct vetor Vetor;

/********************************************
 * OPERAÇÕES
 *******************************************/

// 1. Criar um novo vetor
/**
 * Cria e inicializa a struct Vetor.
 * RETORNO: endereço da struct Vetor criada e inicializada na memória HEAP
 */
Vetor* vet_criar(int tam);

// 2. Inserir um elemento no final da sequência
/**
 * Insere o elemento na última posição do vetor. Caso não haja espaço disponível
 * para a inserção, você deve realocar o vetor, dobrando seu espaço disponível
 * Parâmetro v: Ponteiro para a struct Vetor em que o elemento será inserido.
 * Parâmetro elemento: Elemento a ser inserido.
 * RETORNO: true se a inserção foi realizada com sucesso e false caso contrário
 */
bool vet_anexar(Vetor* v, int elemento);

// 3. Inserir um elemento em qualquer posição da sequência
/**
 * Insere um elemento em uma determinada posição. Ao inserir um elemento na
 * posição, a função deve deslocar todos os elementos a sua direita. Caso não
 * haja espaço disponível para a inserção, você deve realocar o vetor,
 * dobrando seu espaço disponível
 * Parâmetro v: Ponteiro para a struct Vetor em que o elemento será inserido.
 * Parâmetro elemento: Elemento a ser inserido.
 * Parâmetro posicao: Posição em que o elemento deve ser inserido.
 * RETORNO: true se a inserção foi realizada com sucesso e false caso contrário
 */
bool vet_inserir(Vetor* v, int elemento, int posicao);

// 4. Substituir um elemento em uma determinada posição
/**
 * Substitui o valor de uma determinada posição do Vetor.
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro posicao: Posição a ser alterada.
 * Parâmetro novoElemento: elemento a ser atribuido na posição.
 * RETORNO: true se a alteração foi realizada com sucesso e false caso contrário
 */
bool vet_substituir(Vetor* v, int posicao, int novoElemento);

// 5. Remover um elemento de uma determinada posição
/**
 * USANDO A ESTRATÉGIA DO SCANF
 * Remove o elemento de uma determinada posição do vetor .
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro posicao: posição a ser removida.
 * Parâmetro endereco: endereço a ser utilizado para a copiar o valor do elemento removido.
 * RETORNO: true se a inserção foi realizada com sucesso e false caso contrário
 */
bool vet_removerPosicao(Vetor* v, int posicao, int* endereco);

// 6. Remover um elemento de acordo com o seu valor. Caso haja valores repetidos remover apenas a primeira ocorrência.
/**
 * Remove um determinado elemento do vetor .
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro elemento: elemento a ser removido.
 * RETORNO: posição do elemento removido e -1 caso contrário
 */
int vet_removerElemento(Vetor* v, int elemento);

// 7. Recuperar quantos elementos estão armazenados na sequência.
/**
 * Devolve a quantidade de elementos do vetor.
 * Parâmetro v: Ponteiro para a struct Vetor.
 * RETORNO: quantidade de elementos do vetor
 */
int vet_tamanho(Vetor* v);

// 8. Recuperar qual elemento está armazenado em uma determinada posição
/**
 * USANDO A ESTRATÉGIA DO SCANF
 * Pesquisa o elemento armazenado em uma determinada posição do Vetor.
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro posicao: posicao a ser encontrada.
 * Parâmetro saida: Endereço de memória onde a função deve armazenar o elemento encontrado.
 * RETORNO: Se a posição for válida, realiza a cópia no endereço recebido por parâmetro SAIDA e devolve true.
 *          Caso contrário, devolve false
 */
bool vet_elemento(Vetor* v, int posicao, int* saida);

// 9. Recuperar a posição em que um determinado elemento está armazenado. Caso haja valores repetidos, recuperar a primeira ocorrência.
/**
 * Pesquisa a posição de um determinado elemento no Vetor.
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro elemento: elemento a ser procurado.
 * RETORNO: Se encontrado, devolve a posição do elemento no vetor; caso contrário devolve -1
 */
int vet_posicao(Vetor* v, int elemento);

// 10. Imprimir a sequência
/**
 * Imprimir os elementos do vetor
 * Parâmetro v: Ponteiro para a struct Vetor.
 */
void vet_imprimir(Vetor* v);

// 11. Desalocar
/**
 * Destruir/Desalocar/liberar o vetor na memória HEAP
 * Parâmetro v: Ponteiro para a struct Vetor.
 */
void vet_desalocar(Vetor** v);

// 12. Devolve o vetor na forma de String
/**
 * Escreve no endereço recebido por parâmetro uma versão string do vetor
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro endereco: endereço da região de memória onde a função deverá copiar os caracteres.
 * RETORNO: true se a cópia foi realizada com sucesso e false caso contrário
 */

bool vet_toString(Vetor* v, char* enderecoString);

#endif
