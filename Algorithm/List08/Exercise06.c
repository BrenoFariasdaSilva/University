#include <stdio.h>
#include <string.h>

#define SIZE 100

void stringToUpper(char str1[], char str2[]);

int stringCompareNoCase(char s1[], char s2[]);

int main()
{
    char Str1[SIZE] = {0}, Str2[SIZE] = {0};
    int result = 0;

    printf("Digite a primeira string:");
    fgets(Str1, SIZE, stdin);
    printf("\n");

    getchar();

    printf("Digite a segunda string: \n");
    fgets(Str2, SIZE, stdin);
    printf("\n");
        
    stringToUpper(Str1, Str2);         

    printf("%s \n", Str1);
    printf("%s \n", Str2);

    result = stringCompareNoCase(Str1, Str2);
      
    if (result == 0)
        printf("Strings Iguais \n");
    
    if (result > 0)
        printf("String2 vem antes da String1 \n");

    if (result < 0)
        printf("String1 vem antes da String2 \n");

    return 0;
}

void stringToUpper(char str1[], char str2[])
{
    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
    {
        if (str1[i] >= 97 && str1[i] <= 122)
            str1[i] -= 32;

        if (str2[i] >= 97 && str2[i] <= 122)
            str2[i] -= 32;
    }
}

int stringCompareNoCase(char s1[], char s2[])
{
    int result = strcmp(s1, s2);

    return result;
}
