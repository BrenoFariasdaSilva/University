#include <stdio.h>


int main(){
  int m[3][2] = {{10,20},{30,40},{50,60}};
  int* p = (int*)m;
  
/********************************************
* EQUIVALENCIAS
********************************************/
  printf("\n");
  printf("Enderecos\n");
  printf("m:        %u\n", m);
  printf("&m:       %u\n", &m);
  printf("m[0]:     %u\n", m[0]);
  printf("&m[0][0]: %u\n", &m[0][0]);
  printf("p:        %u\n", p);
  printf("\n");

  
/********************************************
* ORGANIZACAO
********************************************/
  printf("&m[0][0]: %u\n", &m[0][0]);
  printf("&m[0][1]: %u\n", &m[0][1]);
  printf("&m[1][0]: %u\n", &m[1][0]);
  printf("&m[1][1]: %u\n", &m[1][1]);
  printf("&m[2][0]: %u\n", &m[2][0]);
  printf("&m[2][1]: %u\n", &m[2][1]);
  printf("\n");
  
/********************************************
* ACESSO
********************************************/
  printf("p[0]:  %u\n", p[0]);
  printf("p[1]:  %u\n", p[1]);
  printf("p[2]:  %u\n", p[2]);
  printf("p[3]:  %u\n", p[3]);
  printf("p[4]:  %u\n", p[4]);
  printf("p[5]:  %u\n", p[5]);
  printf("\n");

  printf("*(p+0):  %u\n", *(p+0));
  printf("*(p+1):  %u\n", *(p+1));
  printf("*(p+2):  %u\n", *(p+2));
  printf("*(p+3):  %u\n", *(p+3));
  printf("*(p+4):  %u\n", *(p+4));
  printf("*(p+5):  %u\n", *(p+5));
  printf("\n");
  
  int qtde_colunas = 2;

  printf("p + (0 * qtde_colunas) + 0: %u\n", p + (0 * qtde_colunas) + 0);
  printf("p + (0 * qtde_colunas) + 1: %u\n", p + (0 * qtde_colunas) + 1);
  printf("p + (1 * qtde_colunas) + 0: %u\n", p + (1 * qtde_colunas) + 0);
  printf("p + (1 * qtde_colunas) + 1: %u\n", p + (1 * qtde_colunas) + 1);
  printf("p + (2 * qtde_colunas) + 0: %u\n", p + (2 * qtde_colunas) + 0);
  printf("p + (2 * qtde_colunas) + 1: %u\n", p + (2 * qtde_colunas) + 1);
  printf("\n");

  printf("*(p + (0 * qtde_colunas) + 0): %u\n", *(p + (0 * qtde_colunas) + 0));
  printf("*(p + (0 * qtde_colunas) + 1): %u\n", *(p + (0 * qtde_colunas) + 1));
  printf("*(p + (1 * qtde_colunas) + 0): %u\n", *(p + (1 * qtde_colunas) + 0));
  printf("*(p + (1 * qtde_colunas) + 1): %u\n", *(p + (1 * qtde_colunas) + 1));
  printf("*(p + (2 * qtde_colunas) + 0): %u\n", *(p + (2 * qtde_colunas) + 0));
  printf("*(p + (2 * qtde_colunas) + 1): %u\n", *(p + (2 * qtde_colunas) + 1));
  printf("\n");


  


  return 0;
}