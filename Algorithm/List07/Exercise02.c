#include <stdio.h>

#define SIZE 10

void printEven(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = i + 1;
    }

    printEven(n, vector);
      
    return 0;
}

void printEven(int n, int vet[n])
{
   for (int i = 0; i < n; i++)
    {
        if (vet[i] % 2 == 0)
        {
            printf("%d ", vet[i]);
        }
    } 
}