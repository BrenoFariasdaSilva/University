#include <stdio.h>

int main()
{
    int penultimoNum = 0, ultimoNum = 1, valorAtual = 0, n = 0;

    printf("Digite o valor de uma posicao: ");
    scanf("%d", &n);

    for (int i = 1; i < n; i++)
    {
        valorAtual = penultimoNum + ultimoNum;

        penultimoNum = ultimoNum;

        ultimoNum = valorAtual;
    }

    printf("O numero na posição %d na serie de Fibonacci e: %d", n, valorAtual);
    
    return 0;
}