#include <stdio.h>

int main()
{
    int number = 0;
    int quantity = 0;
    int sum = 0;
    float average = 0;

    do
    {
        printf("Digite um numero:");
        scanf("%d", &number);

        quantity++;
        sum+= number;
    }
    while (number != 0);

    average = (float)sum / --quantity;

    printf("\n");

    printf("Quantidade de numeros: %d \n", quantity);
    printf("Soma de numeros: %d \n", sum);
    printf("Media de numeros: %.2f \n", average); 
    
    return 0;
}