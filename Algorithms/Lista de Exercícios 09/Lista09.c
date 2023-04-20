/* 
Exercício 1

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
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    
}

*/

/* 
Exercício 2

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

*/

/* 
Exercício 3

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

*/

/*
Exercício 4

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

*/

/* 
Exercício 5

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

*/

/* 
Exercício 6

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

*/

/* 
Exercício 7

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

*/

/*
Exercício 8

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

*/

/* 
Exercício 9

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

*/

/* 
Exercício 10

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

*/

/* 
Exercício 11

#include <stdio.h>
#define L 2
#define C 3

void transpose(int r1, int c1, int m1[r1][c1], int r2, int c2, int m2[r2][c2]);

int main()
{
    int m1[L][C] = {{1, 2, 3},{4, 5, 6}}, transposta[C][L] = {0};
    int rows = L, cols = C;

    printf("A Matriz Original M1[L][C]: \n");

    for (int line = 0; line < L; line++)
    {
        for (int column = 0; column < C; column++)
        {
            printf("%d ", m1[line][column]);
        }
        printf("\n");
    }

    transpose(rows, cols, m1, cols, rows, transposta);

    printf("A Matriz Transposta de M1[L][C]: \n");

    for (int line = 0; line < C; line++)
    {
        for (int column = 0; column < L; column++)
        {
            printf("%d ", transposta[line][column]);
        }
        printf("\n");
    }

    return 0;
}

void transpose(int r1, int c1, int m1[r1][c1], int r2, int c2, int m2[r2][c2])
{
    for (int line = 0; line < L; line++)
    {
        for (int column = 0; column < C; column++)
        {
            m2[column][line] = m1[line][column];
        }
    }
}

*/

/* Exercício 12

#include <stdio.h>
#define SIZE 2 

void multiply(int d, int m1[d][d], int m2[d][d], int m3[d][d]);

int main()
{
    int m1[SIZE][SIZE] = {{1, 2}, {3, 4}};
    int m2[SIZE][SIZE] = {{-1, 3}, {4, 2}};
    int m3[SIZE][SIZE] = {0};
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

    printf("\n");

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%d ", m2[i][j]);
        }
        printf("\n");
    }

    multiply(d, m1, m2, m3);

    printf("\n");

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%d ", m3[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void multiply(int d, int m1[d][d], int m2[d][d], int m3[d][d])
{
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < d; j++)
        {
            for (int k = 0; k < d; k++)
            {
                m3[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

*/

/* Exercício 13

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

*/

/* Exercício 14

#include <stdio.h>
#define SIZE 10 

void pascalTriangle(int n);

int main()
{
    int d = SIZE;

    pascalTriangle(d);

    return 0;
}

void pascalTriangle(int n)
{ 
    int m[n][n+1];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 && j == 1)
                m[i][j] = 1;
            
            else
                m[i][j] = 0;
        }
    }

    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - 1; j++) 
        {
            int sum = m[i][j] +  m[i][j + 1];
            m[i + 1][j + 1] = sum;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", m[i][j]);
        }
        printf("\n");
    }
}

*/

/* Exercício 15

#include <stdio.h>
#define SIZE 3

int checkUpperTriangle(int d, int m[d][d]);

int main()
{
    int m1[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int m2[SIZE][SIZE] = {{1, 2, 3}, {0, 5, 6}, {0, 0, 9}};
    int d = SIZE;
    int result = 0;

    result = checkUpperTriangle(d, m2);

    if (result == 0)
        printf("A Matriz e triangular superior");
    
    else
        printf("A Matriz nao e triangular superior");

    return 0;
}

int checkUpperTriangle(int d, int m[d][d])
{ 
    for (int i = 1; i < d; i++)
    {
        for (int j = 0; j < i - 1; j++)
        {
            if (m[i][j] != 0)
                return -1;
        }
    }

    return 0;
}

*/

/* Exercício 16

#include <stdio.h>
#define SIZE 3

int checkIdentity(int rows, int cols, int m[rows][cols]);

int main()
{
    int m1[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int m2[SIZE][SIZE] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int d = SIZE;
    int result = 0;

    result = checkIdentity(d, d, m2);

    if (result == 0)
        printf("A Matriz e identidade");
    
    else
        printf("A Matriz nao e identidade");

    return 0;
}

int checkIdentity(int rows, int cols, int m[rows][cols])
{ 
    for (int i = 1; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == j)
            {
                if (m[i][j] != 1)
                    return -1;
            }
                
            else
            {
                if (m[i][j] != 0)
                    return -1;
            }
            
        }
    }

    return 0;
}

*/

/* Exercício 17

#include <stdio.h>
#define SIZE 10 

int checkSymmetric(int d, int m[d][d]);

int main()
{
    int m1[SIZE][SIZE] = {{1, 2}, {2, 4}};
    int d = SIZE;
    int result = 0;

    result = checkSymmetric(d, m1);

    if (result == 0)
        printf("A Matriz é simétrica");
    
    else
        printf("A Matriz não é simétrica");

    return 0;
}

int checkSymmetric(int d, int m[d][d])
{ 
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (m[i][j] != m[j][i])
                return -1;
        }
    }

    return 0;
}

*/

/* Exercício 18

#include <stdio.h>
#define rows 4
#define cols 10

void printStrings(int n, int len, char list[n][len]);

int main()
{
    char m[rows][cols] = {"Oi", "Breno", "Farias", "Adeus"};

    printStrings(rows, cols, m);

 
    return 0;
}

void printStrings(int n, int len, char list[n][len])
{ 
    for (int i = 0; i < rows; i++)
    {
        printf("%s \n", list[i]);
    }
}

*/

/* Exercício 19

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define rows 4
#define cols 10

void printStringsMinMax(int n, int len, char list[n][len]);

int main()
{
    char m[rows][cols] = {"Oi", "Breno", "Farias", "Adeus"};

    printStringsMinMax(rows, cols, m);
 
    return 0;
}

void printStringsMinMax(int n, int len, char list[n][len])
{ 
    int max = INT_MIN;
    int min = INT_MAX;
    int length = 0;
    char MaxMin[2] = {0};

    for (int i = 0; i < rows; i++)
    {
        length = strlen(list[i]);

        if (length > max)
        {
            max = length;
            MaxMin[0] = i;
        }

        if (length < min)
        {
            min = length;
            MaxMin[1] = i;
        }
    }

    printf("Max: %s \n", list[MaxMin[0]]);
    printf("Min: %s \n", list[MaxMin[1]]);
}

*/


/* Exercício 20



*/

/* Exercício 21



*/
