#include <stdio.h>
#include <string.h>

#define SIZE 100

int stringContains(char str[], char sub[]);
void stringTrim(char str[]);

int main()
{
    char str1[SIZE] = "Breno Farias da Silva";
        
    stringTrim(str1);

    printf("%s", str1);        

    return 0;
}

void stringTrim(char str[])
{
    int position = stringContains (str, "da");   

    if (position == 0)
        printf("A String2 nao esta dentro da String1");

    else
        str[position] = '\0';
}

int stringContains(char str[], char sub[])
{
    int SubLength = strlen(sub);
    int aux = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub[0])
        {
            for (int j = i; j < SubLength + i; j++)
            {
                if (str[j] == sub[j - i])
                    aux++;
            }
        }

        if (aux == SubLength)
            return i;
    }

    return 0;
}