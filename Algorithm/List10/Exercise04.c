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