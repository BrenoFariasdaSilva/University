/*Exercício 1
#include <stdio.h>

void printString();

int main()
{
    printString();
      
    return 0;
}

void printString()
{
    char Str[10] = {};

    printf("Digite uma string: \n");
    scanf("%s", &Str);

    printf("%s", Str);
}
*/

/*Exercício 2
#include <stdio.h>
#include <string.h>

void printStringReversed(char str[]);

int main()
{
    char Str[10] = {};  

    printf("Digite uma string: \n");
    scanf("%s", &Str);

    printStringReversed(Str);
      
    return 0;
}

void printStringReversed(char str[])
{
    int length = 0;

    length = strlen(str);

    for (int i = length; i >= 0; i--)
    {
        printf("%c", str[i]);
    }
}
*/

/*Exercício 3
#include <stdio.h>

void printStringHyphenized(char str[], char separator);

int main()
{
    char Str[10] = {0}, separator = {0};

    printf("Digite uma string: \n");
    scanf("%s", &Str);

    getchar();

    printf("Digite um caratere separador: \n");
    scanf("%c", &separator);

    printStringHyphenized(Str, separator);
      
    return 0;
}

void printStringHyphenized(char str[], char separator)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c%c", str[i], separator);
    }
}
*/

/* Exercício 4
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
        if (str[i] >= 48 && str[i] =< 57)
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
*/

/* Exercício 5
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
*/

/* Exercício 6
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
    scanf("%99[^\n]", &Str1);
    printf("\n");

    getchar();

    printf("Digite a segunda string: \n");
    scanf("%99[^\n]", &Str2);
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
*/

/* Exercício 7
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
*/

/* Exercício 8
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

    for (int i = 1; str[i] != '\0'; i++)
    {
        if (str[i] == 32 && str[i - 1] != 32)
            words++;
    }

    return words;
} 
*/

/* Exercício 9
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
*/

/* Exercício 10

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
*/


/* Exercício 11
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
*/


/* Exercício 12
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
*/

/*Exercício 13
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
*/

/* Exercício 14
#include <stdio.h>

#define SIZE 100

int stringContains(char str[], char sub[]);
void stringTrim(char str[]);

int main()
{
    char str[SIZE] = {0};

    printf("Digite uma String:");
    scanf("%99[^\n]", str);

    int result = stringContains(&str, "da");    

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
*/

/*
#include <stdio.h>

#define SIZE 10

void intToString(int number, char converted[]);

int main()
{
    char str[SIZE] = {0};
    int number = 0;

    printf("Digite um valor de até 10 digitos:");
    scanf("%d", number);

    if (number > 9999999999)
        printf("Valor inválido! \n");

    intToString(number, str);    

    printf("%s \n", str);      

    return 0;
}

void intToString(int number, char converted[])
{
    int num = -1;
    int i = 0;
    int divider = 1000000000;

    while (num != 0)
    {
        converted[i] = number % divider;
        number %= divider;

         = num;

        divider *= 10;

        i++;
    }

    print
}
*/









