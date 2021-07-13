#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int find(int n, int vet[n], int elem);

int main()
{
    int n = SIZE, vector[SIZE] = {0}, elem = 0, result = 0;

    printf("Digite o valor a ser procurado no array/vetor: ");
    scanf("%d", &elem);
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = -5 + rand () % SIZE;
    }

    result = find(n, vector, elem);

    if (result != -1)
    {
        printf("O valor esta no índice %d do array/vetor. \n", result);

        for (int i = 0; i < SIZE; i++)
        {
            printf("%d ", vector[i]);
        }
    }

    else
        printf("O valor não foi encontrado no array/vetor! \n");
      
    return 0;
}

int find(int n, int vet[n], int elem)
{
   for (int i = 0; i < n; i++)
    {
        if (vet[i] == elem)
            return i;
    }

    return -1;     
}