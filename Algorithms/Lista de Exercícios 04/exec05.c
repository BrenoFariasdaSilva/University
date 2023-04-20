#include <stdio.h>

int main()
{
    printf("Caracteres da Tabela ASCII: \n");

    printf("DEC   OCT   HEX    CHR: \n");

    for (int i = 33; i < 127; i++)
    {
        printf("%03d   %03o   %03x   %3c\n", i, i, i, i);
    }
      
    return 0;
}
