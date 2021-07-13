#include <stdio.h>

int main()
{
    int i = 0, j = 0;

    printf("Digite o numero de linhas \n");
    scanf("%d", &i);

    printf("Digite o numero de colunas \n");
    scanf("%d", &j);

    for (int i = 1; i < 11; i++)
    {
        for (int j = 1;  j < 11; j++)
        {
            if (j == 1)
            {
                printf("[X-");
            }

            if (j == 10)
            {
                printf("X]");
            }

            if (j != 1 && j !=10)
            {
                printf("X-");
            }
        }
        printf("\n");
    }
      
    return 0;
}
