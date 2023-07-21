#include <GL/glut.h>
#include <iostream>

GLfloat angBracoEsqZ = 0;
GLfloat angBracoEsqX = 0;


GLfloat angAntebracoEsqZ = 0;
GLfloat angAntebracoEsqX = 0;


GLfloat angBracoDirZ = 0;
GLfloat angBracoDirX= 0;


GLfloat angAntebracoDirZ = 0;
GLfloat angAntebracoDirX = 0;

GLfloat angPernaEsqZ = 0;
GLfloat angPernaEsqX = 0;

GLfloat angCanelaEsqZ = 0;
GLfloat angCanelaEsqX = 0;

GLfloat angPernaDirZ = 0;
GLfloat angPernaDirX = 0;

GLfloat angCanelaDirZ = 0;
GLfloat angCanelaDirX = 0;

GLfloat angCabecaZ = 0;
GLfloat angCabecaX = 0;

bool keystates[256];

enum {
    CABECA = 0,
    BRACO_ESQ = 1,
    ANTEBRACO_ESQ = 2,
    BRACO_DIR = 3,
    ANTEBRACO_DIR = 4,
    PERNA_DIR = 5,
    CANELA_DIR = 6,
    PERNA_ESQ = 7,
    CANELA_ESQ = 8,
};

int escolha = 0;

void cabeca(){
    //glColor3f(1.0, 0.0, 0.0);
    glutWireSphere(0.5, 20, 20);
}

void tronco(){
    //glColor3f(1.0, 0.0, 0.0);
    glutWireCone(1.0, 1.6, 30, 30);
}

void ombro(){
    glPushMatrix();
        //glColor3f(1.0, 0.0, 0.0);
        glScalef(0.4, 1.0, 0.5);
        glutWireSphere(0.5, 10, 10);
    glPopMatrix();
}

void antebraco(){
    glPushMatrix();
        //glColor3f(1.0, 0.0, 0.0);
        glScalef(0.3, 1.2, 0.5);
        glutWireSphere(0.5, 10, 10);
    glPopMatrix();
}

void mao(){
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(0.3, 0.4, 0.4);
        glutWireCube(1.0);
    glPopMatrix();
}

void quadril(){
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(1.2, 0.7, 0.8);
        glutWireCube(1.0);
    glPopMatrix();
}

void coxa() {
    glPushMatrix();
        //glColor3f(1.0, 0.0, 0.0);
        glScalef(0.5, 1.3, 0.5);
        glutWireSphere(0.5, 10, 10);
    glPopMatrix();
}

void canela() {
    glPushMatrix();
        //glColor3f(1.0, 0.0, 0.0);
        glScalef(0.4, 1.3, 0.5);
        glutWireSphere(0.5, 10, 10);
    glPopMatrix();
}

void pe(){
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(0.4, 0.3, 0.8);
        glutWireCube(1.0);
    glPopMatrix();
}

