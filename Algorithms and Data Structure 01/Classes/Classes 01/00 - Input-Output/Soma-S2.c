#include <stdio.h>

int main(){
    int a, b;
    
    // ENTRADA
    FILE *arq_in = fopen("entrada.in","r");
    fscanf(arq_in, "%d %d", &a, &b);
    fclose(arq_in);
    
    // PROCESSAMENTO
    int soma = a + b;

    // SAÍDA
    FILE *arq_out = fopen("saida.out","w");
    fprintf(arq_out,"%d\n", soma);
    fclose(arq_out);
    return 0;
}