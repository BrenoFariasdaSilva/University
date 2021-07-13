#include <stdio.h>

int main()
{
    double number = 0; 
    int auxiliar = 0;

    printf("Digite um valor fracionado(com a parte fracionaria sendo dividida por um ponto \".\"): \n");
    scanf("%lf", &number);  
       
    printf("O numero com 2 cadas de precisao: %.2lf \n", number);
    
    printf("A parte inteira do valor fracionado: %d \n", (int) number);

    auxiliar = number;

    printf("A parte fracionada: %lf \n", number - auxiliar);

    printf("Notacao cientifica: %.2e \n", number);

    return 0;
}
