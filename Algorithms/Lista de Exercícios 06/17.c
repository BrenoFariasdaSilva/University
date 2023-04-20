#include <stdio.h>
#include <stdlib.h>

void randReport(int n, int* evenSum, int* primes);

int main()
{
    int numbers = 0, evenSum = 0, primes = 0; 

    printf("Digite o numero de elementos: ");
    scanf("%d", &numbers);
    printf("\n");

    randReport(numbers, &evenSum, &primes);

    printf("A soma dos numeros pares gerados: %d \n", evenSum);
    printf("A quantidade de numeros primos: %d \n", primes);
      
    return 0;
}

void randReport(int n, int* evenSum, int* primes)
{
    int randomNumber = 0, dividers = 0;

    for (int i = 0; i < n; i++)
    {
        randomNumber = 1 + rand () % n;

        printf("%d ", randomNumber);
        
        if (randomNumber % 2 == 0)
            *evenSum += randomNumber;

        for (int j = 1; j < randomNumber; j++)
        {
            if (randomNumber % j == 0)
                dividers++;
        }

        if (dividers == 1)
            *primes += 1;

        dividers = 0;
    }
    printf("\n");
}
