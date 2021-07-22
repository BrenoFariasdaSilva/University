#include <stdio.h>
#include "tad_vetor.h"

int main() 
{
    // 1. Criar um novo vetor
    Vetor* vetor = vet_criar(10);

    // 2. Inserir um elemento no final da sequência
    printf("Quantidade de elementos (Antes): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Antes): %d \n", vetor->tamanho_vetor);
    vet_anexar(vetor, 1);
    printf("Quantidade de elementos (Depois): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Depois): %d \n", vetor->tamanho_vetor);

    for (int i = 0; i < vetor->tamanho_vetor; i++)
    {
        printf("%d  ", vetor->vet[i]);
    }
    printf("\n");

    printf("Quantidade de elementos (Antes): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Antes): %d \n", vetor->tamanho_vetor);
    vet_anexar(vetor, 2);
    vet_anexar(vetor, 3);
    vet_anexar(vetor, 4);
    vet_anexar(vetor, 5);
    vet_anexar(vetor, 6);
    vet_anexar(vetor, 7);
    vet_anexar(vetor, 8);
    vet_anexar(vetor, 9);
    // vet_anexar(vetor, 10);
    // vet_anexar(vetor, 11);
    printf("Quantidade de elementos (Depois): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Depois): %d \n", vetor->tamanho_vetor);

    for (int i = 0; i < vetor->tamanho_vetor; i++)
    {
        printf("%d  ", vetor->vet[i]);
    }
    printf("\n \n");

    // 3. Inserir um elemento em qualquer posição da sequência
    printf("Quantidade de elementos (Antes): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Antes): %d \n", vetor->tamanho_vetor);
    vet_inserir(vetor, 99, 5);
    printf("Quantidade de elementos (Depois): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Depois): %d \n", vetor->tamanho_vetor);
    for (int i = 0; i < vetor->tamanho_vetor; i++)
    {
        printf("%d  ", vetor->vet[i]);
    }
    printf("\n");

    printf("Quantidade de elementos (Antes): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Antes): %d \n", vetor->tamanho_vetor);
    vet_inserir(vetor, 98, 6);
    vet_inserir(vetor, 97, 7);
    vet_inserir(vetor, 96, 8);
    vet_inserir(vetor, 95, 9);
    printf("Quantidade de elementos (Depois): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Depois): %d \n", vetor->tamanho_vetor);
    for (int i = 0; i < vetor->tamanho_vetor; i++)
    {
        printf("%d  ", vetor->vet[i]);
    }
    printf("\n \n");

    // 4. Substituir um elemento em uma determinada posição
    printf("Quantidade de elementos (Antes): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Antes): %d \n", vetor->tamanho_vetor);
    vet_substituir (vetor, 5, 111);
    printf("Quantidade de elementos (Depois): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Depois): %d \n", vetor->tamanho_vetor);
    for (int i = 0; i < vetor->tamanho_vetor; i++)
    {
        printf("%d  ", vetor->vet[i]);
    }
    printf("\n \n");

    // 5. Remover um elemento de uma determinada posição
    int elemento = 0;
    printf("Quantidade de elementos (Antes): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Antes): %d \n", vetor->tamanho_vetor);
    vet_removerPosicao(vetor, 5, &elemento);
    printf("Quantidade de elementos (Depois): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Depois): %d \n", vetor->tamanho_vetor);
    for (int i = 0; i < vetor->tamanho_vetor; i++)
    {
        printf("%d  ", vetor->vet[i]);
    }
    printf("\nElement: %d \n\n", elemento);

    // 6. Remover um elemento de acordo com o seu valor. Caso haja valores repetidos remover apenas a primeira ocorrência.
    printf("Quantidade de elementos (Antes): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Antes): %d \n", vetor->tamanho_vetor);
    int position = vet_removerElemento (vetor, 98);
    printf("Quantidade de elementos (Depois): %d \n", vetor->quantidade_elementos);
    printf("Tamanho do Vetor (Depois): %d \n", vetor->tamanho_vetor);
    for (int i = 0; i < vetor->tamanho_vetor; i++)
    {
        printf("%d  ", vetor->vet[i]);
    }
    printf("\nElement: %d \n\n", elemento);

    // 7. Recuperar quantos elementos estão armazenados na sequência.
    int size = vet_tamanho(vetor);
    printf("SIZE: Quantidade de elementos: %d \n\n", size);

    // 8. Recuperar qual elemento está armazenado em uma determinada posição
    int output = 0;
    vet_elemento (vetor, 5, &output);
    printf("Output - Elemento na posicao [%d]: %d \n\n", 5, output);

    // 9. Recuperar a posição em que um determinado elemento está armazenado. Caso haja valores repetidos, recuperar a primeira ocorrência.
    int posicao = vet_posicao (vetor, 95);
    printf("Position of the element %d: %d \n\n", 95, posicao);

    // 10. Imprimir a sequência
    printf("Printing Vector Function: \n");
    vet_imprimir (vetor);

    // 12. Devolve o vetor na forma de String
    char* string = (char*) malloc (100 * sizeof(char));
    vet_toString (vetor, string);
    printf("String: %s\n", string);

    // 11. Desalocar
    vet_desalocar(&vetor);
    return 0;
}