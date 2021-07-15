#include <stdio.h>

double UnitaryCost(const double value, const double change, const int quantity);

int main()
{
    double value = 0;
    double change = 0;
    int quantity = 0;

    scanf("%lf", &value);
    scanf("%lf", &change);
    scanf("%d", &quantity);

    double PricePerUnity = UnitaryCost(value, change, quantity);

    printf("%.2lf", PricePerUnity);

    return 0;
}

double UnitaryCost(const double value, const double change, const int quantity)
{
    if (quantity == 0 || value <= change)
    {
        return -1;
    }

    double PricePerUnity = (value - change);
    PricePerUnity /= quantity;

    return PricePerUnity;
}
