#include <stdio.h>
#include <string.h>

#include "fila.h"

int main()
{
    int tam;
    char str[300];

    scanf("[%d] ", &tam);
    Fila* f1 = fila_criar(-1);
    Fila* f2 = fila_criar(1);
    
    for (int i=0; i < tam; i++){
        int n;
        scanf("%d ", &n);
        fila_inserir(f1, n);        
        fila_inserir(f2, n);
    }
    fila_toString(f1, str);
    printf("%s\n", str);

    fila_toString(f2, str);
    printf("%s\n", str);  
}

