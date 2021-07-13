#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

void findTotals(int rows, int cols, int m[rows][cols]);

int main()
{
    int mat[3][3] = {{1, 2, 0}, {4, 5, 0}, {7, 8, 0}};
    int rows = SIZE, cols = SIZE;

    findTotals(rows, cols, mat);

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

void findTotals(int rows, int cols, int m[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        int sum = 0;

        for (int j = 0; j < cols; j++)
        {
            sum += m[i][j];

            if (j == cols - 1)
                m[i][j] = sum;
        }
    }
}