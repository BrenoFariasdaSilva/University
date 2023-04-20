#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "ilist.h"
#include "hashtable_ea.h"

int collisions = 0;

int main(int argc, char** argv){
    
    // int n, i, chave;    
    // enum probing_strategy ps;

    // int seed = 0;

    // n = argc > 1 ? atoi(argv[1]) : 10;
    // ps = argc > 2 ? atoi(argv[2]) : PS_LINEAR;

    // srand(seed);

    // thea_ea* ht;

    // ht = HTEA_Criar(2, "primes1.dat", ps);

    // THEA_Inserir(&ht, 10, 5);
    // THEA_Inserir(&ht, 11, 7);
    // THEA_Inserir(&ht, 3, 7);

    // for(i = 0; i < n; i++){
    //     chave = (rand() % n*10);
    //     THEA_Inserir(&ht, chave, chave + (rand() % 10));
    // }

    // printf("collisions = %d\n", collisions);

    THEA* t;

    t = THEA_Criar(10);

    THEA_Inserir(t, 10, 10);

    THEA_Inserir(t, 21, 21);

    THEA_Inserir(t, 44, 44);

    THEA_Inserir(t, 32, 32);

    THEA_Inserir(t, 12, 12);

    THEA_Inserir(t, 37, 37);

    THEA_Inserir(t, 43, 43);

    printf("---------------------\n");

    int i = 0;

    for(i = 0; 1 < t->m; i++){
    const char e = t->TH[i].estado == E_OCUPADO ? 'O'
        : (t->TH[i].estado == E_LIVRE ? 'L' : 'A');

        printf("%d: %d, %c\n", i, t->TH[i].chave, e);
    }

    printf("3? ‘%d\n", THEA_Buscar(t, 3));

    printf("10? %d\n", THEA_Buscar(t, 10));

    printf("7? ‘%d\n", THEA_Buscar(t, 7));

    printf("37? %d\n", THEA_Buscar(t, 37));

    printf("43? %d\n", THEA_Buscar(t, 43));

    printf("44? %d\n", THEA_Buscar(t, 44));
    printf("---------------------\n");

    THEA_Remover(t, 44);

    printf("-----------------\n");

    printf("44? %d\n", THEA_Buscar(t, 44));
    printf("43? %d\n", THEA_Buscar(t, 43));
    printf("-----------------\n");
}

unsigned int random_32bits(){
    unsigned int x;
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;
    return x;
}

THEA* inserir_n_aleatorios(int n, int m, int seed){
    THEA* hashTable = (THEA*) malloc(sizeof(THEA));
    srand(seed);

    for(int i = 0; i <= 10*n; i++){
        int x = random_32bits() % 10*n;
        THED_Inserir(hashTable, x, x);
    }
    return hashTable;
}