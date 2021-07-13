#include <stdio.h>

int main()
{
    int timesTable = 0, multiplier = 1;
    
    printf("insert any int number: \n");
    scanf("%d", &timesTable);

    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d = %d \n", timesTable, multiplier++, timesTable * multiplier);
    printf("%d * %d= %d \n", timesTable, multiplier++, timesTable * multiplier);

    return 0;
}