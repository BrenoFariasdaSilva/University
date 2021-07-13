#include <stdio.h>

int main()
{
    int number = 0, prime = 1, sumPrimes = 0, i = 0; 

    printf("Digite um valor: ");
    scanf("%d", &number);

    while (i < number)
    {
        sumPrimes += prime;
        prime+=2;
        i++;
    }

    printf("O quadrado de %d e: %d \n", number, sumPrimes);

    return 0;
}
