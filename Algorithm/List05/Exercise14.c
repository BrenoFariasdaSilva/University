#include <stdio.h>

int main()
{
    int number = -1, conta = 0;

    while (number != 0)
    {
        printf("Digite o valor da sua compra: ");
        scanf("%d", &number);
        printf("\n");

        if (number < 50)
        {
            conta = 0.95 * number;
        }

        if (number < 100 || number > 50)
        {
            conta = 0.90 * number;
        }

        if (number < 200 || number > 100)
        {
            conta = 0.85 * number;
        }

        if (number > 200)
        {
            conta = 0.80 * number;
        }

        printf("O valor da sua conta e: %d \n", conta);
    }

    return 0;
}
