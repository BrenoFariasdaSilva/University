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