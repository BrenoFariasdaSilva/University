#include <stdio.h>

#define SIZE 3

void initValues(int rows, int cols, int m[rows][cols], int start, int step);

int main()
{
    int mat[3][3] = {0};
    int rows = SIZE, cols = SIZE;
    int start = 10;
    int steps = 2;

    initValues(rows, cols, mat, start, steps);

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

void initValues(int rows, int cols, int m[rows][cols], int start, int step)
{
    int count = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            m[i][j] = start + (step * count);

            count++;
        }
    }
}