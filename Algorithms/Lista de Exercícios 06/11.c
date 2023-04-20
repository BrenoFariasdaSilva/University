#include <stdio.h>

void printLine(int n, char fill, char edge);

int main()
{
    int largura = 0;
    char caracterLinha, caracterPonta;

    printf("Digite a largura da linha: ");
    scanf("%d", &largura);

    printf("\n");
    getchar();

    printf("Digite o caracter da linha: ");
    scanf("%c", &caracterLinha);
    

    printf("\n");
    getchar();
    
    printf("Digite o caracter das pontas: ");
    scanf("%c", &caracterPonta);

    printLine(largura, caracterLinha, caracterPonta);
      
    return 0;
}

void printLine(int n, char fill, char edge)
{
    for (int i = 0; i < n; i++)
    {
        if (i == 0 || i == n-1)
        {
            printf("%c", edge);
        }

        else
            printf("%c", fill);   
    }
}