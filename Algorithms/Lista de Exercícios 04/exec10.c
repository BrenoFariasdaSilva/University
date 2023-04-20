#include <stdio.h>

int main()
{
    int number = 0, digito = 0, numberInvertido = 0, algarismos = 0, aux = 0;

    printf("Digite um valor inteiro: \n");
    scanf("%d", &number);

    aux = number;

    // Conta o numero de algarismos para inverter.
    while ((aux % 10) != 0) 
    {
        aux /= 10;
        algarismos++;
    } 

    // Invertendo os valores.
    while ((number % 10) != 0)  
    {   
        digito = number % 10;
        number /= 10;

        algarismos--;
        aux = 1;

        // Potência do algarismo (10 ^ algarismo)
        for (int i = 0; i < algarismos; i++)
        {
            aux *= 10;
        }

        numberInvertido += (digito * aux);
    }

    // Imprimindo os algarismos na ordem correta.
    while ((numberInvertido % 10) != 0)  
    {
        digito = numberInvertido % 10;
        numberInvertido /= 10;
        printf("%d ", digito);
    }

    return 0;
}
