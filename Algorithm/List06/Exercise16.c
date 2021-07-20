#include <stdio.h>
#include <limits.h>
    
void batchReport(int* max, int* min);    

int main()
{
    int max = INT_MIN, min = INT_MAX;

    batchReport(&max, &min);

    printf("Max: %d \n", max);
    printf("Min: %d \n", min);
      
    return 0;
}

void batchReport(int* max, int* min)
{
    int input = 1;

    while (input != 0)
    {
        printf("Digite um valor: (0 para sair)");
        scanf("%d", &input);
        printf("\n");

        if (input == 0)
        {
            break;
        }

        else
        {
            if (input > *max)
                *max = input;

            if (input < *min)
                *min = input;
        }
    }
}
