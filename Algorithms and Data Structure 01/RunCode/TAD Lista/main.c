#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "lista.h"

void teste(char* str, char* esperado)
{
    bool resultado = strcmp(esperado, str) == 0;
    printf("[%s] %s \n", (resultado ? "PASS" : "ERROR"), str);
}


void testeAnexar(){
    printf("\n------------------------------------------------\n");
    printf(">>> TESTE ANEXAR \n");
    printf("------------------------------------------------\n");

    Lista* l = lista_criar();
    lista_anexar(l, 10);
    lista_anexar(l, 20);
    lista_anexar(l, 30);

    char str[300];
    lista_toString(l, str);
    teste(str, "[10,20,30]");

}

void testeInserir(){
    printf("\n------------------------------------------------\n");
    printf(">>> TESTE INSERIR \n");
    printf("------------------------------------------------\n");
    char str[300];

    Lista* l = lista_criar();
    lista_inserir(l, 10, 0);
    lista_toString(l, str);
    teste(str, "[10]");

    lista_inserir(l, 5, 0);
    lista_toString(l, str);
    teste(str, "[5,10]");

    lista_inserir(l, 20, 2);
    lista_toString(l, str);
    teste(str, "[5,10,20]");

    lista_inserir(l, 7, 1);
    lista_toString(l, str);
    teste(str, "[5,7,10,20]");
}

int main(){

    testeAnexar();
    testeInserir();


    return 0;
}