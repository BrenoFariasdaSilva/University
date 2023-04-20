#include <stdio.h>
#include <string.h>

#include "fila.h"

void teste_inserir()
{
    char str[300];
    int n;
    Fila* f1 = fila_criar();
    
    scanf("%d ", &n);
    while(n != -1){
        fila_inserir(f1, n);
        scanf("%d ", &n);
    }
    fila_toString(f1, str);
    printf("%s", str);
    fila_destruir(&f1);
}

void teste_remover(){
    char str[300];
    int n;
    Fila* f1 = fila_criar();
    
    scanf("%d ", &n);
    while(n != -1){
        fila_inserir(f1, n);
        scanf("%d ", &n);
    }

    while(!fila_vazia(f1)){
        TipoElemento e;
        fila_remover(f1, &e);
        printf("(%d) ", e);
    }
    
    fila_destruir(&f1);
}

void teste_primeiro(){
    char str[300];
    int n;
    TipoElemento e;

    Fila* f1 = fila_criar();
    
    scanf("%d ", &n);
    while(n != -1){
        fila_inserir(f1, n);
        scanf("%d ", &n);
    }

    while(!fila_vazia(f1)){
        fila_primeiro(f1, &e);
        printf("(%d)", e);

        TipoElemento removido;
        fila_remover(f1, &removido);        
    }
    
    fila_destruir(&f1);
}

int main(){
    int opcao;
    scanf("[%d]\n", &opcao);
    
    if(opcao == 1){
        teste_inserir();
    }else if(opcao == 2){
        teste_remover();
    }else if(opcao == 3){
        teste_primeiro();
    }

    return true;
}

