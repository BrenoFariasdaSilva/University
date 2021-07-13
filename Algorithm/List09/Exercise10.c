#include <stdio.h>

#define SIZE 3

void sum(int rows, int cols, int m1[rows][cols], int m2[rows][cols], int m3[rows][cols]);

int main()
{
    int mat1[3][3] = {{1, 2, 0}, {4, 5, 0}, {7, 8, 0}};
    int mat2[3][3] = {{1, 2, 0}, {4, 5, 0}, {7, 8, 0}};
    int mat3[3][3] = {0};
    int rows = SIZE, cols = SIZE;

    sum(rows, cols, mat1, mat2, mat3);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", mat3[i][j]);
        }
        printf("\n");
    }
 
    return 0;
}

void sum(int rows, int cols, int m1[rows][cols], int m2[rows][cols], int m3[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            m3[i][j] = m1[i][j] + m2[i][j];
        }
    }
}