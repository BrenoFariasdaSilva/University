#include <stdio.h>

void printBoxFilled(const int width, const int height, const char ch);

int main()
{
    int width = 0, height = 0;
    char character = '\0'; 

    printf("Digite a largura e a altura da caixa: ");
    scanf("%d %d", &width, &height);

    printf("\n");
    getchar();

    printf("Digite o caracter da linha: ");
    scanf("%c", &character);

    printBoxFilled(width, height, character);

    return 0;
}

void printBoxFilled(const int width, const int height, const char ch)
{
    for (int i = 0; i < width * height; i++)
    {
        if (i % width == 0)
        {
            printf("\n");
        }
        printf("%c", ch);
    }
}
