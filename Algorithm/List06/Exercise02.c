#include <stdio.h>

int isPrime(int n)
{
    int dividers = 0;

    for (int i = 1; i < (n+1)/2; i++)
    {
        if (n % i == 0)
        {
            dividers++;
        }
    }
    
    if (dividers == 1)
    {
        return 1;
    }

    return 0;
}

int main()
{
    int number = 0, result = 0;

    printf("Digite um valor: ");
    scanf("%d", &number);

    result = isPrime(number);

    if (result == 1)
    {
        printf("\nO numero %d é primo\n", number);
    }

    else
    {
        printf("\nO numero %d não é primo\n", number);
    }
      
    return 0;
}
