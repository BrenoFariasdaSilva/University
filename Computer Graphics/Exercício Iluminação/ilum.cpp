#include <GL/glut.h>

void lighting() {
    float position[4] = {2.0f, 2.0f, 2.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position); // especifica qual luz será manipulada
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    //ativa a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

}

int init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matriz é a model view
    glLoadIdentity(); //carrega a matriz de identidade
    gluLookAt(0.0, 0.0, 1.0, //posição da câmera
    0.0, 0.0, 0.0, //para onde a câmera aponta
    0.0, 1.0, 0.0); //vetor view-up
    glMatrixMode(GL_PROJECTION); //define que a matriz é a de projeção
    glLoadIdentity(); //carrega a matriz de identidade
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    lighting();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glutSolidSphere(1.5, 40, 40);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,0);
    glutInitWindowSize(400,400);
    glutCreateWindow("Exemplo 1 - Definindo as Cores da Fonte de Luz");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}