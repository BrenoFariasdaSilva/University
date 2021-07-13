#include <stdio.h>

#define SIZE 10

void readVector(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    readVector(n, vector);
      
    return 0;
}

void readVector(int n, int vet[n])
{   
    int value = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Digite o valor da posição %d do array: ", i);
        scanf("%d", &value);

        vet[i] = value;
    } 

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}