#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "big_file.h"
#include "buffer.h"

/**************************************
* PROTÓTIPOS
**************************************/

void Trocar(ITEM_VENDA* item_venda, int maior, int i);
int Partition(ITEM_VENDA* item_venda, int inicio, int fim);
void QuickSort(ITEM_VENDA* item_venda, int inicio, int fim);

void Merge_K_Vias(Buffer** vetor_buffers, Buffer* buffer_saida, int quant_reg_buffer_saida, char* nome_arq_saida, int quant_reg_total);








