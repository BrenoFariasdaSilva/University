#include <stdio.h>

int Prime(const int Number);

int main()
{
    int cases = 0;

    scanf("%d", &cases);

    if (cases < 1 || cases > 100)
    {
        return -1;
    }

    int Values[cases];

    for (int i = 0; i < cases; i++)
    {
        scanf("%d", &Values[i]);

        if (Values[i] < 1 || Values[i] > 108)
        {
           return -1;
        }
    }

    for (int i = 0; i < cases; i++)
    {
        int CheckResult = Prime(Values[i]);

        if (CheckResult == 0)
        {
            printf("%d eh primo", Values[i]);
        }

        else
        {
            printf("%d nao eh primo", Values[i]);
        }

        printf("\n");
    }

    return 0;
}

int Prime(const int Number)
{
    for (int i = 2; i < Number / 2; i++)
    {
        if ((Number % i) == 0)
        {
            return -1;
        }
    }

    return 0;
}
