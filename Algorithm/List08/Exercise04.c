#include <stdio.h>

void stringReport(char str[]);

int main()
{
    char Str[10] = {0};

    printf("Digite uma string: \n");
    scanf("%s", &Str);

    stringReport(Str);
      
    return 0;
}

void stringReport(char str[])
{
    int values = 0, letters = 0, characters = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 48 && str[i] <= 57)
            values++;

        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
            letters++;

        if ((str[i] >= 32 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64))
            characters++;
    }

    printf("Values: %d \n", values);
    printf("Letters: %d \n", letters);
    printf("Characters: %d \n", characters);
}
