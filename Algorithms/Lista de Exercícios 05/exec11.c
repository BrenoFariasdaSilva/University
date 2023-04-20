#include <stdio.h>

int main()
{
    int linhas = 0, number = 0;

    printf("Digite um valor: ");
    scanf("%d", &linhas);

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            number++;
            printf("%d ", number);
        }

        printf("\n");
    }

    return 0;
}
