#include <stdio.h>

void clearBuffer ();

int main() 
{
    char v[10];

    printf("Digite caracteres do vetor ");
    scanf(" %10[^\n]", v);
    printf("\n");
    clearBuffer();

    printf("%s ", v);

    return 0;
}

void clearBuffer ()
{
    while (getchar() != '\n');
}