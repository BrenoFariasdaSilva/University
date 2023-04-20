#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "big_file.h"
#include "buffer.h"
#include "arquivo.h"
#include "ordenacao.h"

int main()
{

    //------------------- DEFINIÇÃO DOS CONTROLES -------------------

    int QUANT_REGISTROS_TOTAL = 10240;                         //N - Quantidade de registros
    int TAM_MAXIMO_BUFFER_ENTRADA = 1024;                    //B - Tamanho máximo do buffer de entrada
    int TAM_MAX_BUFFER_SAIDA = TAM_MAXIMO_BUFFER_ENTRADA / 8;   //S - Tamanho máximo do buffer de saída


    //------------------- DEFINIÇÃO DOS SUBCONTROLES -------------------
    int TAM_ARQUIVO_ENTRADA = 1024 * QUANT_REGISTROS_TOTAL;
    int QUANT_ARQUIVOS_TEMPORARIOS = ceil(TAM_ARQUIVO_ENTRADA / TAM_MAXIMO_BUFFER_ENTRADA) + 1;
    int QUANT_REGISTROS_BUFFER_SAIDA = TAM_MAX_BUFFER_SAIDA / 1024;
    int QUANT_REGISTROS_BUFFER_ENTRADA = ceil(((TAM_MAXIMO_BUFFER_ENTRADA - TAM_MAX_BUFFER_SAIDA) / QUANT_ARQUIVOS_TEMPORARIOS) / 1024);

    //------------------- DECLARAÇÃO DE VARIÁVEIS --------------------------------------
    clock_t t_inicio, t_fim;
    double tempo_execucao;

    //--------------- DEFINIR NOME DOS ARQUIVOS ----------------------------------------
    char *nome_arquivo_entrada = "entrada.dat";
    char *nome_arquivo_saida = "saida.dat";

    //--------------- GERAR ARQUIVO DE ENTRADA -----------------------------------------
    gerar_array_iv(nome_arquivo_entrada, QUANT_REGISTROS_TOTAL, 42);
    printf("Arquivo de entrada gerado com sucesso!\n");

    //--------------- INICIAR CRONOMETRO -----------------------------------------------
    t_inicio = clock();

    //--------------- DIVIDIR ARQUIVO DE ENTRADA EM ARQUIVOS TEMPORARIOS ---------------
    Arquivo_Dividir(nome_arquivo_entrada, QUANT_ARQUIVOS_TEMPORARIOS, QUANT_REGISTROS_TOTAL);
    printf("Arquivos temporarios gerados com sucesso!\n");

    //--------------- CRIAR BUFFERS DE ENTRADA -----------------------------------------
    Buffer **vetor_buffers_entrada = BE_CriarVetor(QUANT_ARQUIVOS_TEMPORARIOS, QUANT_REGISTROS_BUFFER_ENTRADA);
    printf("Buffers de entrada criados com sucesso!\n");

    //--------------- CRIAR ARQUIVO DE SAÍDA -------------------------------------------
    FILE *arquivo_saida = fopen(nome_arquivo_saida, "wb");
    fclose(arquivo_saida);
    printf("Arquivo de saida criado com sucesso!\n");

    //--------------- CRIAR BUFFERS DE SAIDA --------------------------------------------
    Buffer *buffer_saida = BS_Criar(nome_arquivo_saida, QUANT_REGISTROS_BUFFER_SAIDA);
    printf("Buffer de saida criado com sucesso!\n");

    //--------------- INTERCALAÇÃO DE K VIAS --------------------------------------------
    Merge_K_Vias(vetor_buffers_entrada, buffer_saida, QUANT_REGISTROS_BUFFER_SAIDA, nome_arquivo_saida, QUANT_REGISTROS_TOTAL);
    printf("Intercalacao de k vias concluida com sucesso!\n");

    //--------------- REMOVER ARQUIVOS TEMPORARIOS --------------------------------------
    ArquivosTemporarios_Remover(QUANT_ARQUIVOS_TEMPORARIOS);
    printf("Arquivos temporarios removidos com sucesso!\n");

    //--------------- DESTRUIR VETOR DE BUFFERS ----------------------------------------------
    BE_Destruir(vetor_buffers_entrada);
    printf("Vetor de buffers de entrada destruido com sucesso!\n");

    //--------------- DESTRUIR BUFFER DE SAIDA -------------------------------------------------
    BS_Destruir(buffer_saida);
    printf("Buffer de saida destruido com sucesso!\n");

    //--------------- FINALIZAR CRONOMETRO ----------------------------------------------
    t_fim = clock();
    tempo_execucao = (double)(t_fim - t_inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f\n", tempo_execucao);

    printf("FIM\n");
    return 0;
}