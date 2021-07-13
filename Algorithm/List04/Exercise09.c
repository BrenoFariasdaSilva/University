#include <stdio.h>

int main()
{
    int i = 0;
    float number = 0, sum = 0;

    printf("Digite um valor: ");
    scanf("%f", &number);

    while (number != 0)
    {
        sum += number;
        i++;

        printf("Digite um valor: ");
        scanf("%f", &number);
    }

    printf("\nSoma: %.2f\n", sum);
    printf("Media: %.2f\n", sum / i);

    return 0;
}
