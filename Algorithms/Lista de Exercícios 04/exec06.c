#include <stdio.h>

int main()
{
    int number = 0, sum = 0;

    printf("Digite um numero:");
    scanf("%d", &number);

    printf("\n");

    if (number >= 1)
    {
        for (int i = 0; i < number; i++)
        {
            sum += i + 1;

            if (i == number - 1)
            {
                printf("%d = %d \n", i + 1, sum);
            }

            else
            {
                printf("%d + ", i + 1);
            }
        }
    }

    else
    {
        printf("Valor invalido! Tente novamente. \n");
    }


    return 0;
}