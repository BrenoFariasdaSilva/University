#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "big_file.h"

static inline void trocar(ITEM_VENDA* x, ITEM_VENDA* y){
    ITEM_VENDA aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

static void embaralhar(ITEM_VENDA* v, int ini, int fim){
    int i, j;

    for(i = fim-1; i > ini; i--){
        j = (rand() % (i + 1));
        j = j <= ini? ini+1 : j;
        trocar(&v[i], &v[j]);
    }

}

void gerar_array_iv(const char* arquivo_saida, unsigned int n_registros, int seed){
    ITEM_VENDA* iv;
    FILE* saida;
    uint32_t i;
    time_t t = time(NULL);
    
    srand(seed);

    iv = malloc(sizeof(ITEM_VENDA) * n_registros);

    for(i = 0; i < n_registros; i++){
        iv[i].id = i;
        iv[i].id_venda = i + (rand() % 2);
        iv[i].desconto = (rand() % 10) / (float)100;
        iv[i].data = t + (( -1 * (rand() % 30)) * 86400) ;
        //printf("id_venda = %u, desconto = %.2f, data: %u\n", iv[i].id_venda, iv[i].desconto, iv[i].data);
        iv[i].obs[0] = '\0';
    }

    embaralhar(iv, 0, n_registros);

    saida = fopen(arquivo_saida, "wb");
    if(saida == NULL){
        perror("Erro");
        exit(1);
    }


    fwrite(iv, sizeof(ITEM_VENDA), n_registros, saida);
    fclose(saida);


    return;
}
