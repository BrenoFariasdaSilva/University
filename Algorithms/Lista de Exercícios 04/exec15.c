#include <stdio.h>

int main()
{
    int number = 1, cand1 = 0, cand2 = 0, cand3 = 0, cand4 = 0, nulo = 0, branco = 0;

    while (number != 0)
    {
        printf("\nDigite o valor do seu voto: ");
        scanf("%d", &number);

        switch (number)
        {
            case 1:
                cand1++;
            break;

            case 2:
                cand2++;
            break;

            case 3:
                cand3++;
            break;

            case 4:
                cand4++;
            break;  

            case 5:
                nulo++;
            break;

            case 6:
                branco++;
            break;
        }
    }

    int maior = cand1;

    if (cand2 > maior)
    {
        cand2 += branco;
    }

    if (cand3 > maior)
    {
        cand3 += branco;
    }

    if (cand4 > maior)
    {
        cand4 += branco;
    }

    printf("Canditado 01: %d \n",cand1);
    printf("Canditado 02: %d \n",cand2);
    printf("Canditado 03: %d \n",cand3);
    printf("Canditado 04: %d \n",cand4);
    printf("Nulo: %d \n", nulo);
    printf("Branco: %d \n",branco);
     
    return 0;
}
