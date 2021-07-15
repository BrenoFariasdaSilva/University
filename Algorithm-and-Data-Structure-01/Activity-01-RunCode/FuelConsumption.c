#include <stdio.h>

double litersCalculus (const int time, const int averageSpeed);

int main()
{
    int time = 0;
    int averageSpeed = 0;  

    scanf("%d", &time);
    scanf("%d", &averageSpeed);

    const double liters = litersCalculus(time, averageSpeed);

    printf("%.3lf", liters);
      
    return 0;
}

double litersCalculus (const int time, const int averageSpeed)
{
    const double distance = averageSpeed * time;
    const double liters = distance / 12;

    return liters;
}
