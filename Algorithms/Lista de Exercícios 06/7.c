#include <stdio.h>

int isPerfectNumber(int n);

int main()
{
    int number = 0;

    printf("Digite um numero inteiro: ");
    scanf("%d", &number);

    printf("\n");

    int result = isPerfectNumber(number); 

    if (result == 1)
    {
        printf("O numero %d é perfeito! \n", number);
    }

    else
    {
        printf("O numero %d não é perfeito! \n", number);
    }

    return 0;
}

int isPerfectNumber(int n)
{
    int divisors = 0, sum = 0;

    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }

    if (sum == n)
    {
        return 1;
    }

    return 0;
}
