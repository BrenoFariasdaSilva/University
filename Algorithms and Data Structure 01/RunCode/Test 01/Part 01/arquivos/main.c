#include "tad_vetor.h"

void teste_concatena(){
    Vetor* v1 = vet_criar(3);
    vet_anexar(v1, 1);
    vet_anexar(v1, 2);
    vet_anexar(v1, 3);

    Vetor* v2 = vet_criar(3);
    vet_anexar(v2, 4);
    vet_anexar(v2, 5);
    vet_anexar(v2, 6);

    Vetor* v3 = vet_concatena(v1,v2);
    vet_imprimir(v3);  // [1,2,3,4,5,6]
    printf("\n");

    vet_desalocar(&v1);
    vet_desalocar(&v2);
    vet_desalocar(&v3);
}
void teste_intercala(){
    Vetor* v1 = vet_criar(3);
    vet_anexar(v1, 2);
    vet_anexar(v1, 4);
    vet_anexar(v1, 6);

    Vetor* v2 = vet_criar(3);
    vet_anexar(v2, 1);
    vet_anexar(v2, 3);
    vet_anexar(v2, 5);

    Vetor* v3 = vet_intercala(v1,v2);
    vet_imprimir(v3);  // [1,2,3,4,5,6]

    vet_desalocar(&v1);
    vet_desalocar(&v2);
    vet_desalocar(&v3);
}

int main(){
    teste_concatena();
    teste_intercala();
    return 0;
}