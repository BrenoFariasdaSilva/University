#include <stdio.h>

#define SIZE 8

void defrag(const int n, const int vet[n]);

int main()
{
    int vet[SIZE] = {1, 6, -1, 9, 4, -1, 2, -1};
    const int n = SIZE;

    defrag(n, vet);
      
    return 0;
}

void defrag(const int n, const int vet[n])
{  
    int defrag[SIZE] = {0};

    for (int i = 0, j = SIZE - 1, k = 0; i < SIZE; i++)
    {
        if (vet[i] == -1)
        {
            defrag[j] = -1;
            j--;
        }

        else
        {
            defrag[k] = vet[i];
            k++;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", defrag[i]);
    }
}