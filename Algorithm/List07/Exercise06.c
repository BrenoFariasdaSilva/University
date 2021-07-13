#include <stdio.h>
#include <limits.h>

#define SIZE 7

void findMinMax(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {1, 23, 4, 8, 41, 7, 3};

    findMinMax(n, vector);
      
    return 0;
}

void findMinMax(int n, int vet[n])
{
    int maior = INT_MIN, menor = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (vet[i] > maior)
            maior = vet[i];

        if (vet[i] < menor)
            menor = vet[i];
    } 

    printf("O maior e o menor valor do array são: %d e %d", maior, menor);
}