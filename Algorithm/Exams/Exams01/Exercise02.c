#include <stdio.h>

int main()
{
    int n = 0, maioralg = -1, menoralg = 10;

    printf("Digite um valor inteiro para encontrar o maior e o menor dígito: \n");
    scanf("%d", &n);

    while (n % 10 != 0) 
    {
        int aux = n % 10;

        if (aux > maioralg)
        {
            maioralg = aux;
        }

        if (aux < menoralg)
        {
            menoralg = aux;
        }   

        n /= 10;
    }  

    printf("Maioralg: %d \n", maioralg);
    printf("MenorAlg: %d \n", menoralg);

    return 0;
}
