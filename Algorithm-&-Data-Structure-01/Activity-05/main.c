#include <stdio.h>
#include "lista_alocacao_dinamica.c"

int main()
{
    int** m = cria_matriz(2, 3, -1);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}