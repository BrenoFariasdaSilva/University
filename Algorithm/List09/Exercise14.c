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