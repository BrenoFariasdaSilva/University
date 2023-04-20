#include <stdio.h>
#include <string.h>

#include "fila.h"

int main()
{
    char str[300];
    Fila* f1 = fila_criar();
    fila_inserir(f1, 10);
    fila_inserir(f1, 20);
    fila_inserir(f1, 30);
    fila_inserir(f1, 40);
    fila_inserir(f1, 50);


    fila_toString(f1, str);
    printf("%s\n", str);
    
	TipoElemento e;
    fila_primeiro(f1, &e);
    printf("Primeiro (%d)\n", e);
    fila_remover(f1, &e);
    fila_toString(f1, str);
    printf("Removido (%d) %s\n\n", e, str);
	
    fila_primeiro(f1, &e);
    printf("Primeiro (%d)\n", e);
    fila_remover(f1, &e);
    fila_toString(f1, str);
    printf("Removido (%d) %s\n\n", e, str);
    
    fila_primeiro(f1, &e);
    printf("Primeiro (%d)\n", e);
    fila_remover(f1, &e);
    fila_toString(f1, str);
    printf("Removido (%d) %s\n\n", e, str);

    fila_primeiro(f1, &e);
    printf("Primeiro (%d)\n", e);
    fila_remover(f1, &e);
    fila_toString(f1, str);
    printf("Removido (%d) %s\n\n", e, str);

    fila_primeiro(f1, &e);
    printf("Primeiro (%d)\n", e);
    fila_remover(f1, &e);
    fila_toString(f1, str);
    printf("Removido (%d) %s\n\n", e, str);
    

}
