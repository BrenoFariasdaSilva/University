#include <GL/gl.h>
#include <GL/glut.h>

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES); // Sentido anti-horário (frente)
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES); // Sentido horário (trás)
        glVertex3f(-1.0, 0.0, -1.0);
        glVertex3f(-2.0, -2.0, -1.0);
        glVertex3f(0.0, -2.0, -1.0);
    glEnd();
    glFlush();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutCreateWindow("BackFace Culling");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}