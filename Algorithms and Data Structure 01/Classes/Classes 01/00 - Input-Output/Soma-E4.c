#include <stdio.h>

int main(){
    float a, b;
    
    // ENTRADA
    FILE *arq_in = fopen("entrada.in","r");
    fscanf(arq_in, "%f %f", &a, &b);
    fclose(arq_in);

    /*
    
    FILE *arq_in = fopen("nome do arquivo","modo de abertura (r/w)");
    fscanf(arq_in, "%f %f", &a, &b);
    fclose(arq_in);

    */
    
    // PROCESSAMENTO
    float soma = a + b;

    // SAÍDA
    printf("%f\n", soma);

    return 0;
}