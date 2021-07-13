#include <stdio.h>
#include <string.h>
#include <limits.h>

#define rows 4
#define cols 10

void printStringsMinMax(int n, int len, char list[n][len]);

int main()
{
    char m[rows][cols] = {"Oi", "Breno", "Farias", "Adeus"};

    printStringsMinMax(rows, cols, m);
 
    return 0;
}

void printStringsMinMax(int n, int len, char list[n][len])
{ 
    int max = INT_MIN;
    int min = INT_MAX;
    int length = 0;
    char MaxMin[2] = {0};

    for (int i = 0; i < rows; i++)
    {
        length = strlen(list[i]);

        if (length > max)
        {
            max = length;
            MaxMin[0] = i;
        }

        if (length < min)
        {
            min = length;
            MaxMin[1] = i;
        }
    }

    printf("Max: %s \n", list[MaxMin[0]]);
    printf("Min: %s \n", list[MaxMin[1]]);
}