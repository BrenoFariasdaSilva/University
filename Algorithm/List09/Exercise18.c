#include <stdio.h>
#define rows 4
#define cols 10

void printStrings(int n, int len, char list[n][len]);

int main()
{
    char m[rows][cols] = {"Oi", "Breno", "Farias", "Adeus"};

    printStrings(rows, cols, m);

 
    return 0;
}

void printStrings(int n, int len, char list[n][len])
{ 
    for (int i = 0; i < rows; i++)
    {
        printf("%s \n", list[i]);
    }
}