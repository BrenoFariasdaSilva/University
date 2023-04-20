#include <stdio.h>

int main()
{
    int numbers = 0, currentNumber = -1; 

    printf("Digite o numero de valores impares:");
    scanf("%d", &numbers);

    printf("\n");

    for (int i = 0; i < numbers; i++)
    {
        printf("%d. \n", currentNumber += 2);
    }
    
    return 0;
}