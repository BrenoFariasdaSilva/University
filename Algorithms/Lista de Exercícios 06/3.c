#include <stdio.h>
#include <stdlib.h>

void printRandom(int n, int max);

int main()
{
    int number = 0, max = 0;

    printf("Digite a quantidade de números e o seu valor máximo: ");
    scanf("%d %d", &number, &max);

    printf("\n");

    printRandom (number, max);
      
    return 0;
}

void printRandom(int n, int max)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", -100 + (rand () % max * 2));
    }
    printf("\n");
}
