#include<stdio.h>
#include<stdbool.h>

void inverte_string(char* str);

int qtde_vogais1(char* str);
void qtde_vogais2(char* str, int* saida);

char* copia_string(char* str);

int* cria_vetor1(int tam, int valor);
bool cria_vetor2(int tam, int valor, int** saida);

int* clone1(int *valor, int tam);
bool clone2(int *valor, int tam, int** saida);

int* aleatorio1(int tam);
bool aleatorio2(int tam, int** saida);

int dobra_tamanho(int** v, int tam);

int** cria_matriz(int linhas, int colunas, int valor);