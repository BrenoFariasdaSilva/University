#include "tad_vetor.h"
#include <stdio.h>
#include <string.h>

// ************************************************* //
// Especificação dos dados
// ************************************************ //

// ******************************************* //
//  AUXILIARY FUNCTIONS
// ****************************************** //

bool initializeStruct (Vetor* structVector, const int size);
int* createVector (Vetor* structVector, const int size, bool copyContent);
bool copyVectorContent (Vetor* structVector, int* newVector, const int size);
bool deallocateVector (Vetor* structVector, int* newVector);
bool initializeVector (Vetor* structVector, const int size);
bool increaseElementsQuantity(Vetor* v);
bool decreaseElementsQuantity(Vetor* v);
bool AssignValueToCertainPosition (Vetor* v, const int position, const int element);
bool moveElements(Vetor* vector, const int element, const int position);
bool organizeElements(Vetor* v);
bool removeElementByPosition(Vetor* v, int posicao, int* endereco);
bool organizeElements(Vetor* v);
bool compareString(Vetor* v, char* enderecoString);
bool increaseVariablePlusPlus (int* variable);
int DigitsCount (int number);
// --------------------------------------------------------------------------------------------------

bool initializeStruct (Vetor* structVector, const int size)
{
    structVector->vet = createVector(structVector, size, false);
    initializeVector (structVector, size);
    structVector->quantidade_elementos = 0;

    return true;
}

int* createVector (Vetor* structVector, const int size, bool copyContent)
{
    int* newVector = NULL;  

    if (copyContent == true)
    {
        newVector = (int*) malloc ((2 * size) * sizeof(int));
        structVector->tamanho_vetor = (2 * size); 
        copyVectorContent(structVector, newVector, size);    
    }

    else
    {
        newVector = (int*) malloc (size * sizeof(int));
        structVector->tamanho_vetor = size;  
    }

    deallocateVector (structVector, newVector);

    return newVector;
}

bool copyVectorContent (Vetor* structVector, int* newVector, const int size)
{
    for (int i = 0; i < 2 * size; i++)
    {
        if (i < size)
        {
            newVector[i] = structVector->vet[i];
        }

        else
        { 
            newVector[i] = 0;
        }
    }

    return true;
}

bool deallocateVector (Vetor* structVector, int* newVector)
{
    free (structVector->vet);
    structVector->vet = newVector;

    return true;
}

bool initializeVector (Vetor* structVector, const int size)
{
    for (int i = 0; i < size; i++)
    {
        structVector->vet[i] = 0;
    }

    return true;
}

bool increaseElementsQuantity(Vetor* v)
{
    v->quantidade_elementos++;

    return true;
}

bool AssignValueToCertainPosition(Vetor* v, const int position, const int element)
{
    v->vet[position] = element;

    return true;
}

bool moveElements(Vetor* vector, const int element, const int position)
{
    for (int i = (vector->quantidade_elementos); i >= position; i--)
    {
        if (i == position)
        {
            vector->vet[i] = element;
        }

        else
        {
            vector->vet[i] = vector->vet[i-1];
        }
    }

    return true;
}

bool removeElementByPosition(Vetor* v, int posicao, int* endereco)
{
    *endereco = v->vet[posicao];
    v->vet[posicao] = 0;
    decreaseElementsQuantity(v);
    organizeElements(v);

    return true;
}

bool organizeElements(Vetor* v)
{
    for (int i = 0; i < v->quantidade_elementos; i++)
    {
        if (v->vet[i] == 0 && v->vet[i + 1] != 0)
        {
            int hold = v->vet[i + 1];
            v->vet[i] = hold;
            v->vet[i + 1] = 0;
        }
    }

    return true;
}

bool decreaseElementsQuantity(Vetor* v)
{
    v->quantidade_elementos--;

    return true;
}

bool increaseVariablePlusPlus (int* variable)
{
    (*variable)++;

    return true;
}

/********************************************
 * IMPLEMENTAÇÃO
 *******************************************/

// 1. Criar um novo vetor
/**
 * Cria e inicializa a struct Vetor.
 * RETORNO: endereço da struct Vetor criada e inicializada na memória HEAP
 */
Vetor* vet_criar(int tam)
{
    Vetor* newStructVariable = (Vetor*) malloc (sizeof(Vetor));

    initializeStruct (newStructVariable, tam);

    return newStructVariable;
}

// 2. Inserir um elemento no final da sequência
/**
 * Insere o elemento na última posição do vetor. Caso não haja espaço disponível
 * para a inserção, você deve realocar o vetor, dobrando seu espaço disponível
 * Parâmetro v: Ponteiro para a struct Vetor em que o elemento será inserido.
 * Parâmetro elemento: Elemento a ser inserido.
 * RETORNO: true se a inserção foi realizada com sucesso e false caso contrário
 */
