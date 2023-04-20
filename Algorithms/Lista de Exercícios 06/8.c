#include <stdio.h>

void numbersInFull10(int n);

int main()
{
    int number = 0;

    printf("Digite um numero entre -10 e 10: ");
    scanf("%d", &number);

    printf("\n");

    numbersInFull10(number);  
      
    return 0;
}

void numbersInFull10(int n)
{
    if (n < -10 || n > 10)
    {
        printf("Entrada inválida!");
    }

    if (n == 0)
    {
        printf("%d: Zero \n", n);
    }

    if (n == 1)
    {
        printf("%d: Mais Um \n", n);
    }

    if (n == 2)
    {
        printf("%d: Mais Dois \n", n);
    }

    if (n == 3)
    {
        printf("%d: Mais Três \n", n);
    }

    if (n == 4)
    {
        printf("%d: Mais Quatro \n", n);
    }
            
    if (n == 5)
    {
        printf("%d: Mais Cinco \n", n);
    }
            
    if (n == 6)
    {
        printf("%d: Mais Seis \n", n);
    }
            
    if (n == 7)
    {
        printf("%d: Mais Sete \n", n);
    }
            
    if (n == 8)
    {
        printf("%d: Mais Oito \n", n);
    }
            
    if (n == 9)
    {
        printf("%d: Mais Nove \n", n);
    }

    if (n == 10)
    {
        printf("%d: Mais Dez \n", n);
    }

    if (n == -1)
    {
        printf("%d: Menos Um \n", n);
    }

    if (n == -2)
    {
        printf("%d: Menos Dois \n", n);
    }

    if (n == -3)
    {
        printf("%d: Menos Três \n", n);
    }

    if (n == -4)
    {
        printf("%d: Menos Quatro \n", n);
    }
            
    if (n == -5)
    {
        printf("%d: Menos Cinco \n", n);
    }
            
    if (n == -6)
    {
        printf("%d: Menos Seis \n", n);
    }
            
    if (n == -7)
    {
        printf("%d: Menos Sete \n", n);
    }
            
    if (n == -8)
    {
        printf("%d: Menos Oito \n", n);
    }
            
    if (n == -9)
    {
        printf("%d: Menos Nove \n", n);
    }

    if (n == -10)
    {
        printf("%d: Menos Dez \n", n);
    }     
}