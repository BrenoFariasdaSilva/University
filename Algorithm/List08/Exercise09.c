#include <stdio.h>

#define SIZE 100

void stringCapitalize(char str[]);

int main()
{
    char str[SIZE] = {0};

    printf("Digite uma string:");
    scanf("%99[^\n]", str);
    printf("\n");

    getchar();

    stringCapitalize(str);

    return 0;
}

void stringCapitalize(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != 32 && str[i - 1] == 32)
        {
            if (str[i] >= 97 && str[i] <= 122)
                str[i] -= 32;
        }

        else
        {
            if (str[i] >= 65 && str[i] <= 90)
                str[i] += 32;
        }   
    }

    printf("%s", str);
}