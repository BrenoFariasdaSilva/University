#include <stdio.h>
#include <math.h>

#define N 4

struct Point
{
    float x;
    float y;
};

void distanceVector(int n, struct Point v[n]);

int main()
{
    struct Point v[N] = {0, 1, 3, 4, 0, 2, 0, 3};

    distanceVector(N, v);
      
    return 0;
}

void distanceVector(int n, struct Point v[n])
{
    for (int i = 0; i <= N; i+=2)
    {
        float distance = sqrt(pow(v[i + 1].x - v[i].x, 2) + pow(v[i + 1].y - v[i].y, 2));

        printf("A distancia entre os pontos v[%d] e v[%d] e: %.2f \n", i, i + 1, distance); 
    }
}