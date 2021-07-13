#include <stdio.h>

int main()
{
    int number = 0, sumSquare = 0, SquareSum = 0, delta = 0;

    printf("Digite um valor: \n");
    scanf("%d", &number);

    for (int i = 1; i < number + 1; i++)
    {
        sumSquare += i * i;
        SquareSum += i;
    }

    SquareSum *= SquareSum;

    delta = SquareSum - sumSquare;

    printf("Soma dos Quadrados: %d \n", sumSquare);
    printf("Quadrado da Soma: %d \n", SquareSum);
    printf("A diferença: %d \n", delta);
    
    return 0;
}