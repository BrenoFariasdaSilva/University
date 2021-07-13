#include <stdio.h>

int main()
{
    int number = 0;

    printf("Digite um valor inteiro de 0 a 9: \n");
    scanf("%d", &number);

    switch (number)
    {
        case 0:
            printf("Foi digitado o numero Zero(%d)! \n", number);
        break;

        case 1:
            printf("Foi digitado o numero Um(%d)! \n", number);
        break;

        case 2:
            printf("Foi digitado o numero Dois(%d)! \n", number);
        break;

        case 3:
            printf("Foi digitado o numero Tres(%d)! \n", number);
        break;

        case 4:
        printf("Foi digitado o numero Quatro(%d)! \n", number);
        break;

        case 5:
        printf("Foi digitado o numero Cinco(%d)! \n", number);
        break;

        case 6:
        printf("Foi digitado o numero Seis(%d)! \n", number);
        break;

        case 7:
        printf("Foi digitado o numero Sete(%d)! \n", number);
        break;

        case 8:
        printf("Foi digitado o numero Oito(%d)! \n", number);
        break;

        case 9:
        printf("Foi digitado o numero Nove(%d)! \n", number);
        break;

        default:
        printf("Foi digitado um numero invalid(fora da escala 0-9)! \n");
        break;
    }
    
    return 0;
}