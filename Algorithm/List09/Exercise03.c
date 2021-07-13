#include <stdio.h>
#include <limits.h>

#define SIZE 3

void printMinMax(int rows, int cols, int m[rows][cols]);

int main()
{
    int mat[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = SIZE, cols = SIZE;

    printMinMax(rows, cols, mat);
      
    return 0;
}

void printMinMax(int rows, int cols, int m[rows][cols])
{
    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < rows; i++)
    {
        for (int j = cols - 1 ; j > -1; j--)
        {
            if (m[i][j] > max)
                max = m[i][j];

            if (m[i][j] < min)
                min = m[i][j];
        }
    }

    printf("Min: %d \n", min);
    printf("Max: %d \n", max);
    
}