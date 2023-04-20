#include <stdio.h>

int main()
{
    int number = 0, fatorial = 1;

    printf("Digite um valor: ");
    scanf("%d", &number);

    if (number == 0 || number == 1)
    {
        printf("%d! = 1 \n", number);
    }

    if (number > 1)
    {
        for (int i = 0; i < number; i++)
        {
            fatorial *= (number - i);
        }

        printf("%d! = %d \n", number, fatorial);
    }

    else
    {
        printf("Valor Invalido. Tente novamente. \n");
    }

    return 0;
}
