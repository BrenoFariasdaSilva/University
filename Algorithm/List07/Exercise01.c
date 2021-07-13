#include <stdio.h>

#define SIZE 10

void printReverse(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        vector[i]=i + 1;
    }

    printReverse(n, vector);
      
    return 0;
}

void printReverse(int n, int vet[n])
{
   for (int i = n - 1; i >= 0; i--)
    {
        printf("%d ", vet[i]);
    } 
}