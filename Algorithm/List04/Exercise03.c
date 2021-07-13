#include <stdio.h>

int main()
{
    int number = 0;

    printf("Digite o numero de linhas:");
    scanf("%d", &number);

    printf("\n");

    for (int i = 0; i < number; i++)
    {
        printf("Linha %d. \n", number - i);
    }
    
    return 0;
}