#include <stdio.h>

int main()
{
    int linhas = 0, colunas = 0;

    printf("Digite o numero de linhas \n");
    scanf("%d", &linhas);

    printf("Digite o numero de colunas \n");
    scanf("%d", &colunas);

    for (int i = 0; i < linhas; i++)
    {
        printf("||");

        for (int j = 0;  j < colunas; j++)
        {
            printf("=");
        }
        printf("||");
        printf("\n");
    }
      
    return 0;
}
