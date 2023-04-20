#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "big_file.h"

/**************************************
* PROTÓTIPOS
**************************************/

void Arquivo_Dividir(const char *nome_arq_entrada, int quant_arq_temp, int quant_reg_total);
void ArquivosTemporarios_Remover(int quant_arq_temp);
