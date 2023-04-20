#include <stdio.h>

int main()
{
    int m = 0, spaces = 0;

    printf("Digite o numero de linhas \n");
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m - i; j++)
        {
            if (j == 0)
            {
                for (int w = 0; w < i; w++)
                {
                    printf(" ");
                }
            }
            printf("x");
        }
        printf("\n");
    }
      
    return 0;
}
