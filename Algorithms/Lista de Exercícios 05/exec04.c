#include <stdio.h>

int main()
{
    int penultimoNum = 0, ultimoNum = 1, valorAtual = 0, numero = 0, sum = 0, ntermos = 0;

    while (sum < 4000000)
    {
        if (valorAtual % 2 == 0)
        {
            sum += valorAtual;
        }        
        valorAtual = penultimoNum + ultimoNum;

        penultimoNum = ultimoNum;

        ultimoNum = valorAtual;

        ntermos++;
    }

    printf("Ntermos: %d", ntermos);
    
    return 0;
}