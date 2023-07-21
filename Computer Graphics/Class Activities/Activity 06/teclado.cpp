#include <stdio.h>
#include <GL/glut.h>
#include <iostream>

int init(void);
void display(void);
void quadrado();
void moveQuadrado();
void teclado1(int key, int x, int y);
void teclado2(unsigned char key, int x, int y);


int direcao = 0;
float tx=0,ty=0,tz=0;


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
}

void display(){
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0f, 0.0f, 0.0f);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
        glColor3f(1,0,0);

        moveQuadrado();
        glTranslatef(tx, ty, tz);
        quadrado();

        glutSpecialFunc(teclado1);
        glutKeyboardFunc(teclado2);

        glutPostRedisplay();
        glutSwapBuffers();
}

void quadrado(void){
	glBegin(GL_QUADS);
		glVertex2f(0, 20);
		glVertex2f(20, 20);
		glVertex2f(20, 0);
		glVertex2f(0, 0);
	glEnd();
}


void teclado1(int key, int x, int y){
    // Verifica se foi teclado as setinhas
    if(key == GLUT_KEY_LEFT){
        direcao = 1;
    }
    if(key == GLUT_KEY_RIGHT){
        direcao = 2;
    }
    if(key == GLUT_KEY_UP){
        direcao = 3;
    }
    if(key == GLUT_KEY_DOWN){
        direcao = 4;
    }

}

void teclado2(unsigned char key, int x, int y){
    // Verifica se foi teclado w a s d e p
    if(key == 'w'){
        direcao = 3;
    }
    if(key == 's'){
        direcao = 4;
    }
    if(key == 'a'){
        direcao = 1;
    }
    if(key == 'd'){
        direcao = 2;
    }
    if(key == 'p'){
        direcao = 0;
    }
}

void moveQuadrado(){
    if(direcao == 1){
        tx -= 2;
    }
    if(direcao == 2){
        tx += 2;
    }
    if(direcao == 3){
        ty += 2;
    }
    if(direcao == 4){
        ty -= 2;
    }

    // Verifica se o quadrado saiu da tela e faz ele parar
    if(tx > 180){
        tx = 180;
        direcao = 0;
    }else if(tx < 0){
        tx = 0;
        direcao = 0;
    }

    if(ty > 130){
        ty = 130;
        direcao = 0;
    }else if(ty < 0){
        ty = 0;
        direcao = 0;
    }

}
