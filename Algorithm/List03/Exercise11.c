#include <stdio.h>

int main()
{
    char caracter = 0;

    printf("Digite um caractere: ");
    scanf("%c", &caracter);

    if ((caracter >= 'a' && caracter <= 'z') || (caracter >= 'A' && caracter <= 'Z'))
    {
        if (caracter >= 'a' && caracter <= 'z')
        {
            printf("O caracter e uma letra!: %c \n", caracter + 32);
            /* (caracter - 32) porque, como a tabela ASCII segue um padrão, 
            o número representativo de uma letra minúscula comparada a uma letra
            maiúscula é sempre "-32". Logo, se 'a' = 97, implics que 'A' = 97 - 32 = 65.
            */
        }

        else
        {
            printf("O caracter e uma letra!: %c \n", caracter);
        }
    }

    else
    {
        printf("O caracter nao e uma letra!");
    }

    return 0;
}
