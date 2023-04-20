#include <stdio.h>

int main()
{
    int number = 0, verifyNumber = 0, sum = 0, unity = 0, value;

    printf("Digite os digitos de sua conta: \n");
    scanf("%d", &number);

    value = number;

    for (int divider = 100000; divider > 0; divider /= 10)
    {
        unity = value / divider;
        value -= (unity * divider);
        sum += unity; 
    }
      
    verifyNumber = sum % 10;

    printf("Os digitos sao: %06d-%d", number, verifyNumber);

    return 0;
}
