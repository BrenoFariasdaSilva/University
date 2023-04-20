#include "hashtable_ea.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void THEA_Redimensionar (THEA* TH, int novo_m) {
	ELEM* nova, *antiga;
	int i, m_antigo;

	nova = malloc (sizeof (ELEM) * novo_m);

	for (i = 0; i < novo_m; i++) {
		nova[i].estado = E_LIVRE;
	}

	antiga = TH->TH;
	m_antigo = TH->m;
	TH->TH = nova;
	TH->m = novo_m;
	TH->n = 0;

	for (i = 0; i < m_antigo; i++) {
		if (antiga[i].estado == E_OCUPADO) {
			THEA_Inserir(TH, antiga[i].chave, antiga[i].valor);
		}
	}
	
	free (antiga);
}

int THEA_Hash(THEA* TH, int chave, int k)
{
	return ((chave % TH->m) + k) % TH->m;
}

THEA* THEA_Criar(int m){
	THEA* novo;
	int i = 0;

	novo = malloc(sizeof(THEA));
	novo->TH = malloc(sizeof(ELEM) * m);
	novo->m = m;
	novo->n = 0;

	for (i = 0; i < m; i++)
		novo->TH[i].estado = E_LIVRE;
	return novo;
}

int THEA_Inserir(THEA *TH, int chave, int valor){
	int h, k = 0, h_inicial;

	if (TH->m > TH->m / 2) {
		printf("Redimensionado de %d para %d (n = %d) \n", TH->m, TH->m*2, TH->n);
		THEA_Redimensionar(TH, TH->m*2);
	}

	h = THEA_Hash(TH, chave, k);
	h_inicial = h;

	while (TH->TH[h].estado == E_OCUPADO) {
		if (TH->TH[h].chave == chave) {
			TH->n--;
			break;
		}
		k++;
		h = THEA_Hash(TH, chave, k);

		if (h == h_inicial)
			return -1;
	}

	TH->n++;
	TH->TH[h].chave = chave;
	TH->TH[h].valor = valor;
	TH->TH[h].estado = E_OCUPADO;

	return h;
}

int THEA_Buscar(THEA *TH, int chave){
	int h, h_inicial, k = 0;

	h = THEA_Hash(TH, chave, k);
	h_inicial = h;

	while (TH->TH[h].estado != E_LIVRE) {
		if (TH->TH[h].estado == E_OCUPADO && TH->TH[h].chave == chave) {
			return h;
		}

		k++;

		h = THEA_Hash(TH, chave, k);

		if (h_inicial == h) {
			return -1;
		}
 	}

	return -1;
}

void THEA_Remover(THEA* TH, int chave){
	int p;
	p = THEA_Buscar(TH, chave);

	if(p != -1){
		TH->TH[p].estado = E_APAGADO;
		TH->n--;
	}
}

int THEA_ClusterMaximo(THEA* TH){
	int biggest = INT_MIN;
    int size = -1;

    for (int i = 0; i < TH->m; i++) {
        if (TH->TH[i].estado != E_LIVRE) {
            size = TH->n++;
        }
        if (TH[i].n > biggest){
            biggest = size;
        }
    }
    return biggest;
}

float THEA_TamMedioClusters(THEA* TH){
	int sum = 0;
    int validLists = TH->m;

    for (int i = 0; i < TH->m; i++) {
        if (TH->TH[i].estado != E_LIVRE) {
            sum+=TH->n++;
        } else {
            validLists--;
        }
    }
    return (double)sum / validLists;
}