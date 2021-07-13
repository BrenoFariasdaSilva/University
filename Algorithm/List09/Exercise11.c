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