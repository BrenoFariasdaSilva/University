#include <stdio.h>

int main()
{
    /********************************************************* 
     * Redireciona as streams padrão para os arquivos.
     * Dessa forma, tanto o scanf quanto o printf estão 
     * vinculados aos arquivos.
    *********************************************************/
   freopen("Entrada.in", "r", stdin);
   freopen("Saida.out", "w", stdout);

    int a, b;

    // ENTRADA
    scanf("%d %d", &a, &b);
    
    // PROCESSAMENTO
    int soma = a + b;

    
    // SAÍDA
    printf("Soma dos dois valores inteiros: ");
    printf("%d\n", soma);

    return 0;
}