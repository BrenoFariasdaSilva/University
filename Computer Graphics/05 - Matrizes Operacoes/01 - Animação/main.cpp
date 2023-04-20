#include <cstring>
#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>

GLfloat angle = 0, fx = 100, fy = 65;

void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0); // define a cor de fundo
	glMatrixMode(GL_PROJECTION); // carrega a matriz de projeção
	gluOrtho2D(0, 200, 0, 150); // define projeção ortogonal 2D que
	// mapeia objetos da coordenada do
	// mundo para coordenadas da tela
}

void desenhaCasa(void){
	glBegin(GL_POLYGON); // desenha uma casa
	glVertex2f(110, 50);
	glVertex2f(110, 70);
	glVertex2f(100, 80);
	glVertex2f(90, 70);
	glVertex2f(90, 50);
	glEnd();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); // desenha objetos com a cor vermelha
	glMatrixMode(GL_MODELVIEW); // carrega a matriz de modelo

	glLoadIdentity(); // Carrega a matriz identidade

	// utiliza o primeiro vértice da lista como ponto fixo
	glTranslatef(fx, fy, 0); // ponto fixo para a posição original
	glScalef(2.0, 2.0, 1.0); // faz a escala
	glRotatef(angle, 0, 0 ,1);
	glTranslatef(-fx, -fy, 0); // ponto fixo para a origem
	// As operações são feitas de baixo para cima: glTranslatef -> glScalef -> glTranslatef.
	desenhaCasa();

	glutPostRedisplay(); // Atualiza a imagem após a atualização de parametros

	glutSwapBuffers(); // desenha os comandos não executados
}

void rotate2D() {
	angle += 6;
	if (angle >= 360) {
		angle = 0;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(200,0); // posição da janela
	glutInitWindowSize(400,300); // largura e altura da janela
	glutCreateWindow("Escala com Ponto Fixo"); // cria a janela

	init(); // executa função de inicialização

	glutDisplayFunc(display); // função "display" como a função de

	glutIdleFunc(rotate2D);
	// glutIdleFunc(rotateResize3D);

	// callback de exibição
	glutMainLoop(); // mostre tudo e espere

	return 0;
}