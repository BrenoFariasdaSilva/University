#include <stdio.h>
#include <string.h>

#define SIZE 100

int stringContains(char str[], char sub[]);
void stringTrim(char str[]);

int main()
{
    char str[SIZE] = {0};

    printf("Digite uma String:");
    scanf("%99[^\n]", str);

    int result = stringContains(str, "da");    

    if (result != 0)
        printf("%s \n", str);      

    else
        printf("A SubString não foi encontrada na String. \n");

    return 0;
}

int stringContains(char str[], char sub[])
{
    int SubLength = strlen(sub);
    int times = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        int aux = 0;

        if (str[i] == sub[0])
        {
            for (int j = i; j < SubLength + i; j++)
            {
                if (str[j] == sub[j - i])
                    aux++;
            }
        }

        if (aux == SubLength)
        {
            for (int j = 0; j < SubLength; j++)
            {
                str[i + j] = 32;
            }

            stringTrim(&str);

            times++;
        }
    }

    return times;
}

void stringTrim(char str[])
{
    int nSpaces = 0, count = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 32 && str[i + 1] == 32)
        {
            nSpaces++;
            str[i] = str[i + 1];
            str[i + 1] = 32;
        }  

        count++;
    }

    str[count - nSpaces] = '\0';
}
