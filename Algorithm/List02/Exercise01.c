#include <stdio.h>

int main()
{
    int number01 = 0, number02 = 0;
    
    printf("Insert two int numbers: \n");
    scanf("%d %d", &number01, &number02);

    printf("A * B = %d \n", number01 * number02);
    printf("A / B = %d \n", number01 / number02);
    printf("A %% B = %d \n", number01 % number02);

    return 0;
}