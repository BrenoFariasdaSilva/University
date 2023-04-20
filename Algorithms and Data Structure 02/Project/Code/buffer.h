#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#include "big_file.h"

/**************************************
* DADOS
**************************************/

enum
{
    ATIVO,
    INATIVO
};

typedef struct buffer
{
    int quant_registros_buffer;
    int quant_max_registros_buffer;
    int quant_buffers;
    int bloco;
    int status_buffer;
    int status_arquivo;
    char *arq_nome;
    ITEM_VENDA *itens;
} Buffer;

/**************************************
* PROTÓTIPOS
**************************************/

//PROTOTIPOS DO BUFFER ENTRADA
Buffer **BE_CriarVetor(int quant_arq_temp, int quant_reg_buffer_entrada);
Buffer *BE_Criar(char *nome_arq_temp, int quant_reg_buffer_entrada, int quant_arq_temp);

void BE_Reencher(Buffer *buffer);
void BE_Proximo(Buffer *buffer);
ITEM_VENDA BE_Consumir(Buffer *buffer);
void BE_Destruir(Buffer** vetor_buffers);

bool BE_Vazio(Buffer *buffer_entrada);
bool BE_VetorVazio(Buffer **buffer_entrada);

//PROTOTIPOS DO BUFFER SAIDA
Buffer *BS_Criar(char *nome_arq_saida, int quant_reg_buffer_saida);
void BS_Inserir(Buffer* buffer_saida, ITEM_VENDA menor_item);
void BS_Despejar(Buffer* buffer_saida);
void BS_Destruir(Buffer* buffer_saida);
