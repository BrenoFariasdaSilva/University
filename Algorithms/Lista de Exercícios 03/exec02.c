#include <stdio.h>

int main()
{
    int number = 0;

    printf("Digite um valor inteiro: \n");
    scanf("%d", &number);
    
    if (number == 0)
    {
        printf("O numero %d e nulo(zero)!\n", number);
    }
    
    if (number % 2 == 0)
    {
        printf("O numero %d e par!\n", number);
    }

    if (number % 2 != 0)
    {
        printf("O numero %d e impar!\n", number);
    }

    return 0;
}





