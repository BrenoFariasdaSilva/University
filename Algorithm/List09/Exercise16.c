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