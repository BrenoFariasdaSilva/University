#include <stdio.h>

struct aluno{
  int ra;          // 4 bytes
  char nome[72];   // 72 bytes
  float notas[5];  // 20 bytes
};


typedef struct aluno Tipo;

int main(){
  
  Tipo* p = 0;
  printf("p + 0:   %d (%d bytes)\n", p+0, sizeof(Tipo));
  printf("p + 1:   %d (%d bytes)\n", p+1, sizeof(Tipo));
  printf("p + 2:   %d (%d bytes)\n", p+2, sizeof(Tipo));
  printf("p + 3:   %d (%d bytes)\n", p+3, sizeof(Tipo));
  printf("p + 4:   %d (%d bytes)\n", p+4, sizeof(Tipo));

  printf("\n");

  printf("Ponteiro generico com casting\n\n");
  void* g = 100;
  printf("         g + 0:  %d\n", g + 0);
  printf("         g + 1:  %d\n", g + 1);
  printf("         g + 2:  %d\n", g + 2);
  printf("         g + 3:  %d\n", g + 3);
  printf("\n");

  printf("   (int*)g + 0:  %d\n", (int*)g + 0);
  printf("   (int*)g + 1:  %d\n", (int*)g + 1);
  printf("   (int*)g + 2:  %d\n", (int*)g + 2);
  printf("   (int*)g + 3:  %d\n", (int*)g + 3);
  printf("\n");

  printf("(double*)g + 0:  %d\n", (double*)g + 0);
  printf("(double*)g + 1:  %d\n", (double*)g + 1);
  printf("(double*)g + 2:  %d\n", (double*)g + 2);
  printf("(double*)g + 3:  %d\n", (double*)g + 3);

  
  
  return 0;
}