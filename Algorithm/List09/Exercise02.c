#include <stdio.h>
#define SIZE 3

void printMat(int rows, int cols, int m[rows][cols]);

int main()
{
    int mat[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = SIZE, cols = SIZE;

    printMat(rows, cols, mat);
      
    return 0;
}

void printMat(int rows, int cols, int m[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = cols - 1 ; j > -1; j--)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    
}