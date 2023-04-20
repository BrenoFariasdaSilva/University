#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Create program that draws a big red wire_sphere and the wire_sphere follows the mouse movement with no need to click the mouse button.

void init(void);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

GLfloat angle = 0.0;
GLfloat angleX = 0.0;
GLfloat angleY = 0.0;
GLfloat xBegin = 0.0;
GLfloat yBegin = 0.0;
GLint moving, startx, starty;

int main(int argc, char** argv)
{
    glutInit(&argc,argv);                           //inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);    //configura o modo de display
    glutInitWindowPosition(200,0);                  //seta a posição inicial da janela
    glutInitWindowSize(500,500);                    //configura a largura e altura da janela de exibição
    glutCreateWindow("Rotação Esfera");                 //cria a janela de exibição
    init();       
    glutDisplayFunc(display);                       //registra a função de callback de exibição
    glutReshapeFunc(reshape);                       //registra a função de callback de redimensionamento
    glutMouseFunc(mouse);                           //registra a função de callback de mouse
    glutMotionFunc(motion);                         //registra a função de callback de movimento do mouse
    glutMainLoop();                                 //inicia o loop de eventos
    return 0;
}

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);                  //define a cor de fundo da janela de exibição
    glShadeModel(GL_FLAT);                          //define o modelo de sombreamento
    glEnable(GL_DEPTH_TEST);                        //habilita o teste de profundidade
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa a janela de exibição com a cor de fundo especificada
    glPushMatrix();                                     //empilha a matriz atual
    glRotatef(angle,1.0, 0.0,0.0);                   //rotaciona a cena em torno do eixo x e y
    glColor3f(1.0,0.0,0.0);                             //define a cor de desenho como vermelho
    glutWireSphere(1.0,20,16);                          //desenha uma esfera de raio 1.0
    glPopMatrix();                                      //desempilha a matriz atual
    glutSwapBuffers();                                  //troca os buffers de exibição
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);             //define a área de exibição
    glMatrixMode(GL_PROJECTION);                       //define a matriz de projeção atual
    glLoadIdentity();                                  //carrega a matriz identidade
    gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,20.0); //define a projeção perspectiva
    glMatrixMode(GL_MODELVIEW);                        //define a matriz de modelagem/vizualização atual
    glLoadIdentity();                                  //carrega a matriz identidade
    glTranslatef(0.0,0.0,-5.0);                        //translada a cena para frente
}

void mouse(int button, int state, int x, int y)
{
   // detect if the mouse is moving right or left 
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            xBegin = x;
            yBegin = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
    // detect if the mouse is moving up or down
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            xBegin = x;
            yBegin = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
    
}
 // detect moviment in the x and y axis
void motion(int x, int y)
{
    if (moving) {
        angle += (x - xBegin);
        angleY += (y - yBegin);
        xBegin = x;
        yBegin = y;
        glutPostRedisplay();
    }
}