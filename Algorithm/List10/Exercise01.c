#include <stdio.h>
#include <math.h>

struct Point
{
    float x;
    float y;
};

float distance2D(struct Point p1, struct Point p2);

int main()
{
    struct Point p1 = {0.2f, 0.2f};
    struct Point p2 = {3.2f, 4.2f};

    float dist = distance2D(p1, p2); 

    printf("A distancia entre os pontos P1 e P2 e: %.2f", dist); 
      
    return 0;
}

float distance2D(struct Point p1, struct Point p2)
{
    float distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

    return distance;
}