#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int maxLine(int rows, int cols, int m[rows][cols]);

int main()
{
    int mat[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = SIZE, cols = SIZE;
    int HighestSum = 0;

    HighestSum = maxLine(rows, cols, mat);

    printf("Soma da linha de Maior Soma: %d \n", HighestSum);

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

int maxLine(int rows, int cols, int m[rows][cols])
{
    int sum = 0;
    int HighestSum = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum += m[i][j];
        }

        if (sum > HighestSum)
            HighestSum = sum;

        sum = 0;
    }

    return HighestSum;
}