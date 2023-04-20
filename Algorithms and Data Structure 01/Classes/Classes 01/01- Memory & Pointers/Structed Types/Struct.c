#include <stdio.h>
#include <string.h>

typedef struct aluno{ 
    unsigned int ra; 
    char nome[12]; 
    float notas[3]; 
} Aluno;

int main(){
  
  Aluno a1 = {100, "Joao", {6.5, 8.2, 7.3}};
  Aluno a2;
  

/***********************************************
* EQUIVALENCIAS
************************************************/
  printf("&a1:        %u\n", &a1);
  printf("&a1.ra:     %u\n", &a1.ra);
  printf("&a1.nome:   %u\n", &a1.nome);
  printf("&a1.notas:  %u\n", &a1.notas);
  printf("a1.notas:   %u\n", a1.notas);
  printf("\n");
  
/***********************************************
* COPIA
************************************************/
  a2 = a1;

  printf("a1\n");
  printf("[ra]     %d\n", a1.ra);
  printf("[nome]   %s\n", a1.nome);
  printf("[nota 0] %.2f\n", a1.notas[0]);
  printf("[nota 1] %.2f\n", a1.notas[1]);
  printf("[nota 2] %.2f\n", a1.notas[2]);
  printf("\n");

  a2.ra = 300;
  strcpy(a2.nome, "Alex");

  printf("a2\n");
  printf("[ra]     %d\n", a2.ra);
  printf("[nome]   %s\n", a2.nome);
  printf("[nota 0] %.2f\n", a2.notas[0]);
  printf("[nota 1] %.2f\n", a2.notas[1]);
  printf("[nota 2] %.2f\n", a2.notas[2]);


  return 0;
}