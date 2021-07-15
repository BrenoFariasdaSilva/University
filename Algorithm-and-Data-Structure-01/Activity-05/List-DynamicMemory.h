#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Exercise 01
void inverte_string(char* str);
//Exercise 02
int qtde_vogais1(char* str);
void qtde_vogais2(char* str, int* saida);
//Exercise 03
char* copia_string(char* str);
//Exercise 04
int* cria_vetor1(int tam, int valor);
bool cria_vetor2(int tam, int valor, int** saida);
//Exercise 05
int* clone1(int tam, int valor);
bool clone2(int tam, int valor, int** saida);
//Exercise 06
int* aleatorio1(int tam);
bool aleatorio2(int tam, int** saida);
//Exercise 07
int dobra_tamanho(int** v, int tam);
//Exercise 08
int** cria_matriz(int linhas, int colunas, int valor);
