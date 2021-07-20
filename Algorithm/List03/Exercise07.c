#include <stdio.h>
#include <math.h>

int main()
{
    int value = 0, DM = 0, M = 0, C = 0, D = 0, U = 0, sum = 0;

    printf("Digite um valor de 5 algarismos: ");
    scanf("%d", &value);

    if (value > 99999)
    {
        printf("Valor fora da escala!(0 - 99999) \n");
    }

    else
    {
        DM =  (value / pow(10, 4));
    
        M = ((value / pow(10, 3))- (DM * 10));

        C = (value / 100 - (DM * 100 + M * 10 ));

        D = ((value / 10) - (DM * 1000 + M * 100 + C * 10));

        U = (value - (DM * 10000 + M * 1000 + C * 100 + D * 10));

        sum = DM + M + C + D + U;

        printf("A soma dos algarismos do valor %d e: %d %d %d %d %d = %d ", value, DM, M, C, D, U, sum);
    }

    return 0;
}
