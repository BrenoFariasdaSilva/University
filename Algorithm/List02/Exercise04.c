#include <stdio.h>

int main()
{
    int number1 = 0, number2 = 0, number3 = 0;
    const int weight1 = 10, weight2 = 50, weight3 = 40, sumWeights = 100;
    int arithmeticAverage = 0, weightedAverage = 0;

    printf("Digite três valores inteiros: \n");
    scanf("%d %d %d", &number1, &number2, &number3);

    arithmeticAverage = (number1 + number2 + number3) / 3;
    weightedAverage = ((number1 * weight1) + (number2 * weight2) + (number3 * weight3)) / sumWeights;

    printf("Arithmetic Average = %d \n", arithmeticAverage);
    printf("Weighted Average = %d \n", weightedAverage);

    return 0;
}