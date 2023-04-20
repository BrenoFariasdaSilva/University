/*
  Entradas do teclado:
  +  aumenta subidvisão
  -  diminui subidvisão
  f  flat shading
  s  smooth shading
  q  sair
*/

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define A 0.525731112119133696
#define B 0.850650808352039932

/* array de vértices*/
static GLfloat vdata[12][3] = {
  {-A, 0.0, B}, {A, 0.0, B}, {-A, 0.0, -B}, {A, 0.0, -B},
  {0.0, B, A}, {0.0, B, -A}, {0.0, -B, A}, {0.0, -B, -A},
  {B, A, 0.0}, {-B, A, 0.0}, {B, -A, 0.0}, {-B, -A, 0.0}
};

/* indices do triângulo (faces) */
static int tindices[20][3] = {
  {1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},
  {1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},
  {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
  {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7}
};

//define as propriedades de reflexão da superfície
GLfloat ks[] = {0.0, 0.0, 0.0, 1.0};
GLfloat kd[]  = {0.8, 0.6, 0.4, 1.0};
GLfloat ns = 100.0;

// define a posição e parâmetros da luz 0
GLfloat light_ambient[]  = {0.2, 0.2, 0.2, 1.0};
GLfloat light_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light_position[] = {-1.0, 1.1, 2.5, 1.0}; /* posição da fonte de luz local */

int flat = 1;			/* 0 = smooth shading, 1 = flat shading */
int subdiv = 0;			/* número de subdivisões */

/* normaliza um vetor */
void normalize(GLfloat v[3]){
  GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

  v[0] /= d; v[1] /= d; v[2] /= d;
}

/* produto vetorial dos vetores u e v (resultado em n)*/
void normCrossProd (GLfloat u[3], GLfloat v[3], GLfloat n[3]){
  n[0] = u[1]*v[2] - u[2]*v[1];
  n[1] = u[2]*v[0] - u[0]*v[2];
  n[2] = u[0]*v[1] - u[1]*v[0];
  normalize(n);
}

/* calcula a normal de uma face definida por três vértices */
void normFace(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]){
  GLfloat d1[3], d2[3], n[3];
  int k;
  for (k = 0; k < 3; k++) {
    d1[k] = v1[k] - v2[k];
    d2[k] = v2[k] - v3[k];
  }
  normCrossProd(d1, d2, n);
  glNormal3fv(n);
}

/* desenha um triangulo usando uma normal por face (triângulo) */
void drawTriangleFlat(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]){
  glBegin(GL_TRIANGLES);
    normFace(v1, v2, v3);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
  glEnd();
}

/* desenha um triangulo usando uma normal por vértice */
void drawTriangleSmooth(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]){
  glBegin(GL_TRIANGLES);
    glNormal3fv(v1);
    glVertex3fv(v1);
    glNormal3fv(v2);
    glVertex3fv(v2);
    glNormal3fv(v3);
    glVertex3fv(v3);
  glEnd();
}

/* recursivamente subdivide a face `depth' vezes */
/* e desenha os triângulos resultantes */
void subdivide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth){
  GLfloat v12[3], v23[3], v31[3];
  int i;

  if (depth == 0) {
    if (flat == 1)
      drawTriangleFlat(v1, v2, v3);
    else
      drawTriangleSmooth(v1, v2, v3);
    return;
  }

  /* calcula pontos do meio de cada lado */
  for (i = 0; i < 3; i++) {
    v12[i] = (v1[i]+v2[i])/2.0;
    v23[i] = (v2[i]+v3[i])/2.0;
    v31[i] = (v3[i]+v1[i])/2.0;
  }
  normalize(v12);
  normalize(v23);
  normalize(v31);

  /* recursivamente subdivide novos triângulos */
  subdivide(v1, v12, v31, depth-1);
  subdivide(v2, v23, v12, depth-1);
  subdivide(v3, v31, v23, depth-1);
  subdivide(v12, v23, v31, depth-1);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
  glMaterialf(GL_LIGHT0, GL_SHININESS, ns);

  for (int i = 0; i < 20; i++) {
    subdivide(&vdata[tindices[i][0]][0],
              &vdata[tindices[i][1]][0],
              &vdata[tindices[i][2]][0],
	          subdiv);
  }
  glFlush();
}

void init(){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  glShadeModel(GL_SMOOTH);	/* ativa smooth shading */
  glEnable(GL_LIGHTING);	/* ativa iluminação */
  glEnable(GL_LIGHT0);		/* ativa luz 0 */

  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.25, 1.25, -1.25 , 1.25, -2.0, 2.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 0.0,  /* posição */
            0.0, 0.0, -1.0, /* direção */
            0.0, 1.0, 0.0); /* orientação */
}

void keyboard(unsigned char key, int x, int y){
  if (key=='q' || key=='Q') exit(0);
  if (key=='+') subdiv++;
  if (key=='-') subdiv--;
  if (key=='f'|| key=='F') flat = 1;
  if (key=='s'|| key=='S') flat = 0;
  if (subdiv<0) subdiv = 0;

  glutPostRedisplay();
}

int main(int argc, char **argv){
  /* criar janela */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Exemplo 1 - Rendering de Superficies");

  /* funções callbacks */
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();

  glutMainLoop();
  return(0);
}

