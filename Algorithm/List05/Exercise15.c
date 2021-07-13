#include <stdio.h>

int main()
{
    int initialBalance = 0, number = -1, conta = 0, credits = 0, debit = 0; 
    float taxes = 0;

    printf("Digite o seu saldo inicial:");
    scanf("%d", &initialBalance);
    printf("\n");

    conta += initialBalance;

    while (number != 0)
    {
        printf("Digite o valor da operacao: \n");
        scanf("%d", &number);
        printf("\n");

        conta += number;

        if (number > 0)
        {
            credits += number;
        }

        if (number < 0)
        {
            debit += number;
        }
    }

    taxes = debit * 0.0035;

    printf("O total de credito da sua conta e: %d \n", credits);
    printf("O total de debito da sua conta e: %d \n", debit);
    printf("A taxa de imposto da sua conta e: %.2f \n", taxes);
    printf("O extrato da sua conta e: %d \n", conta);

    return 0;
}
