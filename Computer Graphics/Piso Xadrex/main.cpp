#include <GL/gl.h>
#include <GL/glut.h>

int flat = 1;

void piso(){
    int i = 0;
    for (int z = -200; z < 200; z += 5){
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = -200; x < 200; x += 5){
            if (i % 2 == 0) glColor3f(0.0, 0.5, 0.5);
            else glColor3f(1.0, 1.0, 1.0);
            glVertex3f(x, 0.0, z - 5.0);
            glVertex3f(x, 0.0, z);
            i++;
        }
        glEnd();
        i++;
    }
}

void teclado(unsigned char key, int x, int y){
    if (key == 's' or key == 'S') flat = 0;
    if (key == 'f' or key == 'F') flat = 1;
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    if (flat == 1) glShadeModel(GL_FLAT);
    else glShadeModel(GL_SMOOTH);

    piso();
    glFlush();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 5.0, 30.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Piso xadrez");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMainLoop();
}

