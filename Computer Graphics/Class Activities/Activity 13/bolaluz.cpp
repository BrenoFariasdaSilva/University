#include <GL/gl.h>
#include <GL/glut.h>

int width = 640;
int height = 480;

void lighting(){
    glEnable(GL_LIGHTING);

    GLfloat ambGlobal[] = {0.2, 0.2, 0.2, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambGlobal);

    // Luz azul
    GLfloat light0_amb[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diff_spec[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_pos[] = {0.0, -3.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff_spec);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_diff_spec);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glEnable(GL_LIGHT0);
    
    glPushMatrix();
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 1.0);    
        glTranslated(0.0, -3.0, 0.0);
        glutSolidSphere(0.1, 10, 10);
        glEnable(GL_LIGHTING);
    glPopMatrix();

    GLfloat material_amb_diff[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat material_spec[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess = 60.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


    
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        0.0 , 0.0 , -3.0 , // eye
        0.0 , 0.0 , -1.0 , // center
        0.0 , 1.0 , 0.0 // up
    );

    glutSolidSphere(1.0, 30, 30);
    glutSwapBuffers();

}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);   // Cor do fundo
    lighting();

}

void reshape(int w, int h){
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(width, height);
    glutCreateWindow("Esfera luzes!");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}