#include <stdio.h>

#define SIZE 5

void minBills(int money);

int main()
{
    int money = 0;

    printf("Digite um valor inteiro: ");
    scanf("%d", &money);

    printf("\n");

    minBills(money);
      
    return 0;
}

void minBills(int money)
{   
    const int bills[SIZE] = {1, 5, 10, 50, 100};
    int count[SIZE] = {0};

    for (int i = SIZE - 1; i >= 0; i--)
    {
        count[i] = money / bills[i];
        money -= (count[i] * bills[i]);
        printf("%d cedular de %d. \n", count[i], bills[i]);
    }
}