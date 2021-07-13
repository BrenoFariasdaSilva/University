#include <stdio.h>

#define SIZE 7

void histogram(int days[]);

int main()
{
    int vetHistogram[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        printf("Digite a temperatura do %dº dia: ", i + 1);
        scanf("%d", &vetHistogram[i]);
    }

    printf("\n");

    histogram(vetHistogram);
      
    return 0;
}

void histogram(int days[])
{   
    char daysLetter[SIZE] = {'D', 'S', 'T', 'Q', 'Q', 'S', 'S'};
    const char symbol = '>';

    for (int i = 0; i < SIZE; i++)
    {
        printf("%c:", daysLetter[i]);

        for (int j = 0; j < days[i]; j++)
        {
            printf("%c", symbol);
        }
        printf("\n");
    }
}