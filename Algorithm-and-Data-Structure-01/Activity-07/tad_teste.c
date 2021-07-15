#include "tad_teste.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct teste
{
    char testName[200];
    int Total;
    int Passed;
    int Failed;
};

void initializeTest (Teste* t, char * testDescription);
void PrintExpression (bool test, const char * expression);

// Funções Auxiliares.

void initializeTest (Teste* t, char * testDescription)
{
    strcpy (t->testName, testDescription);
    t->Total = 0;
    t->Passed = 0;
    t->Failed = 0;
}

void PrintExpression (bool test, const char * expression)
{
    if (test == true)
    {
        printf("[OK]: %s \n", expression);
    }

    else
    {
        printf("Erro: %s \n", expression);
    }
}

// Implementação.

Teste* teste_criar(char* descricao)
{
    Teste* newTest = (Teste*) malloc (sizeof(Teste));

    initializeTest (newTest, descricao);

    return newTest;
}

void teste_verificar(Teste* t, int condicao, char *mensagem)
{
    if (condicao == true)
    {
        PrintExpression(true, mensagem);
        t->Total++;
        t->Passed++;
    }

    else
    {
        PrintExpression(false, mensagem);
        t->Total++;
        t->Failed++;
    }
}

void teste_relatorio(Teste* t)
{
    printf("\nNome do Teste: %s \n", t->testName);
    printf("Total: %d\n", t->Total);
    printf("Passaram: %d\n", t->Passed);
    printf("Falharam: %d\n", t->Failed);
}

void teste_desalocar(Teste** t)
{
    free (*t);
    *t = NULL;
}