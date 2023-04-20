
#include <stdio.h>

int main()
{
    int num = 0;
    float res = 0;

    printf("Digite um valor inteiro: ");
    scanf("%d", &num);

    res = (num % 2);

    if (res == 0)
    {
        printf("O numero %d e par! \n", num);
    }
    else
    {
        printf("O numero %d e impar! \n", num);
    }
      
    return 0;
}
