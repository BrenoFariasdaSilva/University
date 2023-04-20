#include "lista_incidencia.h"

void teste_criar(){
    int n;
    scanf("%d\n", &n);

    Lista* l = lista_criar(n);
    bool resultado = true;
    for (int i=0; i < l->nos; i++){
        resultado = resultado && (l->vetor[i] == NULL);
    }
    printf("%s", (resultado ? "TRUE" : "FALSE"));
    lista_destruir(&l);
}

void teste_inserir()
{
    int n;
    scanf("%d\n", &n);

    Lista* l = lista_criar(n);
    int origem, destino;
    char str[500];

    scanf("%d %d\n", &origem, &destino);
    while(origem != -1){
        lista_inserirCaminho(l, origem, destino);
        scanf("%d %d\n", &origem, &destino);
    }
    lista_toString(l, str);
    printf("%s", str);
    lista_destruir(&l);
}

void teste_remover()
{
    int n;
    scanf("%d\n", &n);

    Lista* l = lista_criar(n);
    int origem, destino;
    char str[500];

    scanf("%d %d\n", &origem, &destino);
    while(origem != -1){
        lista_inserirCaminho(l, origem, destino);
        scanf("%d %d\n", &origem, &destino);
    }
    // remoÃ§Ã£o
    scanf("%d %d\n", &origem, &destino);
    while(origem != -1){
        lista_removerCaminho(l, origem, destino);
        scanf("%d %d\n", &origem, &destino);
    }
    lista_toString(l, str);
    printf("%s", str);
    lista_destruir(&l);
}

void teste_temCaminho()
{
    int n;
    scanf("%d\n", &n);

    Lista* l = lista_criar(n);
    int origem, destino;
    char str[500];

    scanf("%d %d\n", &origem, &destino);
    while(origem != -1){
        lista_inserirCaminho(l, origem, destino);
        scanf("%d %d\n", &origem, &destino);
    }
    // tem caminho
    scanf("%d %d\n", &origem, &destino);
    while(origem != -1){
        bool ida = lista_temCaminho(l, origem, destino);
        bool volta = lista_temCaminho(l, destino, origem);
        printf("(%d)(%d)\n", ida, volta);
        scanf("%d %d\n", &origem, &destino);
    }
    lista_destruir(&l);
}

int main()
{
    int opcao;
    scanf("[%d]\n", &opcao);
    if(opcao == 1){
        teste_criar();
    }else if(opcao == 2){
        teste_inserir();
    }else if(opcao == 3){
       teste_remover();
    }else if(opcao == 4){
       teste_temCaminho();
    }

    return 0;
}