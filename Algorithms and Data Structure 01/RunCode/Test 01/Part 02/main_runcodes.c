#include "tad_produto.h"
#define MAX_LIMIT 50

Produto* le_produto();
void teste01();
void teste02();

int main()
{
    teste01();
    teste02();
    return 0;
}

Produto* le_produto()
{
    int cod;
    char descricao[50];
    float preco;

    scanf("%d ", &cod);    
    scanf("%f ", &preco);    

    fgets(descricao, MAX_LIMIT, stdin);
    int tam = strlen(descricao); 
    descricao[strlen(descricao)-1] = '\0'; // O fgets inclui na string o \n

    printf("\n");

    return produto_criar(cod, descricao, preco); 
}

// Teste da função produto_criar, produto_destruir, produto_codigo e produto_preco
void teste01()
{
    printf("Teste 01: \n");

    Produto* p = le_produto();
    char descricao[50];
    produto_descricao(p, descricao);
    printf("(01) {%d, %s, %.2f} ", produto_codigo(p), descricao, produto_preco(p));

    produto_destruir(&p);
    printf("%s\n", (p==NULL ? "true": "false"));

    printf("\n");
}

// Teste da função produto_altera_preco e produto_media_preco
void teste02()
{
    printf("Teste 02: \n");

    int qtde;
    scanf("[%d] ", &qtde);

    float preco;
    scanf("%f", &preco);
    Produto* p = produto_criar(1, "produto teste", preco);
    printf("%.2f ", produto_preco(p));
    printf("%.2f ", produto_media_preco(p));
               
    for (int i=1; i < qtde; i++){   
        scanf("%f", &preco); // 200
        produto_altera_preco(p, preco); // 100 + 200 + 300 + 400
        printf("%.2f ", produto_preco(p)); // 500
        printf("%.2f ", produto_media_preco(p)); // 350
    }

    produto_destruir(&p);

    printf("\n");
}