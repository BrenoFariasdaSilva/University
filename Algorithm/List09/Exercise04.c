#include <stdio.h>
#include <limits.h>

#define SIZE 3

void findMinMax(int rows, int cols, int m[rows][cols], int* min, int* max);

int main()
{
    int mat[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = SIZE, cols = SIZE;
    int min = INT_MAX;
    int max = INT_MIN;

    findMinMax(rows, cols, mat, &min, &max);

    printf("Min: %d \n", min);
    printf("Max: %d \n", max);
      
    return 0;
}

void findMinMax(int rows, int cols, int m[rows][cols], int* min, int* max)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (m[i][j] > *max)
                *max = m[i][j];

            if (m[i][j] < *min)
                *min = m[i][j];
        }
    }
}