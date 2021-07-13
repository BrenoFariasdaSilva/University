#include <stdio.h>
#define SIZE 2 

void switchDiagonals(int d, int m1[d][d]);

int main()
{
    int m1[SIZE][SIZE] = {{1, 2}, {3, 4}};
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

    switchDiagonals(d, m1);

    printf("\n");
    printf("A Matriz Modificada M1[L][C]: \n");

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void switchDiagonals(int d, int m1[d][d])
{ 
    int hold = 0;

    for (int i = 0, j = d - 1; i < d; i++, j--) 
    {
        hold = m1[i][j];

        m1[i][j] = m1[i][(d - 1) - j];

        m1[i][(d - 1) - j] = hold;
    }
}