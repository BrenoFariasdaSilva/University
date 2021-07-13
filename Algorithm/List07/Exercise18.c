#include <stdio.h>

#define SIZE1 8
#define SIZE2 5
#define SIZE3 13

void vecConcat(int n1, int v1[n1], int n2, int v2[n2], int v3[]);

int main()
{
    int vet1[SIZE1] = {8, 7, 6, 5, 4, 3, 2, 1};
    const int n1 = SIZE1;

    int vet2[SIZE2] = {9, 1, 2, 3, 4};
    const int n2 = SIZE2;

    int vet3[SIZE3] = {0};

    vecConcat(n1, vet1, n2, vet2, vet3);
      
    return 0;
}

void vecConcat(int n1, int v1[n1], int n2, int v2[n2], int v3[])
{  
    for (int i = 0; i < SIZE3; i++)
    {
        int aux = 0;

        for (int j = 0; j < SIZE3; j++)
        {
            if (v1[i] == v3[j])
                aux++;
        }

        for (int j = 0; j < SIZE3; j++)
        {
            if (v2[i] == v3[j])
                aux++;
        }
        
        if (aux == 0)
        {
            if (i < n1)
                v3[i] = v1[i];

            else
                v3[i] = v2[i - n1];
        }
    }

    for (int i = 0; i < SIZE3; i++)
    {
        printf("%d ", v3[i]);
    }
}