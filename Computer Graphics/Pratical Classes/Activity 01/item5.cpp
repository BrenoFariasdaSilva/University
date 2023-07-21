// Pegar a hora o minuto e o segundo atual

#include <ctime>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

using namespace std;

int init();
void display();
void desenhaCasa();
void transformObject();
void movimentaObjeto(int horizontal, int vertical);
void desenhaQuadrado();
void desenhaTriangulo();
void desenhaCirculo();
void desenhaObjeto(int objeto);
void desenhaLinhasRelogio(void);
void desenhaPonteiroHoras(void);
void desenhaPonteiroMinutos(void);
void desenhaPonteiroSegundos(void);
void rotate();
void horaToAngle();

GLfloat rfx, rfy, sx, sy, angle, tx, ty, objeto, angle_min, angle_hor, angle_seg;
bool direita, esquerda, cima, baixo, borda;
int hora, minuto, segundo;

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200,0);	// posição da janela
	glutInitWindowSize(400,300);		// largura e altura da janela
	glutCreateWindow("Animação");	// cria a janela

	init();						// executa função de inicialização
	glutDisplayFunc(display);	// função "display" como a função de
								// callback de exibição

	glutMainLoop();			// mostre tudo e espere
	return 0;
}

int init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);		// define a cor de fundo

	glMatrixMode(GL_PROJECTION); 	// carrega a matriz de projeção
	gluOrtho2D(0, 200, 0, 150);  	// define projeção ortogonal 2D que
									// mapeia objetos da coordenada do
									// mundo para coordenadas da tela

    time_t now = time(0);
    tm *ltm = localtime(&now);
    hora = ltm->tm_hour;
    minuto = ltm->tm_min;
    segundo = ltm->tm_sec;

    horaToAngle();

    cout << "Hora: " << ltm->tm_hour << endl;
    cout << "Minuto: " << ltm->tm_min << endl;
    cout << "Segundo: " << ltm->tm_sec << endl;

    direita = true;
    cima = true;
    esquerda = false;
    baixo = false;
    tx = 0;
    ty = 0;
    borda = false;
    objeto = rand() % 3;
    angle = 0;
    
    return 0;
}

void desenhaCasa(void){
	glBegin(GL_QUADS);
		glVertex2f(0, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 0);
        glVertex2f(0, 0);
	glEnd();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

    // sleep 1seg
    sleep(1);
    rotate();

    // Segundos
    glPushMatrix();
    desenhaPonteiroSegundos();
    glPopMatrix();

    // Minutos
    glPushMatrix();
    desenhaPonteiroMinutos();
    glPopMatrix();

    // Horas
    glPushMatrix();
    desenhaPonteiroHoras();
    glPopMatrix();


    // Linhas
    glPushMatrix();
    glLoadIdentity();
    desenhaLinhasRelogio();
    glPopMatrix();


    // Circulo do relogio
    glPushMatrix();
    glLoadIdentity();
    desenhaCirculo();
    glPopMatrix();

    glutPostRedisplay();    // chama a função display novamente
	glutSwapBuffers();      // troca os buffers
}



void desenhaCirculo(void){
    glBegin(GL_POINTS);
        for (int i = 0; i < 7200; i++){
            float degInRad = i*180.0f/3.14159f;
            glVertex2f(cos(degInRad)*50.0f + 100, sin(degInRad)*50.0f + 75);
        }
    glEnd();
}

void desenhaLinhasRelogio(void){
    // Cor preta
    glColor3f(0.0, 0.0, 0.0);
    // Desenhar as linha das horas (12 maiores) e minutos (48 menores) sem sair do centro
    glBegin(GL_LINES);
        for (int i = 0; i < 60; i++){
            if (i % 5 == 0){
                // Linhas maiores que não saem do centro
                glVertex2f(cos(i*6*3.14159f/180.0f)*45.0f + 100, sin(i*6*3.14159f/180.0f)*45.0f + 75);
                glVertex2f(cos(i*6*3.14159f/180.0f)*35.0f + 100, sin(i*6*3.14159f/180.0f)*35.0f + 75);
            } else {
                // Linhas menores que não saem do centro
                glVertex2f(cos(i*6*3.14159f/180.0f)*45.0f + 100, sin(i*6*3.14159f/180.0f)*45.0f + 75);
                glVertex2f(cos(i*6*3.14159f/180.0f)*40.0f + 100, sin(i*6*3.14159f/180.0f)*40.0f + 75);
            }
        }
        
    glEnd();
}

void desenhaPonteiroMinutos(void){

    // Desenhar o ponteiro das horas
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(100, 75);
        glVertex2f(cos((angle_min)*3.14159f/180.0f)*30.0f + 100, sin((angle_min)*3.14159f/180.0f)*30.0f + 75);
    glEnd();
}

void desenhaPonteiroHoras(void){

    // Desenhar o ponteiro dos minutos
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex2f(100, 75);
        glVertex2f(cos((angle_hor)*3.14159f/180.0f)*20.0f + 100, sin((angle_hor)*3.14159f/180.0f)*20.0f + 75);
    glEnd();
}

void desenhaPonteiroSegundos(void){
    
        // Desenhar o ponteiro dos segundos
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
            glVertex2f(100, 75);
            glVertex2f(cos((angle_seg)*3.14159f/180.0f)*40.0f + 100, sin((angle_seg)*3.14159f/180.0f)*40.0f + 75);
        glEnd();
}

void rotate(){
    angle_seg -= 6;
    angle_min -= 0.1;
    angle_hor -= 0.1/12;
}

void horaToAngle(){
    angle_seg = 360 - (segundo * 6) + 90;
    angle_min = 360 - (minuto * 6) + 90;
    angle_hor = 360 - (hora * 30) + 90;
}