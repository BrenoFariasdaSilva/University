#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

void initRandom(int rows, int cols, int m[rows][cols], int min, int max);

int main()
{
    int mat[3][3] = {0};
    int rows = SIZE, cols = SIZE;
    int min = -10;
    int max = 10;

    initRandom(rows, cols, mat, min, max);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
      
    return 0;
}

void initRandom(int rows, int cols, int m[rows][cols], int min, int max)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            m[i][j] = min + rand () % (max * 2);
        }
    }
}