void boneco(){
    glPushMatrix();
        glTranslatef(0, 0.1, 0);
        glTranslatef(0.0, -0.3, 0.0);
        glRotatef(-angCabecaZ, 0, 0, 1);
        glRotatef(-angCabecaX, 1, 0, 0);
        glTranslatef(0.0, 0.3, 0.0);
        glColor3f(1.0, 0.0, 0.0);
        if (escolha == CABECA ) {
            glColor3f(0.0, 0.0, 1.0);
        }
        cabeca();
    glPopMatrix();
    // Cria o tronco
    glPushMatrix();
        glScalef(1.0, 1.0, 0.7);
        glTranslatef(0.0, -0.5, 0.0);
        glRotatef(90, 1, 0, 0);
        glColor3f(1.0, 0.0, 0.0);
        tronco();
    glPopMatrix();

    // Cria o braço esquerdo composto pelo ombro e pela mão
    glPushMatrix();
        glTranslatef(-0.88, -1.0, 0.0);
        glTranslatef(0.0, 0.5, 0.0);
        glRotatef(angBracoEsqZ, 0, 0, 1);
        glRotatef(angBracoEsqX, 1, 0, 0);
        glTranslatef(0.0, -0.5, 0.0);
        glColor3f(1.0, 0.0, 0.0);
        if (escolha == BRACO_ESQ ) {
            glColor3f(0.0, 0.0, 1.0);
        }
        ombro();
        glPushMatrix();
            glTranslatef(0, -0.88, 0.0);
            if (escolha == ANTEBRACO_ESQ) {
                glColor3f(0.0, 0.0, 1.0);
                // Rotacionar o antebraço em relação ao ponto 0,0,0
            }
            glTranslatef(0.0, 0.5, 0.0);
            glRotatef(angAntebracoEsqZ, 0, 0, 1);
            glRotatef(angAntebracoEsqX, 1, 0, 0);
            glTranslatef(0.0, -0.5, 0.0);
            antebraco();
            glPushMatrix();
                glTranslatef(0, -0.5, 0.0);
                mao();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    // Cria o braço direito composto pelo ombro e pela mão
    glPushMatrix();
        glTranslatef(0.88, -1.0, 0.0);
        glTranslatef(0.0, 0.5, 0.0);
        glRotatef(angBracoDirZ, 0, 0, 1);
        glRotatef(angBracoDirX, 1, 0, 0);
        glTranslatef(0.0, -0.5, 0.0);
        if (escolha == BRACO_DIR ) {
            glColor3f(0.0, 0.0, 1.0);
        }
        ombro();
        glPushMatrix();
            glTranslatef(0, -0.88, 0.0);
            if (escolha == ANTEBRACO_DIR) {
                glColor3f(0.0, 0.0, 1.0);
                
            }
            glTranslatef(0.0, 0.5, 0.0);
            glRotatef(angAntebracoDirZ, 0, 0, 1);
            glRotatef(angAntebracoDirX, 1, 0, 0);
            glTranslatef(0.0, -0.5, 0.0);

            antebraco();
            glPushMatrix();
                glTranslatef(0, -0.5, 0.0);
                mao();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    // Cria o quadril
    glPushMatrix();
        glTranslatef(0.0, -2.0, 0.0);
        quadril();
    glPopMatrix();

    // Cria a perna esquerda, composta pela coxa, canela e pé
    glPushMatrix();
        glTranslatef(-0.5, -2.8, 0.0);
        glTranslatef(0.0, 0.5, 0.0);
        glRotatef(angPernaEsqZ, 0, 0, 1);
        glRotatef(angPernaEsqX, 1, 0, 0);
        glTranslatef(0.0, -0.5, 0.0);
        if (escolha == PERNA_ESQ ) {
            glColor3f(0.0, 0.0, 1.0);
        }
        coxa();
        glPushMatrix();
            glTranslatef(0, -1.0, 0.0);
            if (escolha == CANELA_ESQ) {
                glColor3f(0.0, 0.0, 1.0);
            }
            glTranslatef(0.0, 0.5, 0.0);
            glRotatef(angCanelaEsqZ, 0, 0, 1);
            glRotatef(angCanelaEsqX, 1, 0, 0);
            glTranslatef(0.0, -0.5, 0.0);
                
            canela();
            glPushMatrix();
                glTranslatef(0, -0.7, 0.2);
                pe();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    // Cria a perna direita, composta pela coxa, canela e pé
    glPushMatrix();
        glTranslatef(0.5, -2.8, 0.0);
        glTranslatef(0.0, 0.5, 0.0);
        glRotatef(angPernaDirZ, 0, 0, 1);
        glRotatef(angPernaDirX, 1, 0, 0);
        glTranslatef(0.0, -0.5, 0.0);
        if (escolha == PERNA_DIR ) {
            glColor3f(0.0, 0.0, 1.0);
        }
        coxa();
        glPushMatrix();
            glTranslatef(0, -1.0, 0.0);
            if (escolha == CANELA_DIR) {
                glColor3f(0.0, 0.0, 1.0);
                
            }
            glTranslatef(0.0, 0.5, 0.0);
            glRotatef(angCanelaDirZ, 0, 0, 1);
            glRotatef(angCanelaDirX, 1, 0, 0);
            glTranslatef(0.0, -0.5, 0.0);
            canela();
            glPushMatrix();
                glTranslatef(0, -0.7, 0.2);
                pe();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void teclado(unsigned char key, int x, int y){
    // Verifica a tecla pressionada e faz algo
    // Se for a recla E, troca de membro
    if (key == 'e' || key == 'E'){
        escolha = (escolha + 1) % 9;
    }
}

/*
void tecladoUp(unsigned char key, int x, int y){
    //
}
*/

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
    if (escolha == BRACO_ESQ){
        if (keystates[GLUT_KEY_RIGHT]){
            angBracoEsqZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angBracoEsqZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angBracoEsqX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angBracoEsqX -= 1;
        }
    }

    if (escolha == BRACO_DIR){
        if (keystates[GLUT_KEY_RIGHT]){
            angBracoDirZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angBracoDirZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angBracoDirX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angBracoDirX -= 1;
        }
    }

    if (escolha == ANTEBRACO_ESQ){
        if (keystates[GLUT_KEY_RIGHT]){
            angAntebracoEsqZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angAntebracoEsqZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angAntebracoEsqX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angAntebracoEsqX -= 1;
        }
    }

    if (escolha == ANTEBRACO_DIR){
        if (keystates[GLUT_KEY_RIGHT]){
            angAntebracoDirZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angAntebracoDirZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angAntebracoDirX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angAntebracoDirX -= 1;
        }
    }

    if (escolha == PERNA_ESQ){
        if (keystates[GLUT_KEY_RIGHT]){
            angPernaEsqZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angPernaEsqZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angPernaEsqX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angPernaEsqX -= 1;
        }
    }

    if (escolha == PERNA_DIR){
        if (keystates[GLUT_KEY_RIGHT]){
            angPernaDirZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angPernaDirZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angPernaDirX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angPernaDirX -= 1;
        }
    }

    if (escolha == CANELA_ESQ){
        if (keystates[GLUT_KEY_RIGHT]){
            angCanelaEsqZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angCanelaEsqZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angCanelaEsqX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angCanelaEsqX -= 1;
        }
    }

    if (escolha == CANELA_DIR){
        if (keystates[GLUT_KEY_RIGHT]){
            angCanelaDirZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angCanelaDirZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angCanelaDirX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angCanelaDirX -= 1;
        }
    }

    if (escolha == CABECA){
        if (keystates[GLUT_KEY_RIGHT]){
            angCabecaZ += 1;
        }
        if (keystates[GLUT_KEY_LEFT]){
            angCabecaZ -= 1;
        }
        if (keystates[GLUT_KEY_UP]){
            angCabecaX += 1;
        }
        if (keystates[GLUT_KEY_DOWN]){
            angCabecaX -= 1;
        }
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

    glPushMatrix();
        // Movimenta para alinhar ao centro da tela
        glTranslatef(0, 2, 0);
        // Desenha o boneco na tela
        boneco();
    glPopMatrix();

    //força o desenho das primitivas
    glutSwapBuffers();
}

// função que redimensiona a viewport quando a janela é redimensionada
void reshape (int w, int h){
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   // define a matriz de projeção. Essa matriz SEMPRE deve vir antes
   // da definição da matriz de transformação (modelview)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   // define que a projeção será perspectiva
   gluPerspective(70.0, (GLfloat) w/(GLfloat) h, 0.1, 50.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0.0, 0.0, 7.0,     //posição da câmera
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

