#include <stdio.h>

float calcula_custo(float valor, float troco, int qtde){
    if (troco > valor) return -1;
    if (qtde <= 0) return -1;

    return (valor - troco) / qtde;
}


int main(){

    float valor, troco, custo;
    int qtde;

    // ENTRADA
    scanf("%f %f %d", &valor, &troco, &qtde);

    // PROCESSAMENTO
    custo = calcula_custo(valor, troco, qtde);

    // SAÍDA
    printf("%f\n", custo);


    return 0;
}