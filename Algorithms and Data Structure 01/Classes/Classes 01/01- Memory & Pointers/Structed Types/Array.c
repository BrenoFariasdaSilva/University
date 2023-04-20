#include <stdio.h>


int main(){
  int v[4] = {10,20,30,40};
  int* p = v;
  
/********************************************
* ORGANIZACAO
********************************************/
  printf("\n");
  printf("Enderecos\n");
  printf("v:     %u\n", v);
  printf("p:     %u\n", p);
  printf("&v[0]: %u\n", &v[0]);
  printf("&v[1]: %u\n", &v[1]);
  printf("&v[2]: %u\n", &v[2]);
  printf("&v[3]: %u\n", &v[3]);
  
/********************************************
* ACESSO
********************************************/
  printf("%s\n", "Acesso via Colchetes");
  printf("v[0]:   %d\n", v[0]);
  printf("p[0]:   %d\n", p[0]);
  printf("v[2]:   %d\n", v[2]);
  printf("p[2]:   %d\n", p[2]);

  printf("\n");
  printf("Acesso via Ponteiro\n");
  printf("*v:   %d\n", *v);
  printf("*p:   %d\n", *p);
  printf("*v+2: %d\n", *(v+2));
  printf("*p+2: %d\n", *(p+2));

  
/********************************************
* COPIA
********************************************/
// Como criamos uma copia de um vetor?





  return 0;
}