#include <stdio.h>
#define SIZE 2 

void multiply(int d, int m1[d][d], int m2[d][d], int m3[d][d]);

int main()
{
    int m1[SIZE][SIZE] = {{1, 2}, {3, 4}};
    int m2[SIZE][SIZE] = {{-1, 3}, {4, 2}};
    int m3[SIZE][SIZE] = {0};
    int d = SIZE;

    printf("A Matriz Original M1[L][C]: \n");

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%d ", m2[i][j]);
        }
        printf("\n");
    }

    multiply(d, m1, m2, m3);

    printf("\n");

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%d ", m3[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void multiply(int d, int m1[d][d], int m2[d][d], int m3[d][d])
{
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < d; j++)
        {
            for (int k = 0; k < d; k++)
            {
                m3[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}