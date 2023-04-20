#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    int a, b;
    
    // ENTRADA
    a = atoi(argv[1]); //A To I = Char Para Int
    b = atoi(argv[2]);
    
    // PROCESSAMENTO
    int soma = a + b;

    // SAÍDA
    printf("%d\n", soma);

    return 0;
}