#include <stdio.h>

int main()
{
    int N = 0, D = 0;

    printf("Digite o numero de linhas e do deslocamento: \n");
    scanf("%d%d", &N, &D);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N * 2; j++)
        {
            if ((i % 2 != 0) && (j == 0))
            {
                for (int z = 0; z < D; z++)
                {
                    printf(" ");
                }  
            }
            printf("X");
        }
        printf("\n");
    }
      
    return 0;
}

