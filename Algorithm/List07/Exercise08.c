#include <stdio.h>

#define SIZE 10

void reverse(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = i + 1;
        printf("%d ", vector[i]);
    }
    printf("\n");

    reverse(n, vector);
      
    return 0;
}

void reverse(int n, int vet[n])
{   
    int hold = 0, j = n - 1;

    for (int i = 0; i < n / 2; i++)
    {
        hold = vet[i];
        vet[i] = vet[j];
        vet[j] = hold;

        j--;
    } 

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}