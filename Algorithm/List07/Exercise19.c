#include <stdio.h>

#define SIZE1 8
#define SIZE2 5
#define SIZE3 13

void vecIntersection(int n1, int v1[], int n2, int v2[], int v3[]);

int main()
{
    int vet1[SIZE1] = {8, 7, 6, 5, 4, 3, 2, 1};
    const int n1 = SIZE1;

    int vet2[SIZE2] = {9, 1, 2, 3, 4};
    const int n2 = SIZE2;

    int vet3[SIZE3] = {0};

    vecIntersection(n1, vet1, n2, vet2, vet3);
      
    return 0;
}

void vecIntersection(int n1, int v1[], int n2, int v2[], int v3[])
{  
    int value = 0, aux = 0;

    for (int i = 0; i < n2; i++)
    {
        value = v2[i];

        for (int j = 0; j < n1; j++)
        {
            if (v1[j] == value)
            {
                v3[aux] = value;
                aux++;
            }
        }
    }

    for (int i = 0; i < SIZE3; i++)
    {
        printf("%d ", v3[i]);
    }
}