#include <stdio.h>
#include <GL/glut.h>
#include <iostream>

void init();
void display();
void desenhaCasa();
void transformObject();
void rotate2D(GLfloat rotangle);
void scale2D(GLfloat incx, GLfloat incy, GLfloat maxx, GLfloat minx);
void movimentaQuadrado();

GLfloat rfx, rfy, sx, sy, angle, ty;
bool increasing;

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

void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);		// define a cor de fundo

	glMatrixMode(GL_PROJECTION); 	// carrega a matriz de projeção
	gluOrtho2D(0, 200, 0, 150);  	// define projeção ortogonal 2D que
									// mapeia objetos da coordenada do
									// mundo para coordenadas da tela
    rfx = 100;
    rfy = 65;
    sx = sy = 1;
    angle = 0;
    ty = 0;
    increasing = true;
}

void desenhaCasa(void){
	glBegin(GL_POLYGON);
		glVertex2f(110, 50);
		glVertex2f(110, 70);
		glVertex2f(100, 80);
		glVertex2f(90, 70);
		glVertex2f(90, 50);
	glEnd();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    movimentaQuadrado();

    glBegin(GL_QUADS);
        glVertex2f(0, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 0);
        glVertex2f(0, 0);
    glEnd();
    glPopMatrix();

	desenhaCasa();

    glLoadIdentity();
    glTranslatef(rfx, rfy, 0);
    scale2D(0.02, 0.02, 3, 1);
    rotate2D(0.5);
    glTranslatef(-rfx, -rfy, 0);

    glutPostRedisplay();
	glutSwapBuffers();
}

void movimentaQuadrado() {
    ty += 1;
    glTranslatef(0, ty, 0);
}

void rotate2D(GLfloat rotangle){
    if (angle >= 360)
        angle = 0;
    angle += rotangle;
    glRotatef(angle, 0, 0, 1);
}

void scale2D(GLfloat incx, GLfloat incy, GLfloat maxsx, GLfloat minsx){
    if (increasing == true){
        sx += incx;
        sy += incy;
        if (sx >= maxsx)
            increasing = false;
    }else{
        sx -= incx;
        sy -= incy;
        if (sx <= minsx)
            increasing = true;
    }
    glScalef(sx, sy, 0);
}