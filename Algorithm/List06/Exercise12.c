#include <stdio.h>

void printBoxCustom(int width, int height, char fill, char edge);

int main()
{
    int largura = 0, altura = 0;
    char caracterLinha, caracterPonta;

    printf("Digite a altura e a largura do desenho: ");
    scanf("%d %d", &altura, &largura);

    printf("\n");
    getchar();

    printf("Digite o caracter da linha: ");
    scanf("%c", &caracterLinha);
    

    printf("\n");
    getchar();
    
    printf("Digite o caracter das pontas: ");
    scanf("%c", &caracterPonta);

    printBoxCustom(largura, altura, caracterLinha, caracterPonta);
      
    return 0;
}

void printBoxCustom(int width, int height, char fill, char edge)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((j == 0 || j == width-1) || (i == 0 || i == height-1))
                printf("%c", edge);
            else
                printf("%c", fill);   
        }
    printf("\n");   
    }
}