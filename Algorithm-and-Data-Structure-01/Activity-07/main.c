#include <stdio.h>
#include "tad_teste.h"

int main()
{
    Teste* t1 = teste_criar("Testes para vericar operadores relacionais");
    teste_verificar(t1, 1==1, "Teste para expressao 1==1");
    teste_verificar(t1, 20>20 == 0, "20>20 == 0");
    teste_verificar(t1, 5<=5, "5<=5");

    Teste* t2 = teste_criar("Testes para verificar operadores aritmeticos");
    teste_verificar(t2, 2*5 == 10, "2*5 == 10");
    teste_verificar(t2, 2+2 == 4, "2+2 == 4");

    teste_relatorio(t1);
    teste_relatorio(t2);
    
    teste_desalocar(&t1); 
    teste_desalocar(&t2);

    return 0;
}