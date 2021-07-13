#include <stdio.h>

void printBox01(int width, int height);

int main()
{
    int width = 0, height = 0;

    printf("Digite a largura e a altura da caixa: ");
    scanf("%d %d", &width, &height);
    printf("\n");

    printBox01(width, height);

    return 0;
}

void printBox01(int width, int height)
{
    for (int i = 1; i <= width * height; i++)
    {
        if (i % 2 == 0)
            printf("1");
        else
            printf("0");
        if (i % width == 0)
            printf("\n");
    }
}
