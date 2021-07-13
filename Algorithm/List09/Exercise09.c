#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int matrixEquals(int r1, int c1, int m1[r1][c1], int r2, int c2, int m2[r2][c2]);

int main()
{
    int mat1[3][3] = {{1, 2, 0}, {4, 5, 0}, {7, 8, 0}};
    int mat2[3][3] = {{1, 2, 0}, {4, 5, 0}, {7, 8, 0}};
    int rows = SIZE, cols = SIZE;
    int equals = 0;

    equals = matrixEquals(rows, cols, mat1, rows, cols, mat2);

    if (equals == 1)
        printf("As matrizes sao iguais!");

    else
        printf("As matrizes nao sao iguais!");
      
    return 0;
}

int matrixEquals(int r1, int c1, int m1[r1][c1], int r2, int c2, int m2[r2][c2])
{
    for (int i1 = 0, i2 = 0; i1 < r1, i2 < r2; i1++, i2++)
    {
        for (int j1 = 0, j2 = 0; j1 < c1, j2 < c2; j1++, j2++)
        {
            if (m1[i1][j1] != m2[i2][j2])
                return 0;
        }
    }

    return 1;
}