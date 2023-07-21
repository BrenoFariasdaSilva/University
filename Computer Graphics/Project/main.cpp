// ############################## PROJETO ILHAS DE FERRO ##############################
// # Autor 1: Breno Farias da Silva
// # Autor 2: Felipe Archanjo da Cunha Mendes

// ############################## TUTORIAL ##############################
// # TECLA "e": Liga e desliga o navio
// # TECLA "w": Move o navio para o norte
// # TECLA "s": Move o navio para o sul
// # TECLA "a": Move o navio para o oeste
// # TECLA "d": Move o navio para o leste
// # TECLA "1": Altera para a camera 1 (visão geral)
// # TECLA "2": Altera para a camera 2 (visao de cima)
// # TECLA "3": Altera para a camera 3 (visao do navio)

// -> Tópicos:
//  -> Desenho
//  -> Movimentação
//  -> Iluminação
//  -> Colisão -> Matrix
// -> Remoção Superfícies Ocultas:
    // glEnable(GL_DEPTH_TEST) no init
    // glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH) no main
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) no display
//  -> Label

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

int width = 800, height = 800;
int x_ini = 0, y_ini = 0, anguloX = 0, anguloY = 0, anguloX_ini = 0, anguloY_ini = 0;

// Variaveis do barco
GLfloat x_pos_barco = 0.0;
GLfloat y_pos_barco = 0.0;
GLfloat z_pos_barco = 120.0;
GLfloat barcoAngle = 0.0;

bool barcoLigado = false;

// Variaveis de camera
int camera = 0;

bool cameraNoBarco = false;

GLfloat x_pos_cam = 0.0;
GLfloat y_pos_cam = 500.0;
GLfloat z_pos_cam = 700.0;

// -> LookAt da câmera geral
GLfloat x_look_cam = 0.0;
GLfloat y_look_cam = 0.0;
GLfloat z_look_cam = 0;

// -> Geral
GLfloat x_pos_cam_1 = 0.0;
GLfloat y_pos_cam_1 = 200.0;
GLfloat z_pos_cam_1 = 500.0;

// -> Navio
GLfloat x_pos_cam_2 = 0.0;
GLfloat y_pos_cam_2 = 1200.0;
GLfloat z_pos_cam_2 = 1.0;

// -> Castelo
GLfloat x_pos_cam_3 = x_pos_barco;
GLfloat y_pos_cam_3 = y_pos_barco + 100.0;
GLfloat z_pos_cam_3 = z_pos_barco + 100.0;
GLfloat x_look_cam_3 = x_pos_barco;
GLfloat y_look_cam_3 = y_pos_barco;
GLfloat z_look_cam_3 = z_pos_barco;

// -> Ilha
GLfloat x_pos_cam_4 = 0;
GLfloat y_pos_cam_4 = 180;
GLfloat z_pos_cam_4 = 90;

// -> Floresta
GLfloat x_pos_cam_5 = -300;
GLfloat y_pos_cam_5 = 300;
GLfloat z_pos_cam_5 = -100;

// -> Dragão
GLfloat x_pos_cam_6 = -300;
GLfloat y_pos_cam_6 = 1000;
GLfloat z_pos_cam_6 = -400;

// Variaveis de luz do sol
GLfloat xLuz_sun = 0.0;
GLfloat yLuz_sun = 200.0;
GLfloat zLuz_sun = 200.0;

GLfloat anguloLuz = 0.0;
GLfloat raio = 2000.0;
GLfloat luzR = 1.0;
GLfloat luzG = 1.0;
GLfloat luzB = 1.0;

// Variaveis da ilha
GLfloat x_pos_ilha = -300.0;
GLfloat y_pos_ilha = 0.0;
GLfloat z_pos_ilha = -500.0;

// Variaveis para o dragao
GLfloat x_pos_dragao = 100.0;
GLfloat y_pos_dragao = 70.0;
GLfloat z_pos_dragao = 200.0;

GLfloat ang_asa_dir = 180;
GLfloat ang_asa_esq = 0.0;
// -> A movimentação da essa é simplesmente um rotate no eixo X dentro do desenhaDragao

bool asaSubindo = true;
//  -> O controle da asa será feito usando o angulo que aumenta de 2 em 2 graus.
//  -> Quando ele chegar em 45 graus, alterna-se o estado da variável de controle

GLfloat anguloDragao = 0.0;
GLfloat raio_dragao = 100.0;

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

void iluminacao(){

    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);  // Habilita o calculo da iluminação considerando a posição do observador

    // Luz ambiente
    GLfloat ambGlobal[] = {0.1, 0.1, 0.1, 1.0}; 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambGlobal);    // Define a cor ambiente da cena

    // Luz do sol
    GLfloat sunPosition[4] = {xLuz_sun, yLuz_sun, zLuz_sun, 1.0};
    GLfloat black[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat white[4] = {luzR, luzG, luzB, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    // Luz navio
    GLfloat torchAngle = 0.5;
    GLfloat torchDir[3] = {0.0, -1.0, 0.0};
    GLfloat torchExp = 3.0;
    GLfloat torchPos[4] = {x_pos_barco, 10000, z_pos_barco, 1.0};
    GLfloat torchAmb[4] = {0.0, 0.0, 0.0, 1.0}; 
    GLfloat torchDiff[4] = {0.1, 0.1, 0.0, 1.0};        
    GLfloat torchSpec[4] = {0.1, 0.1, 0.0, 1.0};

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, torchAngle);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, torchDir);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, torchExp);
    glLightfv(GL_LIGHT1, GL_POSITION, torchPos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, torchDiff);
    glLightfv(GL_LIGHT1, GL_AMBIENT, torchAmb);
    // lLightfv(GL_LIGHT1, GL_SPECULAR, torchSpec);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);

    // Luz castelo
    GLfloat xPos_LuzCastelo = 0.0;
    GLfloat yPos_LuzCastelo = 40.0;
    GLfloat zPos_LuzCastelo = 70.0;  

    GLfloat luzCasteloPos[4] = {xPos_LuzCastelo, yPos_LuzCastelo, zPos_LuzCastelo, 1.0};
    GLfloat luzCasteloAmb[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat luzCasteloDiff[4] = {0.5, 0.5, 0.5, 1.0};       
    GLfloat luzCasteloSpec[4] = {0.5, 0.5, 0.5, 1.0};           
    glLightfv(GL_LIGHT2, GL_POSITION, luzCasteloPos);
    glLightfv(GL_LIGHT2, GL_AMBIENT, luzCasteloAmb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, luzCasteloDiff);
    //glLightfv(GL_LIGHT2, GL_SPECULAR, luzCasteloSpec);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0);



    // GLfloat material[3][4] = {
    //     {1.0, 1.0, 1.0, 1.0},   // Specular
    //     {1.0, 1.0, 1.0, 1.0},   // Difusa
    //     {0.0, 0.0, 0.0, 1.0}    // Ambiente
    // };

    // GLint material_sn = 60;

    // glMaterialfv(GL_FRONT, GL_SPECULAR, &material[0][0]);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    // glMaterialfv(GL_FRONT, GL_AMBIENT, &material[2][0]);
    // glMateriali(GL_FRONT, GL_SHININESS, material_sn);


    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_COLOR_MATERIAL);
}

