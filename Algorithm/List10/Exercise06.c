#include <stdio.h>
#include <string.h>

#define SIZE 2

struct Employee 
{
    char name[50];
    float salary;
    char type[50];
    // D - Developer
    // E - Designer
    // M - Manager
    // S - Support 
};

void printReport(int n, struct Employee v[n]);
float salarySum (int n, struct Employee v[n]);
float salaryAverage (int n, struct Employee v[n]);

int main ()
{
    struct Employee people[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        printf("Write your name: \n");
        scanf("%[^\n]", &people[i].name);
        getchar();

        printf("Write the day you were born: \n");
        scanf("%d", &people[i].salary);

        getchar();

        printf("Write your type: \n");
        scanf("%[^\n]s", &people[i].type);

        printf("\n");

        getchar();
    }
    
    printReport(SIZE, people);

    return 0;
}

void printReport(int n, struct Employee v[n])
{
    float a =  salarySum(n, v);
    printf("Salary Sum: %.2f \n",a);
    printf("Salary Average: %.2f \n", salaryAverage(n, v));
}

float salarySum (int n, struct Employee v[n])
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += v[i].salary;
    }

    return sum;
}

float salaryAverage (int n, struct Employee v[n])
{
    float average = 0;

    for (int i = 0; i < n; i++)
    {
        average += v[i].salary;
    }

    average /= n;

    return average;
}
