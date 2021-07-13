#include <stdio.h>

int main()
{
    int number1 = 0, number2 = 0, maior = 0;

    printf("Digite dois valores naturais (0-9): ");
    scanf("%d %d", &number1, &number2);

    if ((number1 >= 0 && number1 < 10) && (number2 >= 0 && number2 < 10))
    {
        if (number1 == number2)
        {
            printf("Os valores inseridos %d e %d sao iguais! \n", number1, number2);
        }

        else
        {
            if (number1 > number2)
            {
                maior = number1;
                printf("O valor valor e: %d", maior);
            }

            else
            {
                maior = number2;
                printf("O valor valor e: %d", maior); 
            }   
        }
    }

    else
    {
        printf("Valor(es) fora da escala dos naturais(0-9)!\n");
    }

    return 0;
}