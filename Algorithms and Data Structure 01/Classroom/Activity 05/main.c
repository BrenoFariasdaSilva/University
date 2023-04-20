#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lista_alocacao_dinamica.h"

int main()
{
    // // Exercício 01
    // // void inverte_string(char* str);
    // char nome[100] = "Ana Julia da Silva";//18 + \0 = 19: 0 -> 18
    // printf("String: %s \n", nome);
    // inverte_string(nome);
    // printf("Inverte String: %s \n\n", nome);

    // // Exercício 02
    // // int qtde_vogais1(char* str);
    // // int qtde_vogais2(char* str, int* saida);
    // char texto[100] = "UTFPR Campo Mourao";
    // int n1 = qtde_vogais1(texto);
    // int n2;
    // qtde_vogais2(texto, &n2);

    // printf("Quantidade de vogais n1: %d \n", n1);
    // printf("Quantidade de vogais n2: %d \n\n", n2);

    // // Exercício 03
    // // char* copia_string(char* str);
    // char* str = copia_string(texto);

    // printf("Copia String: %s \n\n", str); // "UTFPR Campo Mourao"

    // // Exercício 04
    // // int* cria_vetor1(int tam, int valor);
    // // bool cria_vetor2(int tam, int valor, int** saida);
    // int *v1, *v2;
    // v1 = cria_vetor1(10, -1);
    // cria_vetor2(5, 0, &v2);

    // printf("Cria Vetor V1: ");
    // for (int i = 0; i < 10; i++) 
    // {
    //     printf("%d ", v1[i]); //Tudo com -1
    // }
    // printf("\nCria Vetor V2: ");
    // for (int i = 0; i < 5; i++) 
    // {
    //     printf("%d ", v2[i]); //Tudo com 0
    // }
    // printf("\n\n");

    // // Exercício 05
    // // int* clone1(int* v, int tam);
    // // bool clone2(int* v, int tam, int** saida);   
    // int vet[5] = {2,4,6,8,10};
    // int *copia1, *copia2;
    // copia1 = clone1(vet, 5);
    // clone2(vet, 5, &copia2);

    // printf("Copia Vetor V1: ");
    // for (int i = 0; i < 5; i++) 
    // {
    //     printf("%d ", copia1[i]); // {2,4,6,8,10}
    // } 
    // printf("\nCopia Vetor V2: ");
    // for (int i = 0; i < 5; i++) 
    // {
    //     printf("%d ", copia2[i]); // {2,4,6,8,10}
    // }
    // printf("\n\n");

    // // Exercício 06
    // // int* aleatorio1(int tam);
    // // bool aleatorio2(int tam, int** saida);
    // v1 = aleatorio1(10);
    // aleatorio2(100, &v2);

    // printf("Vetor Aleatorio V1: ");
    // for (int i = 0; i < 5; i++) 
    // {
    //     printf("%d ", v1[i]); // random values
    // } 

    // printf("\nVetor Aleatorio V2: ");
    // for (int i = 0; i < 5; i++) 
    // {
    //     printf("%d ", v2[i]); // random values
    // }
    // printf("\n\n");

    // Exercício 07
    // int dobra_tamanho(int** v, int tam);
    int* dobraTamanho = (int*) calloc(3, sizeof(int));
    dobraTamanho[0] = 2;
    dobraTamanho[1] = 4;
    dobraTamanho[2] = 6;
    int novoTamanho = dobra_tamanho(&dobraTamanho, 3);


    printf("Dobra_Vetor V: ");
    for (int i = 0; i < novoTamanho; i++) 
    {
        printf("%d ", dobraTamanho[i]); // [2,4,6,0,0,0]
    } 
    printf("\n\n");

    // Exercício 08
    // int** cria_matriz(int linhas, int colunas, int valor);
    int** m = cria_matriz(2, 3, -1);

    printf("Cria Matriz M: \n");
    for (int i = 0; i < 2; i++) 
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", m[i][j]); // [-1, -1, -1] [-1, -1, -1]
        }
        printf("\n");
    } 

    return 0;
}