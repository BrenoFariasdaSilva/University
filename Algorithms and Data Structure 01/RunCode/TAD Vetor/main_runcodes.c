#include "tad_vetor.h"

void teste01(){
    // Teste do anexar
    int quantidade, num;
    
    Vetor* v = vet_criar(10);
    scanf("[%d] ", &quantidade);
    for (int i=0; i < quantidade; i++){
        scanf("%d", &num);
        vet_anexar(v, num);        
    }
    
    char str[300];
    vet_toString(v, str);
    printf("%s\n", str);
    scanf("\n");

}

void teste02(){
    // teste do inserir
    int quantidade, num, pos;
    scanf("[%d] ", &quantidade);

    Vetor* v = vet_criar(10);

    for (int i=0; i < quantidade; i++){
        scanf(" (%d,%d)", &num, &pos);
        vet_inserir(v, num, pos);
    }
    
    char str[300];
    vet_toString(v, str);
    printf("%s\n", str);
    scanf("\n");

}

void teste03(){
    // Teste substituir e dobrar o tamanho
    int quantidade, num;
    scanf("[%d]", &quantidade);

    Vetor* v = vet_criar(1);
    
    for (int i=0; i < quantidade; i++){
        vet_anexar(v, i+1);
    }

    for (int i=0; i < vet_tamanho(v); i++){
        vet_substituir(v, i, -2);
    }

    char str[300];
    vet_toString(v, str);
    printf("%s\n", str);
    scanf("\n");
}

void teste04()
{
    // Remover por posicao

    int quantidade, pos;
    scanf("[%d]", &quantidade);

    Vetor* v = vet_criar(10);

    for (int i=0; i < quantidade; i++)
    {
        vet_anexar(v, (i+1)*10);
    }

    int elemento;
    bool resultado;

    // remove posições que não existem
    resultado = vet_removerPosicao(v, -1, &elemento);
    printf("%d ", resultado);
    resultado = vet_removerPosicao(v, vet_tamanho(v)+1, &elemento);
    printf("%d ", resultado);
    
    //remove do meio
    pos = vet_tamanho(v) / 2;
    vet_removerPosicao(v, pos, &elemento);
    printf("%d ", elemento);
    
    // remove do inicio
    vet_removerPosicao(v, 0, &elemento);
    printf("%d ", elemento);

    // remove do final
    vet_removerPosicao(v, vet_tamanho(v)-1, &elemento);
    printf("%d ", elemento);

    while(vet_tamanho(v) > 0)
    {
        vet_removerPosicao(v, 0, &elemento);
        printf("%d ", elemento);
    }

    scanf("\n");
    printf("\n");
}

void teste05(){
    // Remover por elemento

    int quantidade;
    scanf("[%d]", &quantidade);

    Vetor* v = vet_criar(10);

    for (int i=0; i < quantidade; i++){
        vet_anexar(v, (i+1)*10);
    }
    
    int elemento;
    int pos;

    // remove elementos que não existem
    pos = vet_removerElemento(v, -10);
    printf("%d ", pos);
    pos = vet_removerElemento(v, vet_tamanho(v) * 10+1);
    printf("%d ", pos);

    // remove do meio
    vet_elemento(v, vet_tamanho(v)/2, &elemento);
    pos = vet_removerElemento(v, elemento);
    printf("%d ", pos);

    //remove do inicio
    vet_elemento(v, 0, &elemento);
    pos = vet_removerElemento(v, elemento);
    printf("%d ", pos);
    
    //remove do final
    vet_elemento(v, vet_tamanho(v)-1, &elemento);
    pos = vet_removerElemento(v, elemento);
    printf("%d ", pos);

    while(vet_tamanho(v) > 0){
       vet_elemento(v, 0, &elemento);
        pos = vet_removerElemento(v, elemento);
        printf("%d ", pos); 
    }
    
    scanf("\n");
    printf("\n");
}

int main(){
    teste01();

    teste02();

    teste03();

    teste04();

    teste05();
}