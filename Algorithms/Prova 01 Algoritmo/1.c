#include <stdio.h>

int main()
{
    int n = 0, maior = 0, npares = 0;

    printf("Digite 4 valores para encontrar o maior e a quantidade de pares: \n");

    for (int i = 0; i < 4; i++)
    {
        printf("Digite o valor inteiro %d/4: ", i+1);
        scanf("%d", &n);

        if (i == 0)
        {
            maior = n;
        }

        if (n > maior)
        {
            maior = n;
        }

        if (n % 2 == 0)
        {
            npares++;
        }
    }
    printf("Maior: %d \n", maior);
    printf("NPares: %d \n", npares);
    return 0;
}
