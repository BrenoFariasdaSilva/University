#include <stdio.h>
#include <string.h>

void printStringReversed(char str[]);

int main()
{
    char Str[10] = {0};  

    printf("Digite uma string: \n");
    fgets(Str, 10, stdin);

    printStringReversed(Str);
      
    return 0;
}

void printStringReversed(char str[])
{
    int length = 0;

    length = strlen(str);

    for (int i = length; i >= 0; i--)
    {
        printf("%c", str[i]);
    }
}
