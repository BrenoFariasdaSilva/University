#include <stdio.h>
#include <math.h>

#define SIZE 10

void distances(int n, int points[n]);

int main()
{
    int coordinatesPair[SIZE] = {0}, n = SIZE;

    for (int i = 0; i < SIZE; i+=2)
    {
        printf("Digite um par ordenado: ");
        scanf("%d %d", &coordinatesPair[i], &coordinatesPair[i + 1]);
    }

    printf("\n");

    distances(n, coordinatesPair);
      
    return 0;
}

void distances(int n, int points[n])
{   
    int pointsDistance[SIZE/2] = {0};

    for (int i = 0; i < n/2; i++)
    {
        pointsDistance[i] = sqrt(((points[i + 2] - points[i]) * (points[i + 2] - points[i])) + ((points[i + 1])*(points[i+3])));
    }

    for (int i = 0; i < n/2; i++)
    {
        printf("A distancia do %d ponto e: %d \n", i + 1, pointsDistance[i]);
    }
}