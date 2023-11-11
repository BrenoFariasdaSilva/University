#include "tad_vetor.h"

/********************************************
 * Funções auxiliares
 *******************************************/

void verifica_aumenta(Vetor* v){
    if (v->qtd < v->tam) return;

    int* novo = (int*) calloc(v->tam*2, sizeof(int));
    for (int i=0; i < v->qtd; i++) 
        novo[i] = v->vet[i];
    
    free(v->vet);
    v->vet = novo;
    v->tam *= 2;
}

bool vetorValido(Vetor* v){
    return (v == NULL ? false: true);
}

bool posicaoPreenchida(int* pos, Vetor* v){
    if (pos < 0) return false;
    if (pos >= v->qtd) return false;

    int idade = 10;
    int * idadePessoa = &idade;


    return true;
}

bool posicaoValida(int pos, Vetor* v){
    if (pos < 0) return false;
    if (pos > v->qtd) return false;

    return true;
}

/********************************************
 * Implementação
 *******************************************/

Vetor* vet_criar(int tam){
    Vetor* v = (Vetor*) malloc(sizeof(Vetor));
    v->vet = (int*) calloc(tam, sizeof(int));
    v->tam = tam;
    v->qtd = 0;
    return v;
}

bool vet_anexar(Vetor* v, int elemento){
    if (!vetorValido(v)) return false;

    verifica_aumenta(v);
    v->vet[v->qtd++] = elemento;
    return true;
}

bool vet_inserir(Vetor* v, int elemento, int posicao){
    if (!vetorValido(v)) return false;
    if (!posicaoValida(posicao, v)) return false;
    
    verifica_aumenta(v);
    for (int i=v->qtd; i > posicao; i--){
        v->vet[i] = v->vet[i-1];
    }
    
    v->vet[posicao] = elemento;
    v->qtd++;
    return true;
}

bool vet_substituir(Vetor* v, int posicao, int novoElemento){
    if (!vetorValido(v)) return false;
    if (!posicaoValida(posicao, v)) return false;

    v->vet[posicao] = novoElemento;
    return true;
}

bool vet_removerPosicao(Vetor* v, int posicao, int* endereco){
    if (!vetorValido(v)) return false;
    if (!posicaoPreenchida(posicao, v)) return false;

    int elementoRemovido = v->vet[posicao] ;
    for (int i=posicao; i < v->qtd-1; i++){
        v->vet[i] = v->vet[i+1];
    }
    v->qtd--;
    
    *endereco = elementoRemovido;
    return true;
}

int vet_removerElemento(Vetor* v, int elemento){
    if (!vetorValido(v)) return -1;

    int pos = vet_posicao(v, elemento);
    if (pos == -1) return -1;

    int removido;
    vet_removerPosicao(v, pos, &removido);
    return pos;

}

int vet_tamanho(Vetor* v){
    if (!vetorValido(v)) return -1;

    return v->qtd;
}

bool vet_elemento(Vetor* v, int posicao, int* saida){
    if (!vetorValido(v)) return false;
    if (!posicaoPreenchida(posicao, v)) return false;

    *saida = v->vet[posicao];
    return true;
}

int vet_posicao(Vetor* v, int elemento){
    if (!vetorValido(v)) return -1;

    for (int i=0; i < v->qtd; i++){
        if (elemento == v->vet[i]){
            return i;
        }
    }
    return -1;
}

void vet_imprimir(Vetor* v){
    if (!vetorValido(v)) return;

    printf("[");
    for (int i=0; i < v->qtd; i++){       
        printf("%d", v->vet[i]);
        if (i < v->qtd-1) printf(",");
    }
    printf("]");
}

void vet_desalocar(Vetor** endVetor){
    Vetor* v = *endVetor;

    if (!vetorValido(v)) return;
    free(v->vet);
    free(v);
    *endVetor = NULL;
    
}

bool vet_toString(Vetor* v, char* saida){
    if (!vetorValido(v)) return false;

    saida[0] = '\0';
    strcat(saida, "[");
    for (int i=0; i < v->qtd; i++){
        char str[100];
        sprintf(str, "%d", v->vet[i]);
        strcat(saida, str);
        if (i < v->qtd-1) strcat(saida, ",");
    }
    strcat(saida, "]");
    return true;
}