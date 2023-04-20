#include <stdio.h>

int main()
{
    int num = 0;
    int currentNumber = 2; 

    printf("Digite um valor inteiro: ");
    scanf("%d", &num);

    for (int i = 0; i < num; i++)
    {
        printf("Numero %dº: %d \n", i, currentNumber);
        currentNumber+=2;
    }
  
    return 0;
}
