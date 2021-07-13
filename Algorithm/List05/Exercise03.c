#include <stdio.h>
#include <limits.h>

int main()
{
    int number = 0;
    int maiorpar = INT_MIN;
    int menorimpar = INT_MAX;
    int quantity = 0;
    int quantitypar = 0;
    float average = 0;

    do
    {
        printf("Digite um numero:");
        scanf("%d", &number);

        quantity++;

        if (number % 2 == 0)
        {
            average += number;
            quantitypar++;

            if (number > maiorpar)
            {
                maiorpar = number;
            }
        }

        if (number % 2 != 0)
        {
            if (number < menorimpar)
            {
                menorimpar = number;
            }
        }
    }
    while (number != 0);

    --quantity;

    if (quantity != 0)
    {
        average /= quantity;

        printf("\n");

        printf("O Maior Par Digitado: %d \n", maiorpar);
        printf("O Menor Ímpar digitado: %d \n", menorimpar);
        printf("Media de numeros numeros pares: %.2f \n", average);
    } 

    else
    {
        printf("Nenhum valor válido foi inserido!");
    }
    
    return 0;
}