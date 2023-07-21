#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#define TAM_CUBO 1.0f
#define TAM_SALA 4.0f
#define TAM_PAREDE 0.05f

int width = 800, height = 800;
int x_ini = 0, y_ini = 0, anguloX = 0, anguloY = 0, anguloX_ini = 0, anguloY_ini = 0;

void sala(){
    glColor3f(1.0, 0.0, 0.0);
    // teto
    glPushMatrix();
        glTranslatef(0, TAM_SALA/2, 0);
        glScalef(TAM_SALA, TAM_PAREDE, TAM_SALA);
        glutSolidCube(TAM_CUBO);
    glPopMatrix();

    // piso
    glPushMatrix();
        glTranslatef(0, -TAM_SALA/2, 0);
        glScalef(TAM_SALA, TAM_PAREDE, TAM_SALA);
        glutSolidCube(TAM_CUBO);
    glPopMatrix();

    // parede esquerda
    glPushMatrix();
        glTranslatef(-TAM_SALA/2, 0, 0);
        glScalef(TAM_PAREDE, TAM_SALA, TAM_SALA);
        glutSolidCube(TAM_CUBO);
    glPopMatrix();

    // parede direita
    glPushMatrix();
        glTranslatef(TAM_SALA/2, 0, 0);
        glScalef(TAM_PAREDE, TAM_SALA, TAM_SALA);
        glutSolidCube(TAM_CUBO);
    glPopMatrix();

    // parede fundo
    glPushMatrix();
        glTranslatef(0, 0, -TAM_SALA/2);
        glScalef(TAM_SALA, TAM_SALA, TAM_PAREDE);
        glutSolidCube(TAM_CUBO);
    glPopMatrix();

    // Quadrado no meio da sala
    glPushMatrix();
        glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);
            glVertex3f(-1, -1, 0);
            glVertex3f(1, -1, 0);
            glVertex3f(1, 1, 0);
            glVertex3f(-1, 1, 0);
        glEnd();
    glPopMatrix();
             

}

void lampada(){
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
        glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
}



void materialSala(){

    GLfloat material[3][4] = {
        {0.0, 0.0, 0.0, 1.0}, // ambiente
        {1.0, 0.5, 0.0, 1.0}, // difusa
        {1.0, 0.5, 0.0, 1.0} // especular
    };

    GLint shininess = 128;

    glMaterialfv(GL_FRONT, GL_AMBIENT, &material[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &material[2][0]);
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

}

void materialLamp(){

    GLfloat material[3][4] = {
        {0.0, 0.0, 0.0, 1.0}, // ambiente
        {0.0, 0.0, 1.0, 1.0}, // difusa
        {0.0, 0.0, 1.0, 1.0} // especular
    };

    GLint shininess = 128;

    glMaterialfv(GL_FRONT, GL_AMBIENT, &material[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &material[2][0]);
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

}

void cenario(){
    glRotatef(anguloX, 0, 1, 0);
    glRotatef(anguloY, 1, 0, 0);

    glPushMatrix();
        materialSala();
        sala();
    glPopMatrix();

    glPushMatrix();
        materialLamp();
        lampada();
    glPopMatrix();
}

void iluminacao(){
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    GLfloat light1[4][4] = {
        {0.0, 0.0, 0.0, 1.0}, // ambiente
        {1.0, 1.0, 1.0, 1.0}, // difusa
        {1.0, 1.0, 1.0, 1.0}, // especular
        {0.0, 0.0, 0.0, 1.0}
    };

    

    glLightfv(GL_LIGHT1, GL_AMBIENT, &light1[0][0]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, &light1[1][0]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, &light1[2][0]);
    glLightfv(GL_LIGHT1, GL_POSITION, &light1[3][0]);
    glEnable(GL_LIGHT1);

    
}

void mouse(int button, int state, int x, int y){
    x_ini = x;
    y_ini = y;
    anguloX_ini = anguloX;
    anguloY_ini = anguloY;
}

void mouseMov(int x, int y){
    int deltaX = x - x_ini;
    int deltaY = y - y_ini;

    anguloX = anguloX_ini + deltaX;
    anguloY = anguloY_ini + deltaY;
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, 10.0, // Posicao da camera
        0.0, 0.0, 0.0,  // Foco
        0.0, 1.0, 0.0   // Orientacao
    );
    cenario();
    glutSwapBuffers();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    iluminacao();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("Iluminacao 3D");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMov);
    init();
    glutMainLoop();
}
