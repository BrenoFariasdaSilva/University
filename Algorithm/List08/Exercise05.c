#include <stdio.h>

void stringToUpper(char str[]);

int main()
{
    char Str[100] = {0};

    printf("Digite uma string: \n");
    scanf("%99[^\n]", &Str);

    stringToUpper(Str);
      
    return 0;
}

void stringToUpper(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 97 && str[i] <= 122)
            str[i] -= 32;
    }

    printf("%s \n", str);
}