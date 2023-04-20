
#include "lista_incidencia.h"

int main(){
    char str[500];
    
    Lista* l = lista_criar(6);

    lista_inserirCaminho(l, 0, 1);
    lista_inserirCaminho(l, 0, 2);
    lista_inserirCaminho(l, 0, 4);
    lista_inserirCaminho(l, 1, 3);
    lista_inserirCaminho(l, 2, 3);
    lista_inserirCaminho(l, 2, 4);

    lista_toString(l, str);
    printf("%s\n", str);

    lista_removerCaminho(l, 1, 3);
    lista_removerCaminho(l, 0, 1);
    lista_toString(l, str);
    printf("%s", str);
    return 0;
}
