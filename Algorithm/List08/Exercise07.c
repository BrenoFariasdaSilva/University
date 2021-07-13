#include <stdio.h>

#define SIZE 100

int countWords(char str[]);

int main()
{
    char str[SIZE] = {0};
    int wordsCount = 0;

    printf("Digite uma string:");
    scanf("%99[^\n]", &str);
    printf("\n");

    getchar();

    wordsCount = countWords(str);

    printf("Number of words in the string: %d \n", wordsCount);

    return 0;
}

int countWords(char str[])
{
    int words = 1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 32)
            words++;
    }

    return words;
}  