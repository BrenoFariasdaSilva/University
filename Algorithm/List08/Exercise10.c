#include <stdio.h>

#define SIZE 100

int stringCompare(char str1[], char str2[]);

int main()
{
    char Str1[SIZE] = {0}, Str2[SIZE] = {0};
    int result = 0;

    printf("Digite a primeira string:");
    scanf("%99[^\n]", &Str1);
    printf("\n");

    getchar();

    printf("Digite a segunda string: \n");
    scanf("%99[^\n]", &Str2);
    printf("\n");
        
    result = stringCompare(Str1, Str2);         
      
    if (result == 0)
        printf("Strings Iguais \n");
    
    if (result > 0)
        printf("String1 vem antes da String2 \n");

    if (result < 0)
        printf("String2 vem antes da String1 \n");

    return 0;
}

int stringCompare(char str1[], char str2[])
{
    for (int i = 0; str1[i] != '\0'; i++)
    {
        if (str1[i] != str2[i])
        {
            if (str1[i] < str2[i])
                return 1;   
            
            else
                return -1;
        }   
    }

    return 0;
}