// #################### MATERIAIS ####################
void materialMar(){
    GLfloat material[3][4] = {
        {1.0, 1.0, 1.0, 1.0},   // Specular
        {1.0, 1.0, 1.0, 1.0},   // Difusa
        {0.0, 0.0, 0.0, 1.0}    // Ambiente
    };

    GLint material_sn = 60;

    glMaterialfv(GL_FRONT, GL_SPECULAR, &material[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &material[2][0]);
    glMateriali(GL_FRONT, GL_SHININESS, material_sn);
}

void materialCastelo() {
    GLfloat material[3][4] = {
        {0.2, 0.2, 0.2, 1.0},   // Specular
        {0.2, 0.2, 0.2, 1.0},   // Difusa
        {0.2, 0.2, 0.2, 1.0}    // Ambiente
    };

    GLint material_sn = 1;

    glMaterialfv(GL_FRONT, GL_SPECULAR, &material[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &material[2][0]);
    glMateriali(GL_FRONT, GL_SHININESS, material_sn);
}

void materialNavio() {
    GLfloat material[3][4] = {
        {0.0, 0.0, 0.0, 1.0},   // Specular
        {0.58, 0.30, 0.0, 1.0},   // Difusa
        {0.2, 0.2, 0.2, 1.0}    // Ambiente
    };

    GLint material_sn = 2;

    glMaterialfv(GL_FRONT, GL_SPECULAR, &material[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &material[2][0]);
    glMateriali(GL_FRONT, GL_SHININESS, material_sn);
}

void materialBandeira() {
    GLfloat material[3][4] = {
        {1.0, 0.0, 0.0, 1.0},   // Specular
        {1.0, 0.0, 0.0, 1.0},   // Difusa
        {0.2, 0.2, 0.2, 1.0}    // Ambiente
    };

    GLint material_sn = 2;
    
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &material[2][0]);
    glMateriali(GL_FRONT, GL_SHININESS, material_sn);
}

void materialDragao() {
    GLfloat material[3][4] = {
        {1.0, 0.0, 0.0, 1.0},   // Specular
        {1.0, 0.0, 0.0, 1.0},   // Difusa
        {0.2, 0.2, 0.2, 1.0}    // Ambiente
    };

    GLint material_sn = 2;


    glMaterialfv(GL_FRONT, GL_SPECULAR, &material[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &material[2][0]);
    glMateriali(GL_FRONT, GL_SHININESS, material_sn);

}

void materialRochedo() {
    GLfloat material[3][4] = {
        {0.1, 0.1, 0.1, 1.0},   // Specular
        {0.1, 0.1, 0.1, 1.0},   // Difusa
        {0.2, 0.2, 0.2, 1.0}    // Ambiente
    };

    GLint material_sn = 0;


    glMaterialfv(GL_FRONT, GL_SPECULAR, &material[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material[1][0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &material[2][0]);
    glMateriali(GL_FRONT, GL_SHININESS, material_sn);
}


// #################### OBJETOS ####################
void desenhaPiso(){
    glPushMatrix();
        materialMar();
        glColor3f(0.0, 1.0, 1.0);
        glTranslatef(0.0, 0.0, -0.5);
        glScalef(2000.0, 1.0, 2000.0);
        glutSolidSphere(1.0, 100, 100);
    glPopMatrix();
    

}

void desenhaTorreCentral(){
    glColor3f(0.5, 0.5, 0.5);

    glPushMatrix();
        glTranslatef(0.0, 7.0, 0.5);
        glRotatef(90, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 2
    glPushMatrix();
        glTranslatef(-1.4, 7.0, -0.5);
        glRotatef(20, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 3
    glPushMatrix();
        glTranslatef(1.4, 7.0, -0.5);
        glRotatef(-20, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 4
    glPushMatrix();
        glTranslatef(-1.4, 7.0, -2.0);
        glRotatef(-20, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 5
    glPushMatrix();
        glTranslatef(1.4, 7.0, -2.0);
        glRotatef(20, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 6
    glPushMatrix();
        glTranslatef(0.0, 7.0, -3.0);
        glRotatef(90, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //  Trapézio 1
    glPushMatrix();
        glTranslatef(0.0, 13.0, 0.7);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 2
    glPushMatrix();
        glTranslatef(1.4, 13.0, -0.2);
        glRotatef(70, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 3
    glPushMatrix();
        glTranslatef(-1.4, 13.0, -0.2);
        glRotatef(-70, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 4
    glPushMatrix();
        glTranslatef(1.5, 13.0, -2.3);
        glRotatef(110, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 5
    glPushMatrix();
        glTranslatef(-1.5, 13.0, -2.3);
        glRotatef(-110, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 6
    glPushMatrix();
        glTranslatef(0.0, 13.0, -3.2);
        glRotatef(-30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    // retangulo 1
    glPushMatrix();
        glTranslatef(0.0, 14.0, 1.0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);

    glPopMatrix();

    // retangulo 2  
    glPushMatrix();
        glTranslatef(0.0, 14.0, -3.5);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // retangulo 3
    glPushMatrix();
        glTranslatef(2.0, 14.0, -0.2);
        glRotatef(70, 0, 1, 0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // retangulo 4
    glPushMatrix();
        glTranslatef(-2.0, 14.0, -0.2);
        glRotatef(-70, 0, 1, 0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // retangulo 5
    glPushMatrix();
        glTranslatef(2.0, 14.0, -2.3);
        glRotatef(110, 0, 1, 0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // retangulo 6      
    glPushMatrix();
        glTranslatef(-2.0, 14.0, -2.3);
        glRotatef(-110, 0, 1, 0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Teto da torre
    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0.0, 13.5, -1.4);
        glScalef(3.0, 0.2, 4.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Teto da torre 2
    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-0.4, 13.5, -1.4);
        glScalef(3.0, 0.2, 4.2);
        glutSolidCube(1.0);
    glPopMatrix();

    // Teto da torre 3
    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0.4, 13.5, -1.4);
        glScalef(3.0, 0.2, 4.2);
        glutSolidCube(1.0);
    glPopMatrix();

    // Cabo da bandeira
    glPushMatrix();
        glColor3f(1, 0.7, 0.0);
        glTranslatef(0.0, 14.0, -1.4);
        glScalef(0.2, 9, 0.2);
        glutSolidCube(1.0);
    glPopMatrix();

    // Bandeira vermelha
    glPushMatrix();
        materialBandeira();
        glColor3f(1, 0, 0);
        glTranslatef(1.5, 18.0, -1.4);
        glScalef(3.0, 1.0, 0.2);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 1
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
        glTranslatef(0.0, 14.5, 1.0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 2
    glPushMatrix();
        glTranslatef(1.7, 14.5, 0.7);
        glRotatef(70, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 3
    glPushMatrix();
        glTranslatef(-1.7, 14.5, 0.7);
        glRotatef(-70, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);         
    glPopMatrix();

    // Tijolo 4
    glPushMatrix();
        glTranslatef(-2.3, 14.5, -1.0);
        glRotatef(-70, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);  
    glPopMatrix();

    // Tijolo 5
    glPushMatrix();
        glTranslatef(2.3, 14.5, -1.0);
        glRotatef(70, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 6
    glPushMatrix();
        glTranslatef(2.0, 14.5, -2.3);
        glRotatef(110, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 7
    glPushMatrix();
        glTranslatef(-2.0, 14.5, -2.3);
        glRotatef(-110, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 8
    glPushMatrix();
        glTranslatef(0.8, 14.5, -3.5);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 9
    glPushMatrix();
        glTranslatef(-0.8, 14.5, -3.5);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaTorre(){
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
        glTranslatef(0.0, 7.0, 0.5);
        glRotatef(90, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 2
    glPushMatrix();
        glTranslatef(-1.4, 7.0, -0.5);
        glRotatef(20, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 3
    glPushMatrix();
        glTranslatef(1.4, 7.0, -0.5);
        glRotatef(-20, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 4
    glPushMatrix();
        glTranslatef(-1.4, 7.0, -2.0);
        glRotatef(-20, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 5
    glPushMatrix();
        glTranslatef(1.4, 7.0, -2.0);
        glRotatef(20, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 6
    glPushMatrix();
        glTranslatef(0.0, 7.0, -3.0);
        glRotatef(90, 0, 1, 0);
        glScalef(0.5, 12.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //  Trapézio 1
    glPushMatrix();
        glTranslatef(0.0, 13.0, 0.7);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 2
    glPushMatrix();
        glTranslatef(1.4, 13.0, -0.2);
        glRotatef(70, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 3
    glPushMatrix();
        glTranslatef(-1.4, 13.0, -0.2);
        glRotatef(-70, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 4
    glPushMatrix();
        glTranslatef(1.5, 13.0, -2.3);
        glRotatef(110, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 5
    glPushMatrix();
        glTranslatef(-1.5, 13.0, -2.3);
        glRotatef(-110, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    //  Trapézio 6
    glPushMatrix();
        glTranslatef(0.0, 13.0, -3.2);
        glRotatef(-30, 1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3f(-1.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.4, 1.0, 0.0);
            glVertex3f(-1.4, 1.0, 0.0);
        glEnd();
    glPopMatrix();

    // retangulo 1
    glPushMatrix();
        glTranslatef(0.0, 14.0, 1.0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);

    glPopMatrix();

    // retangulo 2  
    glPushMatrix();
        glTranslatef(0.0, 14.0, -3.5);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // retangulo 3
    glPushMatrix();
        glTranslatef(2.0, 14.0, -0.2);
        glRotatef(70, 0, 1, 0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // retangulo 4
    glPushMatrix();
        glTranslatef(-2.0, 14.0, -0.2);
        glRotatef(-70, 0, 1, 0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // retangulo 5
    glPushMatrix();
        glTranslatef(2.0, 14.0, -2.3);
        glRotatef(110, 0, 1, 0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // retangulo 6      
    glPushMatrix();
        glTranslatef(-2.0, 14.0, -2.3);
        glRotatef(-110, 0, 1, 0);
        glScalef(2.8, 0.8, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Teto da torre
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(0.0, 13.5, -1.4);
        glScalef(3.0, 0.2, 4.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Teto da torre 2
    glPushMatrix();
        glTranslatef(-0.4, 13.5, -1.4);
        glScalef(3.0, 0.2, 4.2);
        glutSolidCube(1.0);
    glPopMatrix();

    // Teto da torre 3
    glPushMatrix();
        glTranslatef(0.4, 13.5, -1.4);
        glScalef(3.0, 0.2, 4.2);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 1
    glPushMatrix();
        glTranslatef(0.0, 14.5, 1.0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 2
    glPushMatrix();
        glTranslatef(1.7, 14.5, 0.7);
        glRotatef(70, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 3
    glPushMatrix();
        glTranslatef(-1.7, 14.5, 0.7);
        glRotatef(-70, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);         
    glPopMatrix();

    // Tijolo 4
    glPushMatrix();
        glTranslatef(-2.3, 14.5, -1.0);
        glRotatef(-70, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);  
    glPopMatrix();

    // Tijolo 5
    glPushMatrix();
        glTranslatef(2.3, 14.5, -1.0);
        glRotatef(70, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 6
    glPushMatrix();
        glTranslatef(2.0, 14.5, -2.3);
        glRotatef(110, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 7
    glPushMatrix();
        glTranslatef(-2.0, 14.5, -2.3);
        glRotatef(-110, 0, 1, 0);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 8
    glPushMatrix();
        glTranslatef(0.8, 14.5, -3.5);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 9
    glPushMatrix();
        glTranslatef(-0.8, 14.5, -3.5);
        glScalef(1.0, 0.5, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaMuro(){
    // Base
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
        glTranslatef(0.0, 2.0, 12.0);
        glScalef(14.0, 7.0, 3.0);
        glutSolidCube(1.0);
    glPopMatrix();
    
    // Retangulo base dos tijolos
    glPushMatrix();
        glTranslatef(0.0, 5.6, 13.0);
        glScalef(14.0, 0.5, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 1
    glPushMatrix();
        glTranslatef(-6.0, 6.0, 13.0);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 2
    glPushMatrix();
        glTranslatef(-4.0, 6.0, 13.0);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 3
    glPushMatrix();
        glTranslatef(-2.0, 6.0, 13.0);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 4
    glPushMatrix();
        glTranslatef(0.0, 6.0, 13.0);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 5
    glPushMatrix();
        glTranslatef(2.0, 6.0, 13.0);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 6
    glPushMatrix();
        glTranslatef(4.0, 6.0, 13.0);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 7
    glPushMatrix();
        glTranslatef(6.0, 6.0, 13.0);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

}

void desenhaPortao(){
    // Base 1
    glPushMatrix();
        glTranslatef(-5.5, 2.0, 11.0);
        glScalef(8.5, 7.0, 3.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Base 2
    glPushMatrix();
        glTranslatef(5.5, 2.0, 11.0);
        glScalef(8.5, 7.0, 3.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Base 3
    glPushMatrix();
        glTranslatef(0.0, 4.5, 11.0);
        glScalef(3.0 , 2.0, 3.0);
        glutSolidCube(1.0);
    glPopMatrix();
    
    // Retangulo base dos tijolos
    glPushMatrix();
        glTranslatef(0.0, 5.6, 11.8);
        glScalef(20.0, 0.5, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 1
    glPushMatrix();
        glTranslatef(-8.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 2
    glPushMatrix();
        glTranslatef(-6.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 3
    glPushMatrix();
        glTranslatef(-4.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 4
    glPushMatrix();
        glTranslatef(-2.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 5
    glPushMatrix();
        glTranslatef(0.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 6
    glPushMatrix();
        glTranslatef(2.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 7
    glPushMatrix();
        glTranslatef(4.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 8
    glPushMatrix();
        glTranslatef(6.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tijolo 9
    glPushMatrix();
        glTranslatef(8.0, 6.0, 11.8);
        glScalef(1.0, 1.2, 1.3);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaCastelo(){
    // TORRE CENTRAL ALTA
    materialCastelo();
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(1.5, 1.2, 1.5);
        desenhaTorreCentral();
    glPopMatrix();

    // TORRE CENTRAL MEDIA
    glPushMatrix();
        glTranslatef(0.0, 0.0, 1.0);
        glScalef(2.3, 0.8, 2.3);
        desenhaTorre();
    glPopMatrix();
 
    // TORRE CENTRAL BAIXA
    glPushMatrix();
        glTranslatef(0.0, 0.0, 1.0);
        glScalef(2.5, 0.3, 2.5);
        desenhaTorre();
    glPopMatrix();

    // Muro
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        desenhaPortao();
    glPopMatrix();

    // Muro 1
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(70, 0, 1, 0);
        desenhaMuro();
    glPopMatrix();

    // Muro 2
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(-70, 0, 1, 0);
        desenhaMuro();  
    glPopMatrix();

    // Muro 3
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.3);
        glRotatef(140, 0, 1, 0);
        desenhaMuro();
    glPopMatrix();

    // Muro 4
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.3);
        glRotatef(-140, 0, 1, 0);
        desenhaMuro();
    glPopMatrix();

    // Torre 1
    glPushMatrix();
        glScalef(1.1, 0.6, 1.1);
        glTranslatef(-9.0, 0.0, 10.0);
        desenhaTorre();
    glPopMatrix();

    // Torre 2
    glPushMatrix();
        glScalef(1.1, 0.6, 1.1);
        glTranslatef(9.0, 0.0, 10.0);
        desenhaTorre();
    glPopMatrix();

    // Torre 3
    glPushMatrix();
        glScalef(1.1, 0.6, 1.1);
        glTranslatef(13.0, 0.0, -0.8);
        desenhaTorre();
    glPopMatrix();

    // Torre 4
    glPushMatrix();
        glScalef(1.1, 0.6, 1.1);
        glTranslatef(-13.0, 0.0, -0.8);
        desenhaTorre();
    glPopMatrix();

    // Torre 5
    glPushMatrix();
        glScalef(1.6, 0.6, 1.1);
        glTranslatef(0.0, 0.0, -11.0);
        desenhaTorre();
    glPopMatrix();

    // PISO 1
    glColor3f(0.9, 0.9, 0.9);
    glPushMatrix();
        glTranslatef(0.0, 0.0, 2.4);
        glScalef(20.0, 3.0, 20.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // PISO 2
    glPushMatrix();
        glTranslatef(-2.2, 0.0, 0.1);
        glScalef(20.0, 3.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // PISO 3
    glPushMatrix();
        glTranslatef(2.2, 0.0, 0.1);
        glScalef(20.0, 3.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // PISO 4
    glPushMatrix();
        glTranslatef(0.0, 0.0,-4.0);
        glScalef(14.0, 3.0, 15.0);
        glutSolidCube(1.0);
    glPopMatrix();

}

void desenhoBaseCastelo(){
    // Esfera
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(0.0, -0.9, 0.0);
        glScalef(20.0, 1.2, 30.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

void desenhoIlhaCastelo(){
    desenhoBaseCastelo();
    desenhaCastelo();
}

void desenhaNavio(){
    //glColor3f(0.58, 0.30, 0.0);

    // Camada 1
    materialNavio();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.0, 0.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.0, -1.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.0, -2.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(10.0, 3.0, -1.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(10.0, 3.0, -2.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(10.0, 3.0, 0.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Lateral 1
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 2.7, 1.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.0, 1.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.3, 2.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.6, 2.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 4.3, 2.5);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, 2.5);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 6.0, 3.5);
        glScalef(50.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Lateral 2
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 2.7, -3.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.0, -3.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.3, -4.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 3.6, -4.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 4.3, -4.5);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, -4.5);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 6.0, -5.5);
        glScalef(50.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Lateral 1 da traseira
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(11.0, 3.3, 1.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(12.0, 3.6, 1.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(13.0, 3.9, 2.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(14.0, 4.2, 2.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(15.0, 5.1, 2.5);
        glScalef(20.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Lateral 2 da traseira
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(11.0, 3.3, -3.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(12.0, 3.6, -3.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(13.0, 3.9, -4.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(14.0, 4.2, -4.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(15.0, 5.1, -4.5);
        glScalef(20.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Trazeira
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(20.5, 3.5, -1.3);
        glScalef(1.0, 1.0, 3.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(21.5, 4.2, -1.0);
        glScalef(1.0, 1.0, 4.2);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(22.5, 4.6, -1.0);
        glScalef(1.0, 1.0, 4.9);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(23.5, 5.0, -1.0);
        glScalef(1.0, 1.0, 5.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(24.5, 5.4, -1.0);
        glScalef(1.0, 1.0, 6.8);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(24.5, 6.4, -1.0);
        glScalef(1.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(24.8, 7.4, -1.0);
        glScalef(1.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(25.1, 8.4, -1.0);
        glScalef(1.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(25.4, 9.4, -1.0);
        glScalef(1.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(25.7, 10.4, -1.0);
        glScalef(1.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(26.0, 11.4, -1.0);
        glScalef(1.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Lateral 3 da traseira
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(15.0, 6.1, 3.5);
        glScalef(19.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(16.0, 7.1, 3.5);
        glScalef(18.5, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(17.0, 8.1, 3.5);
        glScalef(18.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(18.0, 9.1, 3.5);
        glScalef(17.5, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(19.0, 10.1, 3.5);
        glScalef(17.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(20.0, 11.1, 3.5);
        glScalef(16.5, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();


    // Lateral 4 da traseira
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(15.0, 6.1, -5.5);
        glScalef(19.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(16.0, 7.1, -5.5);
        glScalef(18.5, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(17.0, 8.1, -5.5);
        glScalef(18.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(18.0, 9.1, -5.5);
        glScalef(17.5, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(19.0, 10.1, -5.5);
        glScalef(17.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(20.0, 11.1, -5.5);
        glScalef(16.5, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // lateral 1 ponta
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-11.0, 3.3, 1.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-12.0, 3.6, 1.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-13.0, 3.9, 2.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-14.0, 4.2, 2.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-15.0, 5.1, 2.5);
        glScalef(20.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Lateral 2 ponta
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-11.0, 3.3, -3.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-12.0, 3.6, -3.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-13.0, 3.9, -4.0);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-14.0, 4.2, -4.5);
        glScalef(20.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-15.0, 5.1, -4.5);
        glScalef(20.0, 1.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Camada 1 ponta
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-11.0, 3.0, 0.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-11.0, 3.0, -1.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-11.0, 3.0, -2.0);
        glScalef(20.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Inclinação da ponta
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-20.5, 3.5, -1.3);
        glScalef(1.0, 1.0, 3.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-21.5, 4.2, -1.0);
        glScalef(1.0, 1.0, 4.2);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-22.5, 4.6, -1.0);
        glScalef(1.0, 1.0, 4.9);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-23.5, 5.0, -1.0);
        glScalef(1.0, 1.0, 5.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-24.5, 5.4, -1.0);
        glScalef(1.0, 1.0, 6.8);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-25.5, 5.4, -1.0);
        glScalef(1.0, 1.0, 6.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-26.5, 5.7, -1.0);
        glScalef(1.0, 1.0, 5.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-27.5, 6.0, -1.0);
        glScalef(1.0, 1.0, 4.9);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-28.5, 6.3, -1.0);
        glScalef(1.0, 1.0, 4.2);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-29.5, 6.6, -1.0);
        glScalef(1.0, 1.0, 3.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-30.5, 6.9, -1.0);
        glScalef(1.0, 1.0, 2.6);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-31.5, 7.2, -1.0);
        glScalef(1.0, 1.0, 1.4);
        glutSolidCube(1.0); 
    glPopMatrix();

    // Piso
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, 2.0);
        glScalef(50.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, 1.0);
        glScalef(50.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, 0.0);
        glScalef(50.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, -1.0);
        glScalef(50.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, -2.0);
        glScalef(50.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, -3.0);
        glScalef(50.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 5.3, -4.0);
        glScalef(50.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Detalhe ponta 1
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-25.5, 6.0, 2.9);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-26.5, 6.2, 2.5);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-27.5, 6.6, 2.0);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-28.5, 6.9, 1.5);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-29.5, 7.2, 1.0);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-30.5, 7.5, 0.5);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-31.5, 7.8, 0.0);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-32.5, 7.8, -1.0);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Detalhe ponta 2
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-25.5, 6.0, -5.0);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-26.5, 6.2, -4.4);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-27.5, 6.6, -3.9);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-28.5, 6.9, -3.4);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-29.5, 7.2, -2.9);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-30.5, 7.5, -2.4);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-31.5, 7.8, -1.9);
        glScalef(1.0, 0.5, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // CABINE DO CAPITAO
    // Parede 1
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(18.3, 8.8, -3.5);
        glScalef(1.0,6.0, 3.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 2
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(18.3, 8.8, 1.5);
        glScalef(1.0,6.0, 3.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parede 3
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(18.3, 10.8, -1.0);
        glScalef(1.0, 3.0, 3.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // teto
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(22.3, 10.8, -1.0);
        glScalef(7.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // TIMAO
    // suporte
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(20.3, 10.8, -1.0);
        glScalef(0.3, 6.0, 0.3);
        glutSolidCube(1.0);
    glPopMatrix();
    // Circulo
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(20.6, 13.8, -1.0);
        glScalef(0.05, 0.8, 0.8);
        glutSolidSphere(1.5, 20, 20);
    glPopMatrix();

    // Escada 1
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(6.2, 6.0, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(7.2, 6.5, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(8.2, 7.0, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(9.2, 7.5, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(10.2, 8.0, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(11.2, 8.5, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(12.2, 9.0, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(13.2, 9.5, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(14.2, 10.0, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(15.2, 10.5, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(16.2, 11.0, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(17.2, 11.5, -4.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Escada 2
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(6.2, 6.0, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(7.2, 6.5, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(8.2, 7.0, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(9.2, 7.5, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(10.2, 8.0, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(11.2, 8.5, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(12.2, 9.0, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(13.2, 9.5, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(14.2, 10.0, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(15.2, 10.5, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(16.2, 11.0, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1,0.55,0.05);
        glTranslatef(17.2, 11.5, 2.0);
        glScalef(1.2, 0.5, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // VELA 1
    // Suporte
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(0.0, 16.0, -1.0);
        glScalef(1.0, 19, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-1.0, 9.0, -1.0);
        glScalef(1.0, 1.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-1.0, 23.0, -1.0);
        glScalef(1.0, 1.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Vela
    glPushMatrix();
        glColor3f(1,1,1);
        if (barcoLigado){
            glTranslatef(-2.0, 16.0, -1.0);
        } else{
            glTranslatef(-1.0, 16.0, -1.0);
        }
        glScalef(1.0, 13.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // VELA 2 - média
    // Suporte
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-10.0, 16.0, -1.0);
        glScalef(1.0, 19, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-11.0, 12.0, -1.0);
        glScalef(1.0, 1.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-11.0, 22.0, -1.0);
        glScalef(1.0, 1.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Vela
    glPushMatrix();
        glColor3f(1,1,1);
        if (barcoLigado){
            glTranslatef(-12.0, 17.0, -1.0);
        } else {
            glTranslatef(-11.0, 17.0, -1.0);
        }
        glScalef(1.0, 9.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // VELA 3 - pequena
    // Suporte
    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-20.0, 16.0, -1.0);
        glScalef(1.0, 19, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-21.0, 14.0, -1.0);
        glScalef(1.0, 1.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5,0.35,0.05);
        glTranslatef(-21.0, 20.0, -1.0);
        glScalef(1.0, 1.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Vela
    glPushMatrix();
        glColor3f(1,1,1);
        if (barcoLigado){
            glTranslatef(-22.0, 17.0, -1.0);
        } else{
            glTranslatef(-21.0, 17.0, -1.0);
        }
        glScalef(1.0, 5.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // BANDEIRA
    glPushMatrix();
        glColor3f(0.5,0.5,0.5);
        glTranslatef(-10.0, 28.0, -1.0);
        glScalef(0.2, 5, 0.2);
        glutSolidCube(1.0);
    glPopMatrix();

    if (barcoLigado){
        glPushMatrix();
            materialBandeira();
            glColor3f(1,0,0);
            glTranslatef(-10.0, 29.0, -3.5);
            glScalef(0.2, 3, 5.0);
            glutSolidCube(1.0);
        glPopMatrix();
    } else{
        glPushMatrix();
            materialBandeira();
            glColor3f(1,0,0);
            glTranslatef(-10.0, 29.0, -1.4);
            glScalef(0.2, 3, 0.1);
            glutSolidCube(1.0);
        glPopMatrix();
    }

}

void desenhaSol(){
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(xLuz_sun, yLuz_sun , 0.0);
        glutSolidSphere(10.0, 20, 20);
    glPopMatrix();
}



// Dragão
void escamaDragao(){
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-0.5, 10.0, 0.0);
        glScalef(1.5, 6, 1.2);
        glutSolidCube(1.0);
    glPopMatrix();
}

void corpoDragao(){
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(5.0, 5.0, 6.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(5.0, -0.1, 0.0);
        glScalef(6.0, 6.5, 7.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(11.0, -0.2, 0.0);
        glScalef(7.0, 7.5, 8.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(22.0, -1.0, 0.0);
        glScalef(16.0, 12.0, 12.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(36.0, -0.5, 0.0);
        glScalef(13.0, 9.0, 8.8);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(47.0, -0.5, 0.0);
        glScalef(10.0, 8.0, 7.5);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(56.0, -0.5, 0.0);
        glScalef(8.0, 6.0, 6.5);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(63.0, 1.5, 0.0);
        glRotatef(30, 0.0, 0.0, 1.0);
        glScalef(10.0, 5.0, 5.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(71.0, 4.0, 0.0);
        glScalef(10.0, 3.5, 4.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(-2.0, -6.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(2.0, -3.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(6.0, 0.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(11.0, 6.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(15.0, 8.6, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(19.0, 9.6, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(24.0, 12.6, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(28.0, 16.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(31.0, 18.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(35.0, 20.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(35.0, 20.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(39.0, 22.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(43.0, 23.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(47.0, 25.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(43.0, 23.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(50.0, 29.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(53.0, 34.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(57.0, 37.0, 0.0);
        escamaDragao();
    glPopMatrix();
}

void cabecaDragao(){

    // Cranio
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-5.0, 0.0, 0.0);
        glScalef(6.0, 8.0, 9.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Mandibula inferior
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-12.0, -2.6, 0.0);
        glScalef(9.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Lingua
    glPushMatrix();
        glColor3f(1,0.5,0.5);
        glTranslatef(-12.0, -1.8, 0.0);
        glScalef(9.0, 1.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Mandibula superior
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-12.0, 1.2, 0.0);
        glScalef(9.0, 3.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Nariz
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-15.0, 3.0, 0.0);
        glScalef(2.6, 2.0, 5.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Olho direito
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(-6.0, 2.0, 4.5);
        glScalef(1.0, 1.0, 1.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // Olho esquerdo
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(-6.0, 2.0, -4.0);
        glScalef(1.0, 1.0, 1.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // Escamas
    glPushMatrix();
        glRotatef(-35, 0.0, 0.0, 1.0);
        glTranslatef(-7.0, -8.0, 0.0);
        escamaDragao();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-30, 0.0, 0.0, 1.0);
        glTranslatef(-4.0, -7.0, 0.0);
        escamaDragao();
    glPopMatrix();

}

void asaDragao(){
    glColor3f(0.8, 0.0, 0.0);
    // Parte 1
    glPushMatrix();
        glTranslatef(18.0, 2.0, 13.0);
        glScalef(6.0, 2.5, 15.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parte 2
    glPushMatrix();
        glTranslatef(18.0, 2.0, 28.0);
        glScalef(5.0, 1.5, 15.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parte 3
    glPushMatrix();
        glTranslatef(18.0, 2.0, 43.0);
        glScalef(4.0, 1.0, 15.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parte 4
    glPushMatrix();
        glTranslatef(28.0, 2.0, 19.0);
        glScalef(16.0, 1.5, 2.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // Parte 5
    glPushMatrix();
        glTranslatef(28.0, 2.0, 34.0);
        glScalef(16.0, 1.0, 2.5);
        glutSolidCube(1.0);
    glPopMatrix();


    // Subasa 1
    glPushMatrix();
        glTranslatef(25.0, 2.0, 12.0);
        glScalef(18.0, 0.5, 15.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Subasa 2
    glPushMatrix();
        glTranslatef(26.0, 2.0, 26.0);
        glScalef(18.0, 0.5, 15.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Subasa 3
    glPushMatrix();
        glTranslatef(27.0, 2.0, 42.0);
        glScalef(18.0, 0.5, 15.0);
        glutSolidCube(1.0);
    glPopMatrix();
}



void desenhaDragao(){
    glColor3f(1.0, 0.0, 0.0);

    corpoDragao();

    glPushMatrix();
        glTranslatef(-0.5, 3.0, 0.0);
        glRotatef(20, 0.0, 0.0, 1.0);
        cabecaDragao();
    glPopMatrix();

    glPushMatrix();
        glRotatef(ang_asa_esq, 1.0, 0.0, 0.0);
        asaDragao();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 4.0, 0.0);
        glRotatef(ang_asa_dir, 1.0, 0.0, 0.0);
        asaDragao();
    glPopMatrix();
}


// Ilha
void terraIlha(){
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(0.0, 10.0, 0.0);
        glScalef(400.0, 20.0, 300.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(0.0, 27.0, 0.0);
        glScalef(300.0, 10.0, 200.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

void arvore(){
    // folhas
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(0.0, 10.0, 0.0);
        glScalef(10.0, 20.0, 10.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // tronco
    glPushMatrix();
        glColor3f(0.5, 0.3, 0.0);
        glTranslatef(0.0, -20.0, 0.0);
        glScalef(2.0, 20.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
}

void  xIlha(){
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(0.0, 50.0, 0.0);
        glScalef(180.0, 30.0, 20.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glTranslatef(0.0, 50.0, 0.0);
        glScalef(180.0, 30.0, 20.0);
        glutSolidCube(1.0);
    glPopMatrix();
}


void desenhaIlha(){
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        terraIlha();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-70.0, 135.0, -70.0);
        glScalef(3, 3, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-100.0, 135.0, -100.0);
        glScalef(3, 6, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-120.0, 135.0, -70.0);
        glScalef(3, 4, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-70.0, 135.0, -120.0);
        glScalef(3, 5, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-100.0, 135.0, -150.0);
        glScalef(3, 3, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-120.0, 135.0, -120.0);
        glScalef(3, 4, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-70.0, 135.0, -170.0);
        glScalef(3, 5, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-150.0, 135.0, -100.0);
        glScalef(3, 5, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-170.0, 135.0, -70.0);
        glScalef(3, 3, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-150.0, 135.0, -120.0);
        glScalef(3, 4, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-170.0, 135.0, -120.0);
        glScalef(3, 5, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-200.0, 135.0, -100.0);
        glScalef(3, 3, 3);
        arvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-200.0, 135.0, -80.0);
        glScalef(3, 4, 3);
        arvore();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(130.0, -25.0, 0.0);
        glRotatef(20, 0.0, 1.0, 0.0);
        xIlha();
    glPopMatrix();
}


void textOnScreen(float x, float y, char *string){
    // Sempre manter o texto acima de tudo
    glMatrixMode(GL_PROJECTION);    // Seleciona a matriz de projeção
    glPushMatrix();                 // Salva a matriz de projeção atual
    glLoadIdentity();               // Reseta a matriz de projeção
    glOrtho(0, 800, 0, 600, -5, 5); // Define uma projeção ortogonal
    glMatrixMode(GL_MODELVIEW);     // Seleciona a matriz de modelagem
    glPushMatrix();                 // Salva a matriz de modelagem atual
    glLoadIdentity();               // Reseta a matriz de modelagem
    glDisable(GL_LIGHTING);         // Desabilita iluminação
    glDisable(GL_DEPTH_TEST);       // Desabilita teste de profundidade
    glRasterPos2f(x, y);            // Posiciona o texto na tela
    while (*string)                 // Enquanto não for o fim da string
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++); // Escreve o caractere
    glEnable(GL_DEPTH_TEST);        // Habilita teste de profundidade
    glEnable(GL_LIGHTING);          // Habilita iluminação
    glMatrixMode(GL_PROJECTION);    // Seleciona a matriz de projeção               
    glPopMatrix();                  // Restaura a matriz de projeção anterior
    glMatrixMode(GL_MODELVIEW);     // Seleciona a matriz de modelagem
    glPopMatrix();                  // Restaura a matriz de modelagem anterior
}

void desenhaRochedo(){
    // Camada 1
    glPushMatrix();
        glColor3f(0.9, 0.9, 0.9);
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(300.0, 20.0, 100.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // Camada 2
    glPushMatrix();
        glColor3f(0.8, 0.8, 0.8);
        glTranslatef(0.0, 10.0, 0.0);
        glScalef(250.0, 40.0, 80.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // Camada 3
    glPushMatrix();
        glColor3f(0.7, 0.7, 0.7);
        glTranslatef(0.0, 20.0, 0.0);
        glScalef(200.0, 60.0, 60.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // Camada 4
    glPushMatrix();
        glColor3f(0.6, 0.6, 0.6);
        glTranslatef(0.0, 30.0, 0.0);
        glScalef(150.0, 80.0, 40.0);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

}

void desenhaRochedos(){
    materialRochedo();
    glPushMatrix();
        glTranslatef(400.0, 0.0, -500.0);
        glRotatef(-45, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.8, 0.8, 0.8);
        glTranslatef(700.0, 0.0, -200.0);
        glRotatef(-70, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.6, 0.6, 0.6);
        glTranslatef(1000.0, 0.0, 100.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(1200.0, 0.0, 300.0);
        glRotatef(-110, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(1000.0, 0.0,700.0);
        glRotatef(-120, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(800.0, 0.0, 900.0);
        glRotatef(-140, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.8, 0.8, 0.8);
        glTranslatef(200.0, 0.0, 700.0);
        glRotatef(-160, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.7, 0.7, 0.7);
        glTranslatef(-300.0, 0.0, 900.0);
        glRotatef(-180, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.6, 0.6, 0.6);
        glTranslatef(-800.0, 0.0, 1000.0);
        glRotatef(-200, 0.0, 1.0, 0.0);
        desenhaRochedo();
    glPopMatrix();

    

}

void cenario(){
    glRotatef(anguloX, 0, 1, 0);
    glRotatef(anguloY, 1, 0, 0);

    glPushMatrix();

        glPushMatrix();
            desenhaRochedos();
        glPopMatrix();
            
        glPushMatrix();
            glTranslatef(x_pos_barco, y_pos_barco, z_pos_barco);
            glRotatef(barcoAngle, 0, 1, 0);
            desenhaNavio();
        glPopMatrix();

        glPushMatrix();
            desenhaPiso();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-300.0, 0.0, -500.0);
            glScalef(0.5, 0.5, 0.5);
            desenhaIlha();
        glPopMatrix();

        glPushMatrix();
            glScalef(2, 2, 2);
            glTranslatef(x_pos_dragao, y_pos_dragao, z_pos_dragao);
            glRotatef(-anguloDragao + 90, 0.0, 1.0, 0.0);
            desenhaDragao();
        glPopMatrix();

        glPushMatrix();
            desenhaSol();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 2.0, 0.0);
            glScalef(4, 4, 4);
            desenhoIlhaCastelo();
        glPopMatrix();

        

        
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            textOnScreen(10, 130, "CAMERAS: ");

            // Camera 1
            if(camera == 1){
                glColor3f(0.0, 0.0, 0.5);
            }else{
                glColor3f(0.0, 0.0, 0.0);
            }
            textOnScreen(10, 110, "1 - Horizontal Geral");

            // Camera 2
            if(camera == 2){
                glColor3f(0.0, 0.0, 0.5);
            }else{
                glColor3f(0.0, 0.0, 0.0);
            }
            textOnScreen(10, 90, "2 - Vertical Geral");

            // Camera 3
            if(camera == 3){
                glColor3f(0.0, 0.0, 0.5);
            }else{
                glColor3f(0.0, 0.0, 0.0);
            }
            textOnScreen(10, 70, "3 - Navio");

            // Camera 4
            if(camera == 4){
                glColor3f(0.0, 0.0, 0.5);
            }else{
                glColor3f(0.0, 0.0, 0.0);
            }
            textOnScreen(10, 50, "4 - Castelo");

            // Camera 5
            if(camera == 5){
                glColor3f(0.0, 0.0, 0.5);
            }else{
                glColor3f(0.0, 0.0, 0.0);
            }
            textOnScreen(10, 30, "5 - Ilha");

            // Camera 6
            if(camera == 6){
                glColor3f(0.0, 0.0, 0.5);
            }else{
                glColor3f(0.0, 0.0, 0.0);
            }
            textOnScreen(10, 10, "6 - Dragao");
        glPopMatrix();


    glPopMatrix();
}

// ########################## FUNÇÕES ESPECIAIS ##########################
void sunMove(){

    // Movimentação do sol
    GLfloat anguloLuzRad = 0;
    anguloLuzRad = anguloLuz * M_PI / 180.0;

    xLuz_sun = raio * cos(anguloLuzRad);
    yLuz_sun = raio * sin(anguloLuzRad);

    if(anguloLuz > 150 && anguloLuz < 360 && luzR >= 0.0){
        luzR -= 0.01;
        luzG -= 0.01;
        luzB -= 0.01;
    }

    if(anguloLuz > 0 && anguloLuz < 90 && luzR <= 1.0){
        luzR += 0.01;
        luzG += 0.01;
        luzB += 0.01;
    }

    anguloLuz += 0.1;
    if(anguloLuz >= 360){
        anguloLuz = 0;
    }

    // Movimentação do dragoa
    GLfloat anguloDragaoRad = 0;
    anguloDragaoRad = anguloDragao * M_PI / 180.0;

    x_pos_dragao = -200 + raio_dragao * cos(anguloDragaoRad);
    z_pos_dragao = -300 + raio_dragao * sin(anguloDragaoRad);

    anguloDragao += 1.0;

    if(anguloDragao >= 360){
        anguloDragao = 0;
    }

    


    // Movimentação da asa do dragao
    if(asaSubindo){
        ang_asa_esq += 2.0;
        ang_asa_dir -= 2.0;

        if(ang_asa_esq >= 45){
            asaSubindo = false;
        }
    }else{
        ang_asa_esq -= 2.0;
        ang_asa_dir += 2.0;

        if(ang_asa_esq <= -45){
            asaSubindo = true;
        }

        
    }





    iluminacao();
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    GLfloat ratio = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, ratio, 1.0, 4000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void teclado(unsigned char key, int x, int y)
{
    if(key >= '1' && key <= '6'){
        camera = key - '0';
    }

    if (key == 'e'){
        barcoLigado = !barcoLigado;
    }

    if (key == '1'){
        cameraNoBarco = false;
        // Camera geral
        x_pos_cam = x_pos_cam_1;
        y_pos_cam = y_pos_cam_1;
        z_pos_cam = z_pos_cam_1;

        x_look_cam = 0;
        y_look_cam = 0;
        z_look_cam = 0;
    }
    else if (key == '2'){
        cameraNoBarco = false;
        // Camera navio
        x_pos_cam = x_pos_cam_2;
        y_pos_cam = y_pos_cam_2;
        z_pos_cam = z_pos_cam_2;
        x_look_cam = 0;
        y_look_cam = 0;
        z_look_cam = 0;
    }
    else if (key == '3'){
        // Camera castelo
        cameraNoBarco = true;
    }
    else if (key == '4'){
        // Camera ilha
        cameraNoBarco = false;
        x_pos_cam = x_pos_cam_4;
        y_pos_cam = y_pos_cam_4;
        z_pos_cam = z_pos_cam_4;

        x_look_cam = 0;
        y_look_cam = 0;
        z_look_cam = 0;
    }
    else if (key == '5'){
        // Camera floresta
        cameraNoBarco = false;
        x_pos_cam = x_pos_cam_5;
        y_pos_cam = y_pos_cam_5;
        z_pos_cam = z_pos_cam_5;

        x_look_cam = x_pos_ilha;
        y_look_cam = y_pos_ilha;
        z_look_cam = z_pos_ilha;
    }
    else if (key == '6') {
        // Camera dragao
        cameraNoBarco = false;
        x_pos_cam = x_pos_cam_6;
        y_pos_cam = y_pos_cam_6;
        z_pos_cam = z_pos_cam_6;

        x_look_cam = x_pos_ilha;
        y_look_cam = y_pos_ilha;
        z_look_cam = z_pos_ilha;
    }

    if (barcoLigado){
        if (key == 'w'){
            // Move para frente
            z_pos_barco -= 2.0;

            barcoAngle = -90;     
        }
        if (key == 's'){
            // Move para trás
            z_pos_barco += 2.0;

            barcoAngle = 90;
        }
        if (key == 'a'){
            // Move para esquerda
            x_pos_barco -= 2.0;

            barcoAngle = 0;

        }
        if (key == 'd'){
            // Move para direita
            x_pos_barco += 2.0;

            barcoAngle = 180;

        }
        
    }

    glutPostRedisplay();
}

void tecladoEsp(int key, int x, int y){


    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if(cameraNoBarco){
        x_pos_cam = x_pos_barco;
        y_pos_cam = y_pos_barco + 100;
        z_pos_cam = z_pos_barco + 100;

        x_look_cam = x_pos_barco;
        y_look_cam = y_pos_barco + 50;
        z_look_cam = z_pos_barco;

    }

    // O LookAt tá sendo usando para mover a câmera de acordo com a movimentação do navio

    gluLookAt(
        x_pos_cam, y_pos_cam, z_pos_cam,  // Onde a câmera está
        x_look_cam, y_look_cam, z_look_cam,  // Para onde a câmera está olhando
        0.0, 1.0, 0.0   // Vetor Up
    );


    cenario();

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
    glutCreateWindow("Iron Islands");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMov);
    glutReshapeFunc(reshape);
    glutSpecialFunc(tecladoEsp);
    glutIdleFunc(sunMove);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}