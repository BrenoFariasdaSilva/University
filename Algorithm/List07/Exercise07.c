#include <stdio.h>

#define SIZE 10

void replaceAll(int n, int vet[n], int elem);

int main()
{
    int n = SIZE, vector[SIZE] = {0}, element = 0;

    printf("Digite o valor a para alterar o array/vetor: ");
    scanf("%d", &element);

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = i + 1;
    }

    replaceAll(n, vector, element);
      
    return 0;
}

void replaceAll(int n, int vet[n], int elem)
{
    for (int i = 0; i < n; i++)
    {
        vet[i] = elem - 1;
    } 

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}