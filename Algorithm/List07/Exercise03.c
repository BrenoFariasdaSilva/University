#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void setPositive(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = -5 + rand () % SIZE;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vector[i]);
    } 
    printf("\n");

    setPositive(n, vector);
      
    return 0;
}

void setPositive(int n, int vet[n])
{
   for (int i = 0; i < n; i++)
    {
        if (vet[i] < 0)
        {
            vet[i] *= -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    } 
}