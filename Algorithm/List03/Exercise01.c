#include <stdio.h>

int main()
{
    int valor1 = 0, valor2 = 0;
    char caracter = 0;

    printf("Digite uma operacao com 2 operandos inteiros e um operador: ");
    scanf("%d %c %d", &valor1, &caracter, &valor2);

    if ((caracter == '+') || (caracter == '-') || (caracter == '*') || (caracter == '/'))
    {
        if (caracter == '+')
        {
            printf("%d %c %d = %d \n", valor1, caracter, valor2, valor1 + valor2);
        }

        if (caracter == '-')
        {
            printf("%d %c %d = %d \n", valor1, caracter, valor2, valor1 - valor2);
        }

        if (caracter == '*')
        {
            printf("%d %c %d = %d \n", valor1, caracter, valor2, valor1 * valor2);
        }

        if (caracter == '/')
        {
            printf("%d %c %d = %d \n", valor1, caracter, valor2, valor1 / valor2);
        }
    }
 
    else
    {
        printf("Dados invalidos! \n");
    }

    return 0;
}
