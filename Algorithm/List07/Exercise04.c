#include <stdio.h>

#define SIZE 7

int sumValues(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {1, 23, 4, 8, 41, 7, 3}, average = 0;

    average = sumValues(n, vector);

    printf("A media aritmetica e: %d \n", average);
      
    return 0;
}

int sumValues(int n, int vet[n])
{
    int average = 0, sum = 0, i = 0;

    for (i = 0; i < n; i++)
    {
        sum += vet[i];
    } 

    average = sum / n;

    return average;
}