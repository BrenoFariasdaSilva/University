#include <stdio.h>

int main()
{
    for (int i = 1; i < 11; i++)
    {
        for (int j = 1;  j < 11; j++)
        {
            printf("%d x %d = %d \n", i, j, i * j);
        }
    }
      
    return 0;
}
