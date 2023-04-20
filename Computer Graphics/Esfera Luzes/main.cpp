#include <GL/gl.h>
#include <GL/glut.h>

const int width = 300, height = 300;

void lightning(){
    glEnable(GL_LIGHTING);
    GLfloat ambienteGlobal[] = {0.2, 0.2, 0.2, 0.0,};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambienteGlobal);

    GLfloat light0_ambiente[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light0_diffuse_spec[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_position[] = {0.0, -3.0, 0.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse_spec);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_diffuse_spec);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_LIGHT0);

    glPushMatrix();
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(0.0, -3.0, 0.0);
        glutSolidSphere(0.5, 10, 10);
        glEnable(GL_LIGHTING);
    glPopMatrix();


    GLfloat material_ambiente_diffuse[] = {0.0, 0.0, 1.0, 1.0}; // Efeito de quando a luz se espalha pela superfície
    GLfloat material_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat material_shininess = 60.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_ambiente_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
}

void reshape(int width, int height) {
    GLfloat aspect = (GLfloat) width / (GLfloat) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, -3.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );
    glutSolidSphere(1.0, 30, 30);
    glutSwapBuffers();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    lightning();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(width, height);
    glutCreateWindow("Esfera Luzes");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}