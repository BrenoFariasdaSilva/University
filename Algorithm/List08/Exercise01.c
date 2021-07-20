#include <stdio.h>

void printString();

int main()
{
    printString();
      
    return 0;
}

void printString()
{
    char Str[10] = {};

    printf("Digite uma string: \n");
    scanf("%s", Str);

    printf("%s", Str);
}
