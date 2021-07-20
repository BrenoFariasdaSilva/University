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
        fgets (person[i].name, 50, stdin);

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
