#include <stdio.h>
#include <string.h>

#define SIZE 100

int stringContains(char str[], char sub[]);

int main()
{
    int result = 0;

    char str1[SIZE] = "Breno Farias da Silva";
        
    result = stringContains (str1, "Farias");   

    if (result == -1)
        printf("A String2 nao esta dentro da String1");

    else
        printf("A String2 esta dentro da String1");     

    return 0;
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
            return 0;
    }

    return -1;
}