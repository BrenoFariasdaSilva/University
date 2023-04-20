#include <stdio.h>

int main()
{
    int a = 0, b = 0, quociente = 0;
    
    printf("Digite dois valores inteiros: \n");
    scanf("%d %d", &a, &b);
    
    quociente = a / b;

    printf("A %% B = %d \n", a % b);
    printf("A %% B = %d \n", a - (b * quociente));

    return 0;
}





