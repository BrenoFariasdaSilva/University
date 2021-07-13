#include <stdio.h>

int main()
{
    int number = 0, A = 0, B = 0;

    printf("SUM Supreme! \n");
    printf("1 - Set A \n");
    printf("2 - Set B \n");
    printf("3 - Show A + B \n");
    printf("4 - Show A x B \n");
    printf("5 - Exit \n");

    while (number != 5)
    {
        printf("Digite um uma opcao: ");
        scanf("%d", &number);

        switch (number)
        {
            case 1:
                printf("Digite o valor de A: ");
                scanf("%d", &A);
                break;

            case 2:
                printf("Digite o valor de B: ");
                scanf("%d", &B);
                break;

            case 3:
                printf("A soma e: %d \n", A + B);
                break;

            case 4:
                printf("A multiplicacao e: %d \n", A * B);
                break;
        }
    }

    return 0;
}
