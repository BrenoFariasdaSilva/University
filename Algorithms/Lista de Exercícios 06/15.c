#include <stdio.h>

void printBoxProgressive(int height, int width, int max);

int main()
{
    int width = 0, height = 0, max = 0;

    printf("Digite a largura, a altura da caixa e o contador máximo: ");
    scanf("%d %d %d", &width, &height, &max);
    printf("\n");

    printBoxProgressive(height, width, max);

    return 0;
}

void printBoxProgressive(int height, int width, int max)
{
    int counter = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d", counter);

            if (counter == max)
            {
                counter = 0;
            }

            counter++;
        }
        printf("\n");
    }
}
