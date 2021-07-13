#include <stdio.h>

void printStringHyphenized(char str[], char separator);

int main()
{
    char Str[10] = {0}, separator = {0};

    printf("Digite uma string: \n");
    scanf("%s", &Str);

    getchar();

    printf("Digite um caratere separador: \n");
    scanf("%c", &separator);

    printStringHyphenized(Str, separator);
      
    return 0;
}

void printStringHyphenized(char str[], char separator)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c%c", str[i], separator);
    }
}