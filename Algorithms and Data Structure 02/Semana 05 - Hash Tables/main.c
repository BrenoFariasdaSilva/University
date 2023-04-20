#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "ilist.h"
#include "hashtable_ea.h"

unsigned int random_32bits();
THED* inserir_n_aleatorios(int n, int m, int seed);
int THED_MaisLonga(THED* TH);
int THED_MaisCurta(THED* TH);
float THED_TamMedio(THED* TH);

int main(int argc, char** argv){
    int n = 1000;
    int m = 10;

    THED* th = inserir_n_aleatorios(n, m, 42);

    //for(int i = 0; i < th->m; i++){
    //    printf("%d: ", i);
    //    ILIST_Imprimir(th->t[i], 1);
    //}

    int longa = THED_MaisLonga(th);
    printf("\nMais longa: %d\n", longa);
    
    int curta = THED_MaisCurta(th);
    printf("Mais curta: %d\n", curta);

    float medio = THED_TamMedio(th);
    printf("Tamanho medio: %f\n", medio);

    return 0;
}

// Exercise A

unsigned int random_32bits(){
    unsigned int x;
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;
    return x;
}

THED* inserir_n_aleatorios(int n, int m, int seed){
    THED* hashTable = (THED*) malloc(sizeof(THED));
    srand(seed);

    for(int i = 0; i <= 10*n; i++){
        int x = random_32bits() % 10*n;
        THED_Inserir(hashTable, x, x);
    }
    return hashTable;
}

// Exercise B

int THED_MaisLonga(THED* TH){
    int biggest = INT_MIN;
    int size = -1;

    for (int i = 0; i < TH->m; i++) {
        if (!TH->t[i]) {
            size = TH->t[i]->tam;
        }
        if (tam > biggest){
            biggest = size;
        }
    }
    return biggest;
}

int THED_MaisCurta(THED* TH){
    int shorter = INT_MAX;
    int size = -1;''

    for (int i = 0; i < TH->m; i++) {
        if (!TH->t[i]) {
            size = TH->t[i]->tam;
        }
        if (tam < shorter){
            shorter = size;
        }
    }
    return shorter;
}

float THED_TamMedio(THED* TH){
    int sum = 0;
    int validLists = TH->m;

    for (int i = 0; i < TH->m; i++) {
        if (!TH->t[i]) {
            sum+=TH->t[i]->tam;
        } else {
            validLists--;
        }
    }
    return (double)sum / validLists;
}

// Exercise C

// Exercise D