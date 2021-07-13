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