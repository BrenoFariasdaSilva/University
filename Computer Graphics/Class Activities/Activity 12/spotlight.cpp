#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

int width = 500;
int height = 500;

GLfloat movZ = 0.0f;
GLfloat movX = 0.0f;

GLfloat raio = 3.0;
GLfloat spotAngle = 10.0;

void iluminacao(){
    glEnable(GL_LIGHTING); // Habilita o uso de iluminação
    GLfloat ambGlobal[] = {0.2, 0.2, 0.2, 0.0}; 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambGlobal);    // Define a cor ambiente da cena
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);  // Habilita o calculo da iluminação considerando a posição do observador

    GLfloat bolas[3][4] = {
        {0.0, 0.0, 0.0, 1.0},
        {1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0}
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, &bolas[0][0]); // Define a cor ambiente do material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &bolas[1][0]); // Define a cor difusa do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, &bolas[2][0]); // Define a cor especular do material
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0); // Define a concentração do brilho

    glEnable(GL_COLOR_MATERIAL); // Habilita o uso da cor do material como cor do objeto
}

void desenha(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            glPushMatrix();
                glTranslatef(-4 + i, 0.0, -4 + j);
                if((i+j) % 3 == 0){
                    glColor3f(1.0, 0.0, 0.0);
                } else if((i+j) % 3 == 1){
                    glColor3f(0.0, 1.0, 0.0);
                } else {
                    glColor3f(0.0, 0.0, 1.0);
                }
                glutSolidSphere(0.5, 30, 30);
            glPopMatrix();
        }
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    GLfloat ratio = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, ratio, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void tecladoEsp(int key, int x, int y){
    if(key == GLUT_KEY_PAGE_DOWN){
        spotAngle -= 1.0;
    }
    
    if(key == GLUT_KEY_PAGE_UP){
        spotAngle += 1.0;
    }

    if(key == GLUT_KEY_UP){
        movZ -= 0.1;
    }

    if(key == GLUT_KEY_DOWN){
        movZ += 0.1;
    }

    if(key == GLUT_KEY_LEFT){
        movX -= 0.1;
    }

    if(key == GLUT_KEY_RIGHT){
        movX += 0.1;
    }
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        0.0, 5.0, 4.0,  // Onde a câmera está
        0.0, 0.0, 0.0,  // Para onde a câmera está olhando
        0.0, 1.0, 0.0   // Vetor Up
    );
    glPushMatrix();
        glTranslatef(movX, 0.0, movZ);
        glPushMatrix();
            glDisable(GL_LIGHTING);
            glColor3f(1.0, 1.0, 1.0);
            glRotatef(-90, 1.0, 0.0, 0.0);
            glutWireCone(raio * tan(spotAngle / 180 * M_PI), 3.0, 30, 30);
            glEnable(GL_LIGHTING);
        glPopMatrix();

        GLfloat spotDir[] = {0.0, -1.0, 0.0};
        GLfloat spotExp = 3.0;
        GLfloat spotPos[] = {0.0, 3.0, 0.0, 1.0};

        // GLfloat light0[3][4] = {
        //     {0.0, 0.0, 0.0, 1.0},
        //     {1.0, 1.0, 1.0, 1.0},
        //     {1.0, 1.0, 1.0, 1.0}
        // };
        // glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]); // Define a cor ambiente da luz
        // glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]); // Define a cor difusa da luz
        // glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]); // Define a cor especular da luz

        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);          // Define o angulo de abertura do feixe de luz
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);   // Define a direção do feixe de luz
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExp);     // Define a concentração do feixe de luz
        glLightfv(GL_LIGHT0, GL_POSITION, spotPos);        // Define a posição da luz
        glEnable(GL_LIGHT0);                                // Habilita a luz 0
    glPopMatrix();

    desenha();

    glutSwapBuffers();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    iluminacao();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("SpotLight");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(tecladoEsp);
    glutMainLoop();
    return 0;
}