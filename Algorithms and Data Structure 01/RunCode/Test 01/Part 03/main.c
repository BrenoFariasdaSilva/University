#include "tad_estoque.h"
#include "tad_produto.h"


int main(){
    
    Estoque* e = estoque_criar("estoque");
    Produto* p1 = produto_criar(1, "produtoA", 1.0);
    Produto* p2 = produto_criar(2, "produtoB", 2.0);
    Produto* p3 = produto_criar(3, "produtoB", 3.0);

    estoque_anexar(e, p1);
    estoque_anexar(e, p2);
    estoque_anexar(e, p3);

    estoque_imprimir(e);
    
    return 0;
}