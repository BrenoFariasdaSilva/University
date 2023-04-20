#include <stdio.h>
#include <string.h>

#define N 5 

void unshuffle(char s[]);
void simpleMerge(int n, int v1[], int v2[], int v3[]);
void matrixFill(int d, int m[d][d], int init[d]);

int main()
{
    char RandomChar[] = "ababbababa";

    int v1[N] = {1, 2, 3, 4, 5};
    int v2[N] = {5, 4, 3, 2, 1}; 
    int v3[2*N] = {0};

    int initVet[N] = {1, 2, 3, 4, 5};
    int vet[N][N] = {0};

    printf("%s \n", RandomChar);

    unshuffle (RandomChar);
    
    simpleMerge (N, v1, v2, v3);

    matrixFill (N, vet, initVet);
      
    return 0;
}

void unshuffle(char s[])
{
    int CountA = 0;
    int SIZE = strlen(s);

    for (int i = 0; i < SIZE; i++)
    {
        if (s[i] == 97)
        {
            CountA++;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        if (i < CountA)
            s[i] = 'a';

        else
            s[i] = 'b';
    }

    printf("%s \n\n", s);
}

void simpleMerge(int n, int v1[], int v2[], int v3[])

{
    for (int i = 0; i < 2*n; i++)
    {
        if (i % 2 == 0)
            v3[i] = v1[i / 2];

        else
            v3[i] = v2[i / 2];
    }

    for (int i = 0; i < 2*n; i++)
    {
        printf("%d ", v3[i]);
    }

    printf("\n\n");
}

void matrixFill(int d, int m[d][d], int init[d])
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (i == 0)
                m[i][j] = init[j];

            else
                m[i][j] = 1 + (m[i - 1][j]);
        }
    }

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

