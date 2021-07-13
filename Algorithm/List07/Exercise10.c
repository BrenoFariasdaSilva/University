#include <stdio.h>

#define SIZE 10

void reverseInput(int n);

int main()
{
    int n = SIZE;

    reverseInput(n);
      
    return 0;
}

void reverseInput(int n)
{   
    int vet[n], value = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Digite o valor da posição %d do array: ", i);
        scanf("%d", &value);

        vet[i] = value;
    } 

    for (int i = n - 1; i >= 0; i--)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}