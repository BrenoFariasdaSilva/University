#include <stdio.h>

#define SIZE 100

void stringTrim(char str[]);

int main()
{
    char Str[SIZE] = {0};

    printf("Digite a primeira string:");
    scanf("%99[^\n]", Str);
    printf("\n");

    getchar();
        
    stringTrim(Str);        

    return 0;
}

void stringTrim(char str[])
{
    int nSpaces = 0, count = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 32 && str[i + 1] != '\0')
        {
            nSpaces++;
            str[i] = str[i+1];
            str[i + 1] = 32;
        }  

        count++;
    }

    str[count - nSpaces] = '\0';

    printf("%s \n", str);
}