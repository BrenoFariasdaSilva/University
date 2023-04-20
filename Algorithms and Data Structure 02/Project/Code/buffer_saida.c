#include "buffer.h"
#include "arquivo.h"

/**************************************
* IMPLEMENTAÇÃO
**************************************/

//--------------- CRIAR BUFFERS DE SAIDA --------------------------------------------
Buffer *BS_Criar(char *nome_arq_saida, int quant_reg_buffer_saida)
{

    ITEM_VENDA *itens = (ITEM_VENDA *)malloc(quant_reg_buffer_saida * sizeof(ITEM_VENDA));
    for (int i = 0; i < quant_reg_buffer_saida; i++)
    {
        itens[i].id = 0;
        itens[i].id_venda = 0;
        itens[i].desconto = 0;
        itens[i].data = 0;
        itens[i].obs[0] = '\0';
    }

    Buffer *buffer_saida = (Buffer *)malloc(sizeof(Buffer));
    buffer_saida->quant_registros_buffer = 0;
    buffer_saida->quant_max_registros_buffer = quant_reg_buffer_saida;
    buffer_saida->quant_buffers = 1;
    buffer_saida->bloco = 0;
    buffer_saida->status_buffer = ATIVO;
    buffer_saida->status_arquivo = ATIVO;
    buffer_saida->arq_nome = nome_arq_saida;
    buffer_saida->itens = itens;

    return buffer_saida;
}


//--------------- INSERIR NO BUFFER DE SAIDA --------------------------------------------
void BS_Inserir(Buffer* buffer_saida, ITEM_VENDA menor_item){
    buffer_saida->itens[buffer_saida->quant_registros_buffer] = menor_item;
    buffer_saida->quant_registros_buffer++;
}


//--------------- ESCREVER NO ARQUIVO DE SAIDA --------------------------------------------
void BS_Despejar(Buffer* buffer_saida){
    //printf("despejando...\n");
    FILE* arq_saida = fopen(buffer_saida->arq_nome, "wb");

    fseek(arq_saida, 0, SEEK_END);

    if(buffer_saida->quant_registros_buffer < buffer_saida->quant_max_registros_buffer){
        fwrite(buffer_saida->itens, sizeof(ITEM_VENDA), buffer_saida->quant_registros_buffer, arq_saida);
        buffer_saida->status_buffer = INATIVO;
    } else{
        fwrite(buffer_saida->itens, sizeof(ITEM_VENDA), buffer_saida->quant_max_registros_buffer, arq_saida);
    }

    buffer_saida->quant_registros_buffer = 0;
    buffer_saida->bloco++;
    fclose(arq_saida);
}


//--------------- DESTRUIR BUFFER DE SAIDA --------------------------------------------
void BS_Destruir(Buffer* buffer_saida){
    free(buffer_saida->itens);
    free(buffer_saida);
}