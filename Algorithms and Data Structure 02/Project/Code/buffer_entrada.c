#include "buffer.h"
#include "arquivo.h"

/**************************************
* IMPLEMENTAÇÃO
**************************************/

//--------------- CRIAR VETOR DE BUFFERS DE ENTRADA -----------------------------------
Buffer **BE_CriarVetor(int quant_arq_temp, int quant_reg_buffer_entrada)
{
    Buffer **vetor_buffer_entrada = (Buffer **)malloc(quant_arq_temp * sizeof(Buffer *));

    for (int i = 0; i < quant_arq_temp; i++)
    {
        char nome_arq_temp[100];
        sprintf(nome_arq_temp, "P%d.dat", i);

        vetor_buffer_entrada[i] = BE_Criar(nome_arq_temp, quant_reg_buffer_entrada, quant_arq_temp);
    }

    return vetor_buffer_entrada;
}

//--------------- CRIAR BUFFERS DE ENTRADA --------------------------------------------
Buffer *BE_Criar(char *nome_arq_temp, int quant_reg_buffer_entrada, int quant_arq_temp)
{

    Buffer *buffer_entrada = (Buffer *)malloc(sizeof(Buffer));
    ITEM_VENDA *itens = (ITEM_VENDA *)malloc(quant_reg_buffer_entrada * sizeof(ITEM_VENDA));
    FILE *arq_temp = fopen(nome_arq_temp, "rb");

    fread(itens, sizeof(ITEM_VENDA), quant_reg_buffer_entrada, arq_temp);

    buffer_entrada->quant_registros_buffer = quant_reg_buffer_entrada;
    buffer_entrada->quant_max_registros_buffer = quant_reg_buffer_entrada;
    buffer_entrada->quant_buffers = quant_arq_temp;
    buffer_entrada->bloco = 1;
    buffer_entrada->status_buffer = ATIVO;
    buffer_entrada->status_arquivo = ATIVO;
    buffer_entrada->arq_nome = nome_arq_temp;
    buffer_entrada->itens = itens;

    fclose(arq_temp);

    return buffer_entrada;
}

//--------------- REENCHER BUFFER ----------------------------------------------
void BE_Reencher(Buffer *buffer)
{
    FILE *arq_temp = fopen(buffer->arq_nome, "rb");
    ITEM_VENDA *itens;

    fseek(arq_temp, buffer->bloco * buffer->quant_max_registros_buffer * sizeof(ITEM_VENDA), SEEK_SET);
    int inicio = ftell(arq_temp);
    fseek(arq_temp, 0, SEEK_END);
    int fim = ftell(arq_temp);
    int tam_restante = fim - inicio;
    fseek(arq_temp, buffer->bloco * buffer->quant_max_registros_buffer * sizeof(ITEM_VENDA), SEEK_SET);

    if (tam_restante <= buffer->quant_max_registros_buffer * sizeof(ITEM_VENDA)){

        itens = (ITEM_VENDA *)malloc(tam_restante);
        fread(itens, sizeof(ITEM_VENDA), tam_restante / sizeof(ITEM_VENDA), arq_temp);
        buffer->quant_registros_buffer = tam_restante / sizeof(ITEM_VENDA);

        buffer->status_arquivo = INATIVO;
        free(buffer->itens);
        buffer->itens = itens;

    } else{

        itens = (ITEM_VENDA *)malloc(buffer->quant_max_registros_buffer * sizeof(ITEM_VENDA));
        fread(itens, sizeof(ITEM_VENDA), buffer->quant_max_registros_buffer, arq_temp);
        buffer->quant_registros_buffer = buffer->quant_max_registros_buffer;

        free(buffer->itens);
        buffer->itens = itens;
        buffer->bloco++;
    }
}

void BE_Proximo(Buffer *buffer){
    
    for(int i = 0; i < buffer->quant_registros_buffer - 2; i++){

        int prox = i + 1;
        buffer->itens[i] = buffer->itens[prox];

    }

}

//--------------- CONSUMIR ITEM VENDA DO BUFFER ----------------------------------------------
ITEM_VENDA BE_Consumir(Buffer *buffer){

    ITEM_VENDA item = buffer->itens[0];

    buffer->quant_registros_buffer--;

    if(buffer->quant_registros_buffer == 0 && buffer->status_arquivo == ATIVO){
        BE_Reencher(buffer);
    } else{
        BE_Proximo(buffer);
    }

    return item;
}

//--------------- BUFFER VAZIO --------------------------------------------------------
bool BE_Vazio(Buffer *buffer_entrada)
{
    return (buffer_entrada->quant_registros_buffer == 0 ? true : false);
}
//--------------- VETOR DE BUFFERS VAZIO ----------------------------------------------
bool BE_VetorVazio(Buffer **buffer_entrada){

    for (int i = 0; i < buffer_entrada[0]->quant_buffers; i++){

        if (!BE_Vazio(buffer_entrada[i])){
            return false;
        }
    }

    return true;
}

void BE_Destruir(Buffer** vetor_buffers){
    int quant_buffers = vetor_buffers[0]->quant_buffers;
    
    for (int i = 0; i < quant_buffers; i++){
        free(vetor_buffers[i]->itens);
        free(vetor_buffers[i]);
    }
    
    free(vetor_buffers);
}