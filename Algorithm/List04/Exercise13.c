#include <stdio.h>

int main()
{
    int number = 0, prime = 0, i = 1;

    printf("Digite um valor: ");
    scanf("%d", &number);

    while (i <= number)
    {
        if (number % i == 0)
        {
            prime++;
        }

        i++;
    }

    if (prime == 2)
    {
        printf("O numero %d e primo!", number);
    }

    else
    {
        printf("O numero %d nao e primo!", number);
    }

    return 0;
}
