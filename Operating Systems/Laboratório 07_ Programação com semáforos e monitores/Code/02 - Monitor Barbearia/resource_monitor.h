#ifndef __BARBER_H__
#define __BARBER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define QUANT_CADEIRAS 5
#define QUANT_MAX_CLIENTES 11

/* --- concurrency controls --- */
pthread_mutex_t mutex;
pthread_cond_t cond_barbeiro;
pthread_cond_t cond_cliente;

/* --- resource --- */
int cadeiras_ocupadas;
int cadeiras_vazias;
int clientes_atendidos;

/* --- monitor operations --- */
void initMonitor();
void destroyMonitor();
void *barbeiro(void *arg);
void *cliente(void *arg);


#endif