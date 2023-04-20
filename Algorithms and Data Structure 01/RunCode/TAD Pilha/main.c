#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "pilha.h"

int main(){

    Pilha* p1 = pilha_criar();
    pilha_empilhar(p1, 10);
    pilha_empilhar(p1, 20);
    pilha_empilhar(p1, 30);

    char str[200];
    strcpy(str, "UTFPR\0");

    pilha_toString(p1, str);
    printf("%s\n", str); //[30,20,10]

    return 0;
}