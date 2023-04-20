#include <stdio.h>

int main()
{
    char caracter = 0;

    printf("Digite um caractere: ");
    scanf("%c", &caracter);

    if ((caracter >= 'a' && caracter <= 'z') || (caracter >= 'A' && caracter <= 'Z'))
    {
        printf("O caracter e uma letra!");
    }

    else
    {
        printf("O caracter nao e uma letra!");
    }

    return 0;
}
