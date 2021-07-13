#include <stdio.h>

int factorialSum(int n);

int main()
{
    int number = 0;

    printf("Digite um numero da soma dos fatorais : ");
    scanf("%d", &number);

    printf("\n");

    int result = factorialSum(number);   

    printf("A soma dos fatorais de %d! a 1! e: %d \n", number, result);
      
    return 0;
}

int factorialSum(int n)
{
    int sum = 0, fatorial = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            fatorial *= j; 
        }

        sum += fatorial;
        fatorial = 1;
    }

    return sum;
}
