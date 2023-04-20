#include "tad_timer.h"
#include <stdlib.h>
#include <time.h>

struct timer
{
    time_t Start;
    time_t End;
    time_t ElapsedTime;
};

// Auxiliary Functions Prototypes

int data_validation (Timer* t);

// Function Development

Timer* timer_criar()
{
    Timer* CreateTime = (Timer*) malloc (sizeof(Timer));

    timer_reset(CreateTime);

    return CreateTime;
}

void timer_start(Timer* t)
{
    time(&t->Start);
}

void timer_stop(Timer* t)
{
    time(&t->End);
}

float timer_resultado(Timer* t)
{
    int timer_verify = data_validation (t);

    if (timer_verify == -1)
    {
        return -1;
    }

    t->ElapsedTime = ((t->End) - (t->Start));

    return t->ElapsedTime;
}

int data_validation (Timer* t)
{
    if (t->Start == -1 || t->End == -1)
    {
        return -1;
    }

    return 0;  
}

void timer_reset(Timer* t)
{
    t->Start = -1;
    t->End = -1;
    t->ElapsedTime = 0;
}

void timer_desalocar(Timer** t)
{
    free(t);
    t = NULL;
}