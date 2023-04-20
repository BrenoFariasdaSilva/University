#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"

int main()
{
    Fila* f = fila_criar();

    fila_inserir(f, 10);
    fila_inserir(f, 20);
    fila_inserir(f, 30);
    fila_inserir(f, 40);

    char str[200];
    fila_toString(f, str);
    printf("%s\n", str); //[10,20,30,40]

    // Remove 2 elementos
    int elemento;
    fila_remover(f, &elemento);
    printf("Removido: %d\n", elemento); // 10

    fila_remover(f, &elemento);
    printf("Removido: %d\n", elemento); // 20

    fila_toString(f, str);
    printf("%s\n", str); //[10,20,30,40]

    // Remover o restante dos elementos
    fila_remover(f, &elemento);
    printf("Removido: %d\n", elemento); // 30

    fila_remover(f, &elemento);
    printf("Removido: %d\n", elemento); // 40

    fila_toString(f, str);
    printf("%s\n", str); //[10,20,30,40]

    if(!fila_remover(f, &elemento)){
        printf("A fila esta vazia\n");

    }

    return 0;
}