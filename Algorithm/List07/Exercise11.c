#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void countElements(int n, int vet[n]);

int main()
{
    int vet[SIZE], n = SIZE;

    printf("Vetor: ");
    
    for (int i = 0; i < n; i++)
    {
        vet[i] = rand () % SIZE;
        printf("%d ", vet[i]);  
    }

    printf("\n");

    countElements(n, vet);
      
    return 0;
}

void countElements(int n, int vet[n])
{   
    int countVet[SIZE] = {0};

    for (int i = 0; i < n; i++)
    {
        int value = vet[i];
        countVet[value]++;
    } 

    for (int i = 0; i < n; i++)
    {
        printf("Contador do numero %d: %d \n", i, countVet[i]);
    }
}