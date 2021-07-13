#include <stdio.h>
#include <limits.h>

int main()
{
    int number = 1, min = INT_MAX, max = INT_MIN;

    printf("Digite um numeros (Digite 0 para sair): ");
    scanf("%d", &number);

    min = number;
    max = number;

    if (number == 0)
    {
        printf("Nenhum valor foi inserido! Por favor, tente novamente. \n");
    }

    else
    {
        while (number != 0)
        {
            if (number > max)
            {
                max = number;
            }

            if (number < min)
            {
                min = number;
            }

            printf("Digite um numeros (Digite 0 para sair): ");
            scanf("%d", &number);
        }

        printf("Minimo: %d\n", min);
        printf("Maximo: %d\n", max);
    }
    
    return 0;
}
