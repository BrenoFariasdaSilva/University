#include <stdio.h>

int main()
{
    int number = 0;

    printf("Digite o numero de linhas: \n\n");
    scanf("%d", &number);

    for (int i = 0; i < number; i++)
    {
        printf("Linha %d. \n", i + 1);
    }
    
    return 0;
}