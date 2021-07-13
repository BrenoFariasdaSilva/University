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