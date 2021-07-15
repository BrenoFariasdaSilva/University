#include <stdio.h>

typedef struct produto
{
    int codigo; 
    char descricao[12]; 
    float preco; 
} Produto;

int main() 
{
    Produto prodA = {1, "Teclado", 98.50};
    Produto prodB = {2, "Mouse", 65.00};
    Produto prodC = {3, "Webcam", 130.00};
    Produto vet[4];

    Produto prodD = {4, "SSD", 420.00};
    vet[3] = prodD;

    vet[0] = prodA;
    vet[1] = prodB;
    vet[2] = prodC;
    
    printf("%s \n", prodC.descricao);

    strcpy(vet[2]->descricao, "Mouse Sem Fio");

    printf("%s \n", prodC.descricao);

    return 0;
}

