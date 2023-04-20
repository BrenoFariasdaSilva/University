#include "lista.h"
#include <string.h>

/*------------------------------------------------
Especificação dos dados
-------------------------------------------------*/

typedef struct no
{
	TipoElemento dado;
	struct no    *ant;
	struct no    *prox;
}No;

struct lista
{
	No *sentinela;
	int qtde;
};

/*------------------------------------------------
FUNÇÕES AUXILIARES
-------------------------------------------------*/

No* criar_no(TipoElemento elemento)
{
    No* no = (No*) malloc(sizeof(No));
    no->dado = elemento;
    no->prox = NULL;
    no->ant = NULL;
    return no;
}

No* devolver_enderecoNo(Lista* l, int posicao)
{
    No* aux = l->sentinela;
    for (int i=0; i <= posicao; i++) aux = aux->prox;
    return aux;
}

void insere_direita(No* referencia, No* no)
{
    no->prox = referencia->prox;
    no->ant = referencia;
    referencia->prox->ant = no;
    referencia->prox = no;
}


/*------------------------------------------------
Implementação das funções
-------------------------------------------------*/

Lista* lista_criar()
{
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->sentinela = (No*) malloc(sizeof(No));
    l->sentinela->prox = l->sentinela;
    l->sentinela->ant = l->sentinela;
    l->qtde = 0;
    return l;
}

void lista_destruir(Lista** endereco)
{
    Lista* l = *endereco;
    No* aux;
    TipoElemento e;
    while(l->qtde > 0){
        lista_removerPosicao(l, 0, &e);
    }
    free(l);
    *endereco = NULL;
}

bool lista_anexar(Lista* l, TipoElemento elemento)
{
    No *novo = criar_no(elemento);
    if(l->qtde == 0)
    {
        l->sentinela->prox = novo;
        l->sentinela->ant = novo;
        l->qtde++;
        return true;
    }

    No *aux = l->sentinela->ant;
    aux->prox = novo;
    novo->ant = aux;
    l->sentinela->ant = novo;
    l->qtde++;

    return true;
}

bool lista_inserir(Lista* l, TipoElemento elemento, int posicao)
{
    if (l == NULL) return false;

    No* novo = criar_no(elemento);
    No* aux = devolver_enderecoNo(l, posicao-1);

    insere_direita(aux, novo);

    l->qtde++;
    return true;
}

bool lista_removerPosicao(Lista* l, int posicao, TipoElemento* endereco)
{
    if (posicao >= l->qtde) return false;

    No *aux = l->sentinela;

    for (int i = 0; i < posicao; i++)
    {
        aux = aux->prox;
    }

    aux->prox = aux->prox->prox;
    aux->prox->ant = aux;
    l->qtde--;

    return true;
}

int lista_removerElemento(Lista* l, TipoElemento elemento)
{
    No *aux = l->sentinela;

    int i;

    for (i = 0; i < l->qtde; i++)
    {
        if (aux->dado == elemento) break;
        aux = aux->prox;
    }

    if (aux->dado != elemento) return 0;

    if (i =! 0) 
    {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }

    else
    {
        l->sentinela = aux->prox;
        aux->prox->ant = NULL;
    }

    l->qtde--;

    return aux->dado;
}

bool lista_substituir(Lista* l, int posicao, TipoElemento novoElemento)
{
    if (posicao >= l->qtde) return false;

    No *aux = l->sentinela;
    for (int i = 0; i < posicao; i++)
    {
        aux = aux->prox;
    }

    aux->dado = novoElemento;

    return true;
}

int lista_posicao(Lista* l, TipoElemento elemento)
{
    No *aux = l->sentinela;

    int i;
    for (i = 0; i < l->qtde; i++)
    {
        if (aux->dado == elemento) break;
        aux = aux->prox;
    }

    if (aux->dado != elemento) return -1;

    return i;
}

bool lista_buscar(Lista* l, int posicao, TipoElemento* endereco)
{
    if (posicao >= l->qtde) return false;

    No *aux = l->sentinela;

    for (int i = 0; i < posicao; i++)
    {
        aux = aux->prox;
    }

    endereco = &aux->dado;

    return true;
}

int lista_tamanho(Lista* l)
{
    return l->qtde;
}

bool lista_vazia(Lista* l)
{
    if (l->qtde == 0) return true;
    return false;
}

bool lista_toString(Lista* l, char* str)
{
    char elemento[20];

    str[0] = '\0';
    strcat(str, "[");
    No* aux = l->sentinela->prox;

    for (int i = 0; i < l->qtde; ++i)
    {
        sprintf(elemento, FORMATO, aux->dado);
        strcat(str, elemento);
        if(l->qtde - i > 1) strcat(str, ",");
        aux = aux->prox;
    }

    strcat(str, "]");
    
    return true;
}