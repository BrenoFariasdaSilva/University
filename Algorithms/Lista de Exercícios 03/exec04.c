#include <stdio.h>

int main()
{
    int year = 0;

    printf("Digite um ano com 4 algarismos: ");
    scanf("%d", &year);

    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        printf("O ano e bissexto! \n");
    }

    else
    {
        printf("O ano nao e bissexto! \n");
    }

    return 0;
}