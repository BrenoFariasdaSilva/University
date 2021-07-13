#include <stdio.h>
#include <limits.h>

#define SIZE 7

void tempReport(int days[]);

int main()
{
    int vetHistogram[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        printf("Digite a temperatura do %dº dia: ", i + 1);
        scanf("%d", &vetHistogram[i]);
    }

    printf("\n");

    tempReport(vetHistogram);
      
    return 0;
}

void tempReport(int days[])
{   
    char daysLetter[SIZE] = {'D', 'S', 'T', 'Q', 'Q', 'S', 'S'};
    const char symbol = '>';

    int average = 0, max = INT_MIN, min = INT_MAX;

    for (int i = 0; i < SIZE; i++)
    {
        average += days[i];

        if (days[i] > max)
            max = days[i];
        if (days[i] < min)
            min = days[i];

        printf("%c:", daysLetter[i]);

        for (int j = 0; j < days[i]; j++)
        {
            printf("%c", symbol);
        }
        printf("\n");
    }

    average /= 7;

    printf("A média é: %d \n", average);
    printf("A mínima é: %d \n", min);
    printf("A máxima é: %d \n", max);
}