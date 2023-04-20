/* Exercício 1

#include <stdio.h>
#include <math.h>

struct Point
{
    float x;
    float y;
};

float distance2D(struct Point p1, struct Point p2);

int main()
{
    struct Point p1 = {0.2f, 0.2f};
    struct Point p2 = {3.2f, 4.2f};

    float dist = distance2D(p1, p2); 

    printf("A distancia entre os pontos P1 e P2 e: %.2f", dist); 
      
    return 0;
}

float distance2D(struct Point p1, struct Point p2)
{
    float distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

    return distance;
}

*/

/* Exercício 2
#include <stdio.h>
#include <math.h>

#define N 4

struct Point
{
    float x;
    float y;
};

void distanceVector(int n, struct Point v[n]);

int main()
{
    struct Point v[N] = {0, 1, 3, 4, 0, 2, 0, 3};

    distanceVector(N, v);
      
    return 0;
}

void distanceVector(int n, struct Point v[n])
{
    for (int i = 0; i <= N; i+=2)
    {
        float distance = sqrt(pow(v[i + 1].x - v[i].x, 2) + pow(v[i + 1].y - v[i].y, 2));

        printf("A distancia entre os pontos v[%d] e v[%d] e: %.2f \n", i, i + 1, distance); 
    }
}
*/

/* Exercício 3
#include <stdio.h>
#include <time.h>

struct Date 
{
    int day;
    int mon;
    int year;
};

struct Date get_current_date()
{
    time_t now;
    //retorna a contagem de segundos desde 01/01/1970 (padrão Unix)

    time(&now);
    // converte time para calendário e retorna uma struct contendo
    // os campos dia, mês, ano, hora, minuto e segundo

    struct tm* p_time = localtime(&now);

    // copia os dados do struct tm em Heap para um struct Date e o devolve
    struct Date d;
    d.day = p_time->tm_mday;
    d.mon = p_time->tm_mon + 1; // na struct, mês 0-11
    d.year= p_time->tm_year + 1900; // na struct, conta ano a partir de 1900

    return d;
}

int main ()
{
    struct Date bornDate = {17, 4, 2001};
    struct Date currentDate = get_current_date();

    int age = currentDate.year - bornDate.year;

    if(currentDate.mon < bornDate.mon)
        age--;

    else if(currentDate.mon == bornDate.mon)
        if(currentDate.day > bornDate.day)
            age--;

    printf("Your age is: %d", age);

    return 0;
}

*/

/* Exercício 4
#include <stdio.h>
#include <time.h>

struct Person 
{
    char name[51];
    int day;
    int mon;
    int year;
};

struct Person get_current_date()
{
    time_t now;
    //retorna a contagem de segundos desde 01/01/1970 (padrão Unix)

    time(&now);
    // converte time para calendário e retorna uma struct contendo
    // os campos dia, mês, ano, hora, minuto e segundo

    struct tm* p_time = localtime(&now);

    // copia os dados do struct tm em Heap para um struct Date e o devolve
    struct Person d;
    d.day = p_time->tm_mday;
    d.mon = p_time->tm_mon + 1; // na struct, mês 0-11
    d.year= p_time->tm_year + 1900; // na struct, conta ano a partir de 1900

    return d;
}

void printData(struct Person p);
int numberOfWords(struct Person p);

int main ()
{
    struct Person person = {"Breno Farias da Silva", 17, 4, 2001};
    
    printData(person);

    return 0;
}

void printData(struct Person p)
{
    struct Person currentDate = get_current_date();

    int age = currentDate.year - p.year;

    if(currentDate.mon < p.mon)
        age--;

    else if(currentDate.mon == p.mon)
        if(currentDate.day > p.day)
            age--;

    int words = numberOfWords(p);

    printf("Your name is: %s \n", p.name);
    printf("Your name has %d words \n", words);
    printf("Your age is: %d \n", age);
}

int numberOfWords(struct Person p)
{
    int count = 1;

    for (int i = 0; p.name[i] != '\0'; i++)
    {
        if (p.name[i] == 32)
            count++;
    }

    return count;
}
*/

/* Exercício 5
#include <stdio.h>
#include <time.h>

#define SIZE 2

struct Person 
{
    char name[51];
    int day;
    int mon;
    int year;
};

struct Person get_current_date()
{
    time_t now;
    //retorna a contagem de segundos desde 01/01/1970 (padrão Unix)

    time(&now);
    // converte time para calendário e retorna uma struct contendo
    // os campos dia, mês, ano, hora, minuto e segundo

    struct tm* p_time = localtime(&now);

    // copia os dados do struct tm em Heap para um struct Date e o devolve
    struct Person d;
    d.day = p_time->tm_mday;
    d.mon = p_time->tm_mon + 1; // na struct, mês 0-11
    d.year= p_time->tm_year + 1900; // na struct, conta ano a partir de 1900

    return d;
}

void printPersonVector(int n, struct Person v[n]);
int numberOfWords(struct Person p);

int main ()
{
    struct Person person[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        printf("Write your name: \n");
        scanf("%[^\n]", &person[i].name);

        printf("Write the day you were born: \n");
        scanf("%d", &person[i].day);

        printf("Write the month you were born: \n");
        scanf("%d", &person[i].mon);

        printf("Write the year you were born: \n");
        scanf("%d", &person[i].year);

        printf("\n");

        getchar();
    }
    
    printPersonVector(SIZE, person);

    return 0;
}

void printPersonVector(int n, struct Person v[n])
{
    struct Person currentDate = get_current_date();

    for (int i = 0; i < n; i++)
    {
        int age = currentDate.year - v[i].year;

        if(currentDate.mon < v[i].mon)
            age--;

        else if(currentDate.mon == v[i].mon)
            if(currentDate.day > v[i].day)
                age--;

        int words = numberOfWords(v[n]);

        printf("Your name is: %s \n", v[i].name);
        printf("Your name has %d words \n", words);
        printf("Your age is: %d \n", age);
    }
}

int numberOfWords(struct Person p)
{
    int count = 1;

    for (int i = 0; p.name[i] != '\0'; i++)
    {
        if (p.name[i] == 32)
            count++;
    }

    return count;
}
*/

/* Exercício 6

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
        scanf("%[^\n]", &people[i].type);

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