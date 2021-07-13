#include <stdio.h>

int main()
{
    int m = 0, spaces = 0, x = 1;

    printf("Digite o numero de linhas \n");
    scanf("%d", &m);

    spaces = m - 1;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }

        spaces--;
        
        for (int w = 0; w < x; w++)
        {
            printf("X");
        }
        x += 2;

        printf("\n");
    }
      
    return 0;
}
