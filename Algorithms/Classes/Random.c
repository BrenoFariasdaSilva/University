#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t age = 0;

    printf("Digite a sua idade: ");
    scanf("%d", &age);
    printf("\n");

    printf("Sua idade: %d\n", age);

    return 0;
}