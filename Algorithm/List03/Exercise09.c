#include <stdio.h>

int main()
{
    int valor1 = 0, valor2 = 0, valor3 = 0, temp = 0;

    printf("Digite tres valores inteiros: \n");
    scanf("%d %d %d", &valor1, &valor2, &valor3);


    if ( valor1 > valor2 )
    {
        temp = valor2;
        valor2 = valor1; 
        valor1 = temp;
    }

    if ( valor2 > valor3 )
    {
        temp = valor3; 
        valor3 = valor2;
        valor2 = temp;
    }

    if ( valor1 > valor2)
    {
        temp = valor2;
        valor2 = valor1;
        valor1 = temp;
    }

    printf("Os valores ordenados: %d <= %d <= %d. \n", valor1, valor2, valor3);

    return 0;
}
