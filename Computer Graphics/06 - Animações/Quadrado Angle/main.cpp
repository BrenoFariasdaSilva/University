#include <stdio.h>
#include <GL/glut.h>
#include <iostream>

void init();
void display();
void movimentaQuadrado();

GLfloat tx, rightLimit, leftLimit;
int drivingRight;

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200,0);	// posição da janela
	glutInitWindowSize(400,400);		// largura e altura da janela
	glutCreateWindow("Animação");	// cria a janela

	init();						// executa função de inicialização
	glutDisplayFunc(display);	// função "display" como a função de
								// callback de exibição

	glutMainLoop();			// mostre tudo e espere
	return 0;
}

void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);		// define a cor de fundo

	glMatrixMode(GL_PROJECTION); 	// carrega a matriz de projeção
	gluOrtho2D(0, 200, 0, 150);  	// define projeção ortogonal 2D que
									// mapeia objetos da coordenada do
									// mundo para coordenadas da tela
    tx = 0;
    leftLimit = 20;
    rightLimit = 180;
    drivingRight = 1;
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    movimentaQuadrado();
    glBegin(                                                                                                                                                                                                                                                           GL_QUADS);
        glVertex2f(0, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 0);
        glVertex2f(0, 0);
    glEnd();
    glPopMatrix();

    glutPostRedisplay();
	glutSwapBuffers();
}

void movimentaQuadrado() {
    if (drivingRight == 1 && tx < 180) {
		tx++;                                                       
	} else if (drivingRight == 0 && tx > -1) 
        tx--;

    glTranslatef(tx, tx, 0);
	if (tx == 180 || tx == 0) {
		if (drivingRight == 1)
			drivingRight = 0;
		else 
			drivingRight = 1;
	}
	
}