#include <stdio.h>

int main()
{
    int valor1 = 0, valor2 = 0, valor3 = 0, maior = 0;

    printf("Digite tres valores inteiros: \n");
    scanf("%d %d %d", &valor1, &valor2, &valor3);

    maior = valor1;

    if (valor2 > maior)
    {
        maior = valor2;
    }

    if (valor3 > maior)
    {
        maior = valor3;
    }

    printf("O maior valor e: %d", maior);

    return 0;
}