bool vet_anexar(Vetor* v, int elemento)
{
    if ((v->quantidade_elementos) == (v->tamanho_vetor))
    {
       createVector(v, v->tamanho_vetor, true);
    }

    AssignValueToCertainPosition (v, v->quantidade_elementos, elemento);
    increaseElementsQuantity(v);

    return true;
}

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
bool vet_inserir(Vetor* v, int elemento, int posicao)
{
    if ((v->quantidade_elementos) == (v->tamanho_vetor))
    {
        createVector(v, v->tamanho_vetor, true);
        moveElements(v, elemento, posicao);
        increaseElementsQuantity(v);
    }

    else
    {
        moveElements(v, elemento, posicao);
        increaseElementsQuantity(v);
    }
}

// 4. Substituir um elemento em uma determinada posição
/*
 * Substitui o valor de uma determinada posição do Vetor.
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro posicao: Posição a ser alterada.
 * Parâmetro novoElemento: elemento a ser atribuido na posição.
 * RETORNO: true se a alteração foi realizada com sucesso e false caso contrário
*/
bool vet_substituir(Vetor* v, int posicao, int novoElemento)
{
    if (posicao < v->tamanho_vetor)
    {
        AssignValueToCertainPosition (v, posicao, novoElemento);
        return true;
    }

    return false;
}

// 5. Remover um elemento de uma determinada posição
/**
 * USANDO A ESTRATÉGIA DO SCANF
 * Remove o elemento de uma determinada posição do vetor .
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro posicao: posição a ser removida.
 * Parâmetro endereco: endereço a ser utilizado para a copiar o valor do elemento removido.
 * RETORNO: true se a inserção foi realizada com sucesso e false caso contrário
 */
bool vet_removerPosicao(Vetor* v, int posicao, int* endereco)
{
    if (posicao >= v->tamanho_vetor)
    {
        return false;
    }

    removeElementByPosition(v, posicao, endereco);

    return true;
}

// 6. Remover um elemento de acordo com o seu valor. Caso haja valores repetidos remover apenas a primeira ocorrência.
/**
 * Remove um determinado elemento do vetor .
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro elemento: elemento a ser removido.
 * RETORNO: posição do elemento removido e -1 caso contrário
 */
int vet_removerElemento(Vetor* v, int elemento)
{
    for (int i = 0; i < v->quantidade_elementos; i++)
    {
        if (v->vet[i] == elemento)
        {
            v->vet[i] = 0;
            decreaseElementsQuantity(v);
            organizeElements(v);
            return i;
        }
    }

    return -1;
}

// 7. Recuperar quantos elementos estão armazenados na sequência.
/**
 * Devolve a quantidade de elementos do vetor.
 * Parâmetro v: Ponteiro para a struct Vetor.
 * RETORNO: quantidade de elementos do vetor
 */
int vet_tamanho(Vetor* v)
{
    return v->quantidade_elementos;
}

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
bool vet_elemento(Vetor* v, int posicao, int* saida)
{
    if (posicao >= (v->quantidade_elementos))
    {
        return false;
    }

    *saida = v->vet[posicao];

    return true;
}

// 9. Recuperar a posição em que um determinado elemento está armazenado. Caso haja valores repetidos, recuperar a primeira ocorrência.
/**
 * Pesquisa a posição de um determinado elemento no Vetor.
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro elemento: elemento a ser procurado.
 * RETORNO: Se encontrado, devolve a posição do elemento no vetor; caso contrário devolve -1
 */
int vet_posicao(Vetor* v, int elemento)
{
    for (int i = 0; i < v->quantidade_elementos; i++)
    {
        if (v->vet[i] == elemento)
        {
            return i;
        }
    }

    return -1;
}

// 10. Imprimir a sequência
/**
 * Imprimir os elementos do vetor
 * Parâmetro v: Ponteiro para a struct Vetor.
 */
void vet_imprimir(Vetor* v)
{
    for (int i = 0; i < v->quantidade_elementos; i++)
    {
        printf("vet[%d] = %d \n", i, v->vet[i]);
    }
    printf("\n");
}

// 11. Desalocar
/**
 * Destruir/Desalocar/liberar o vetor na memória HEAP
 * Parâmetro v: Ponteiro para a struct Vetor.
 */
void vet_desalocar(Vetor** v)
{
    free (v);
    *v = NULL;
}

// 12. Devolve o vetor na forma de String
/**
 * Escreve no endereço recebido por parâmetro uma versão string do vetor
 * Parâmetro v: Ponteiro para a struct Vetor.
 * Parâmetro endereco: endereço da região de memória onde a função deverá copiar os caracteres.
 * RETORNO: true se a cópia foi realizada com sucesso e false caso contrário
 */
bool vet_toString(Vetor* v, char* saida)
{
    if (v->vet == NULL) 
    {
        return false;
    }

    saida[0] = '\0';
    strcat(saida, "[");

    for (int i=0; i < v->tamanho_vetor; i++)
    {
        char str[100];

        sprintf(str, "%d", v->vet[i]);
        strcat(saida, str);

        if (i < v->tamanho_vetor - 1) 
        {
            strcat(saida, ",");
        }
    }

    strcat(saida, "]");

    return true;
}