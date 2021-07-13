#include <stdio.h>

int factorialSum(int n);

int main()
{
    int number = 0, sum = 0;

    printf("Digite um numero da soma dos fatorais : ");
    scanf("%d", &number);

    printf("\n");

    for (int i = 1; i <= number; i++)
    {
        sum += factorialSum(i); 
    }

    printf("A soma dos fatorais de %d! a 1! e: %d \n", number, sum);
      
    return 0;
}

int factorialSum(int n)
{
    int fatorial = 1;

    for (int i = 1; i <= n; i++)
    {
        fatorial *= i; 
    }

    return fatorial;
}
