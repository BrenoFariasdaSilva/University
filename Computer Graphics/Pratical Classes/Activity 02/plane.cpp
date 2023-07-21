#include <GL/glut.h>

bool keystates[256];
float xrot = 0.0f;
float zrot = 0.0f;

float xpos = 0.0f;
float ypos = 0.0f;

void desenhaTerreno(){
    float L = 500.0;
    float incr = 1.0;
    float y = -0.5;

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (float i = -L; i <= L; i += incr){
        glVertex3f(i, y, -L);
        glVertex3f(i, y, L);

        glVertex3f(-L, y, i);
        glVertex3f(L, y, i);
    }
    glEnd();
}

void fan(){
    glColor3d(0.5,1,0);
    glPushMatrix();
        glTranslated(0,0,0);
        glScaled(1,1,0.7);
        glutSolidSphere(0.8,30,30);
    glPopMatrix();

    glColor3d(0.5,1,0);
    glPushMatrix();
        glTranslated(0,0,0);
        glRotated(5,0,1,0);
        glScaled(0.5,2.5,0.05);
        glutSolidSphere(1,30,30);
    glPopMatrix();

    glColor3d(0.5,1,0);
    glPushMatrix();
        glTranslated(0,0,0);
        glRotated(-5,0,1,0);
        glRotated(90,0,0,1);
        glScaled(0.5,2.5,0.05);
        glutSolidSphere(1,30,30);
    glPopMatrix();

}

void plane(){
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;

    /// Main body
    glColor3d(0.5,1,0);
    glPushMatrix();
        glTranslated(0,0,0);
        glScaled(3,0.4,0.5);
        glutSolidSphere(1,30,30);
    glPopMatrix();

    glColor3d(0,0,0);
    glPushMatrix();
        glTranslated(1.7,0.1,0);
        glScaled(1.5,0.7,0.8);
        glRotated(40,0,1,0);
        glutSolidSphere(0.45,30,30);
    glPopMatrix();

    ///Right
    glColor3d(0.8,1,0);
    glPushMatrix();
        glTranslated(0,0,1.2);
        glRotated(-50,0,1,0);
        glScaled(0.7,0.1,3);
        glRotated(25,0,1,0);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.8,1,0);
    glPushMatrix();
        glTranslated(-0.3,-0.15,1.5);
        glRotated(90,0,1,0);
        glScaled(0.1,0.1,0.9);
        glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    glColor3d(0.8,1,0);
    glPushMatrix();
        glTranslated(0.2,-0.15,0.9);
        glRotated(90,0,1,0);

        /// FAN
//        glPushMatrix();
//            glTranslated(0,0,0.5);
//            glRotated(10*a,0,0,1);
//            glScaled(0.1,0.1,0.1);
//            fan();
//        glPopMatrix();

        glScaled(0.1,0.1,0.9);
        glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    ///Left
    glColor3d(0.8,1,0);
    glPushMatrix();
        glTranslated(0,0,-1.2);
        glRotated(50,0,1,0);
        glScaled(0.7,0.1,3);
        glRotated(-25,0,1,0);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.8,1,0);
    glPushMatrix();
        glTranslated(-0.3,-0.15,-1.5);
        glRotated(90,0,1,0);
        glScaled(0.1,0.1,0.9);
        glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    glColor3d(0.8,1,0);
    glPushMatrix();
        glTranslated(0.2,-0.15,-0.9);
        glRotated(90,0,1,0);
        glScaled(0.1,0.1,0.9);
        glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.8,0,0);
        glScaled(0.8,0.5,0.3);

        ///Right
        glColor3d(0.8,1,0);
        glPushMatrix();
            glTranslated(0.4,0,1.5);
            glRotated(-30,0,1,0);
            glScaled(0.7,0.1,3);
            glRotated(10,0,1,0);
            glutSolidCube(1);
        glPopMatrix();

        ///left
        glColor3d(0.8,1,0);
        glPushMatrix();
            glTranslated(0.4,0,-1.5);
            glRotated(30,0,1,0);
            glScaled(0.7,0.1,3);
            glRotated(-10,0,1,0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();


    glColor3d(0.8,1,0);
    glPushMatrix();
        glTranslated(-2.7,0.5,0);
        glRotated(45,0,0,1);
        glScaled(0.8,2,0.1);
        glRotated(-20,0,0,1);
        glutSolidCube(0.5);
    glPopMatrix();

//    glColor3d(0.8,1,0);
//    glPushMatrix();
//        glTranslated(-2.95,0.85,0);
//        glRotated(90,0,1,0);
//        glScaled(0.05,0.05,0.6);
//        glutSolidTorus(0.5,0.5,50,50);
//    glPopMatrix();

    ///FANS

//    glPushMatrix();
//        glTranslated(0,0,0);
//        glRotated(10*a,0,0,1);
//        //glRotated(90,1,0,0);
//        fan();
//    glPopMatrix();
}

