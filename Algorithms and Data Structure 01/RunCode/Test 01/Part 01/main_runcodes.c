#include "tad_vetor.h"

Vetor* lerVetor(){
    int tam;
    scanf("[%d] ", &tam);
    Vetor* v = vet_criar(tam);
    for (int i=0; i < tam; i++){
        int n;
        scanf("%d ", &n);
        vet_anexar(v, n);
    }
    return v;
}

void teste01(){

    // Leitura do primeiro vetor
    Vetor* v1 = lerVetor();
    // Leitura do segundo vetor
    Vetor* v2 = lerVetor();
    Vetor* v3 = vet_concatena(v1, v2);
    vet_imprimir(v3);
    
    vet_desalocar(&v1);
    vet_desalocar(&v2);
    vet_desalocar(&v3);
    scanf("\n");
    printf("\n");
}

void teste02(){
    Vetor* v1 = lerVetor();
    Vetor* v2 = lerVetor();
    Vetor* v3 = vet_intercala(v1, v2);
    vet_imprimir(v3);

    vet_desalocar(&v1);
    vet_desalocar(&v2);
    vet_desalocar(&v3);
    scanf("\n");
    printf("\n");
}


int main(){
    
    teste01();
    teste02();

    return 0;
}