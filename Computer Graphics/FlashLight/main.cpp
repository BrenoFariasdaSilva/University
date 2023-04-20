#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLfloat raio = 3.0;
GLfloat spotAngle = 10.0;
const int width = 400;
const int height = 400;
int moveX = 0;
int moveZ = 0;

void ilumination() {
    glEnable(GL_LIGHTING); // Habilitar as luzes
    GLfloat ambienteGlobal[] = {0.2, 0.2, 0.2, 0.0}; // Canal RGB e o último é a distância da luz. Seria como a luz do sol.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambienteGlobal);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    GLfloat ballsLightning[3][4] = {
        {0.0, 0.0, 0.0, 1.0}, // Ambiente
        {1.0, 1.0, 1.0, 1.0}, // Difusa
        {1.0, 1.0, 1.0, 1.0}  // Especular
    };

    glMaterialfv(GL_FRONT, GL_AMBIENT, &ballsLightning[0][0]); //  Configuração das luzes do material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &ballsLightning[1][0]); //  Configuração das luzes do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, &ballsLightning[2][0]); //  Configuração das luzes do material
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0); //  Configuração das luzes do material
    
    // glEnable(GL_LIGHT0); // Luz ambiente.
    glEnable(GL_COLOR_MATERIAL);

}

void draw(){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            glPushMatrix();
                glTranslatef(-4 + i, 0.0, -4 + j);
                if ((i + j) % 3 == 0)
                    glColor3f(1.0, 0.0, 0.0);
                else if ((i + j) % 3 == 1)
                    glColor3f(0.0, 1.0, 0.0);
                else 
                    glColor3f(0.0, 0.0, 1.0);

                glutSolidSphere(0.5, 30, 30);
            glPopMatrix();
        }
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    GLfloat ratio = (GLfloat) width / (GLfloat) height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Sempre que usar uma perspectiva, usar o loadIdentity antes
    gluPerspective(60, ratio, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void specialKeyboard(int key, int x, int y){
    if (key == GLUT_KEY_PAGE_DOWN)
        spotAngle -= 0.5;
    if (key == GLUT_KEY_PAGE_UP)
        spotAngle += 0.5;
    if (key == GLUT_KEY_UP)
        moveZ--;
    if (key == GLUT_KEY_DOWN)
        moveZ++;
    if (key == GLUT_KEY_LEFT)
        moveX++;
    if (key == GLUT_KEY_RIGHT)
        moveX--;
        
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
        0.0, 5.0, 4.0,
        0.0, 0.0, 0.0, 
        0.0, 1.0, 0.0
    );
    glPushMatrix();
        glTranslatef(moveX, 0.0, moveZ);

        glPushMatrix();
            glDisable(GL_LIGHTING);
            glColor3f(1.0, 1.0, 1.0);
            glRotatef(-90.0, 1, 0, 0);
            glutWireCone(raio * tan(spotAngle / 180 * M_PI), 3.0, 30, 30);
            glEnable(GL_LIGHTING);
        glPopMatrix();

        GLfloat spotDirection[] = {0.0, -1.0, 0.0};
        GLfloat spotExponent = 3.0; // Quanto menor o valor, mais intenso é.
        GLfloat spotPosition[] = {0.0, 3.0, 0.0, 1.0};

        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
        glLightfv(GL_LIGHT0, GL_POSITION, spotPosition);
        glEnable(GL_LIGHT0);
    glPopMatrix();
    draw();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST); // Testar a profundidade das superficies ocultas.
    ilumination();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("Spotlight");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeyboard);
    init();
    glutMainLoop();
}