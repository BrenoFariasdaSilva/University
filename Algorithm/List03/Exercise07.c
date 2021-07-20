#include <stdio.h>
#include <math.h>

int main()
{
    int valor = 0, DM = 0, M = 0, C = 0, D = 0, U = 0, soma = 0;

    printf("Digite um valor de 5 algarismos: ");
    scanf("%d", &valor);

    if (valor > 99999)
    {
        printf("Valor fora da escala!(0 - 99999) \n");
    }

    else
    {
        DM =  (valor / pow(10, 4));
    
        M = ((valor / pow(10, 3))- (DM * 10));

        C = (valor / 100 - (DM * 100 + M * 10 ));

        D = ((valor / 10) - (DM * 1000 + M * 100 + C * 10));

        U = (valor - (DM * 10000 + M * 1000 + C * 100 + D * 10));

        soma = DM + M + C + D + U;

        printf("A soma dos algarismos do valor %d e: %d %d %d %d %d = %d ", valor, DM, M, C, D, U, soma);
    }

    return 0;
}
