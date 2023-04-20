#include "arquivo.h"
#include "ordenacao.h"

/**************************************
* IMPLEMENTAÇÃO
**************************************/

//--------------- FUNÇÃO DIVIDIR ARQUIVO EM ARQUIVOS TEMPORARIOS -------------
 
void Arquivo_Dividir(const char* nome_arq_entrada, int quant_arq_temp, int quant_reg_total){

    int quant_reg_arqTemp = ceil((double)quant_reg_total / quant_arq_temp);

    ITEM_VENDA* vetor_itens = (ITEM_VENDA*) malloc(quant_reg_arqTemp * sizeof(ITEM_VENDA));
    FILE* arq_entrada = fopen(nome_arq_entrada, "rb");


    for(int i = 0; i < quant_arq_temp; i++){
        char nome_arq_temp[50];
        sprintf(nome_arq_temp, "P%d.dat", i);
        FILE* arq_temp = fopen(nome_arq_temp, "wb");

        fseek(arq_entrada, i * quant_reg_arqTemp * sizeof(ITEM_VENDA), SEEK_SET);
        int inicio = ftell(arq_entrada);
        fseek(arq_entrada, 0, SEEK_END);
        int fim = ftell(arq_entrada);
        int tam_restante_arq_entrada = fim - inicio;
        fseek(arq_entrada, i * quant_reg_arqTemp * sizeof(ITEM_VENDA), SEEK_SET);

        int quant_registros_para_serem_lidos = tam_restante_arq_entrada / 1024;

        if(quant_registros_para_serem_lidos > quant_reg_arqTemp){
            fread(vetor_itens, sizeof(ITEM_VENDA), quant_reg_arqTemp, arq_entrada);
            QuickSort(vetor_itens, 0, quant_reg_arqTemp-1);
            fwrite(vetor_itens, sizeof(ITEM_VENDA), quant_reg_arqTemp, arq_temp);
        } else{
            fread(vetor_itens, sizeof(ITEM_VENDA), quant_registros_para_serem_lidos, arq_entrada);
            QuickSort(vetor_itens, 0, quant_registros_para_serem_lidos-1);
            fwrite(vetor_itens, sizeof(ITEM_VENDA), quant_registros_para_serem_lidos, arq_temp);
        }

        fclose(arq_temp);
    }
    fclose(arq_entrada);
}

//--------------- FUNÇÃO REMOVER ARQUIVOS TEMPORARIOS -------------

void ArquivosTemporarios_Remover(int quant_arq_temp){
    for (int i = 0; i < quant_arq_temp; i++){
        char nome[100];
        sprintf(nome, "P%d.dat", i);
        int del = remove(nome);
    }
}