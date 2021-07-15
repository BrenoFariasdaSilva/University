#include "tad_timer.h"
#include <stdlib.h>
#include <time.h>

struct timer
{
    clock_t Start;
    clock_t End;
    clock_t ElapsedTime;
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
    t->Start = clock ();
}

void timer_stop(Timer* t)
{
    t->End = clock ();
}

float timer_resultado(Timer* t)
{
    int timer_verify = data_validation (t);

    if (timer_verify == -1)
    {
        return -1;
    }

    t->ElapsedTime = (float) ((t->End) - (t->Start)) / CLOCKS_PER_SEC;

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
    t->ElapsedTime = -1;
}

void timer_desalocar(Timer** t)
{
    free(t);
    t = NULL;
}