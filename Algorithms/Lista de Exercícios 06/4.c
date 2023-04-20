#include <stdio.h>

int summation(int n);

int main()
{
    int number = 0;

    printf("Digite um valor inteiro: ");
    scanf("%d", &number);

    printf("\n");

    int result = summation(number);   

    printf("O somatório e: %d \n", result);
      
    return 0;
}

int summation(int n)
{
    int sum  = 0;

    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }

    return sum;
}