void teclado(unsigned char key, int x, int y){
    // D - frente
    if(key == 'd'){
        xpos += 0.1;
    }

    // A - trás
    if(key == 'a'){
        xpos -= 0.1;
    }

    // W - cima
    if(key == 'w'){
        ypos += 0.1;
    }

    // S - baixo
    if(key == 's'){
        ypos -= 0.1;
    }
}


// void tecladoUp(unsigned char key, int x, int y){
//     keystates[key] = true;
// }


void tecladoSpecial(int key, int x, int y){
    // define no vetor 'keystates' que a tecla está pressionada
    keystates[key] = true;
    
}

void tecladoSpecialUp(int key, int x, int y){
    // define no vetor 'keystates' que a tecla não está mais pressionada
    keystates[key] = false;
}

void loop(){
    // verifica as teclas que estão pressionadas e realiza as operações
    if(keystates[GLUT_KEY_UP]){
        xrot += 0.5;
    }
    if(keystates[GLUT_KEY_DOWN]){
        xrot -= 0.5;
    }
    if(keystates[GLUT_KEY_LEFT]){
        zrot += 0.5;
    }
    if(keystates[GLUT_KEY_RIGHT]){
        zrot -= 0.5;
    }

    glutPostRedisplay();
}

int init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
}

void display(){
    //limpa o buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(  xpos, ypos, 10.0,     //posição da câmera
                xpos, ypos, 0.0,     //para onde a câmera aponta
                0.0, 1.0, 0.0   );    //vetor viewup

    desenhaTerreno();

    glPushMatrix();
        glRotated(xrot,1,0,0);
        glRotated(zrot,0,0,1);
        // Move
        glTranslated(xpos,ypos,0);
        plane();
    glPopMatrix();

    //força o desenho das primitivas
    glutSwapBuffers();
}

// função que redimensiona a viewport quando a janela é redimensionada
void reshape (int w, int h){
   const float ar = (float) w / (float) h;
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   // define a matriz de projeção. Essa matriz SEMPRE deve vir antes
   // da definição da matriz de transformação (modelview)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   // define que a projeção será utilizando Frustum
   glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(xpos, ypos, 10.0,     //posição da câmera
             0.0, 0.0, 0.0,     //para onde a câmera aponta
             0.0, 1.0, 0.0);    //vetor viewup
}

int main(int argc, char** argv){
    glutInit(&argc,argv);                           //inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);    //configura o modo de display
    glutInitWindowPosition(200,0);                  //seta a posição inicial da janela
    glutInitWindowSize(800,800);                    //configura a largura e altura da janela de exibição
    glutCreateWindow("AP2 - Boneco 3D");                 //cria a janela de exibição

    init();                                         //executa função de inicialização
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutIgnoreKeyRepeat(1);
    //glutKeyboardUpFunc(tecladoUp);
    glutSpecialFunc(tecladoSpecial);
    glutSpecialUpFunc(tecladoSpecialUp);
    glutIdleFunc(loop);

    glutMainLoop();                                  //mostre tudo e espere
    return 0;
}
