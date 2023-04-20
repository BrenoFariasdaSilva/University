#include <cstring>
#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>

class wcPt2D {
	public: GLfloat x, y;
	public: bool point = false;
	public: bool lines = false;
	public: bool triangle = false;
	public: bool square = false;
	public: int numberOfVerts = 0;
};

void translatePolygon(wcPt2D* verts, GLint nVerts, GLfloat tx, GLfloat ty) {
	for (int i = 0; i < nVerts; i++) {
		verts[i].x += tx;
		verts[i].y += ty;
	}

	glFlush();

	if (verts[0].point == true) {
		glBegin(GL_POINT);
	}

	if (verts[0].lines == true) {
		glBegin(GL_LINE);
	} 
	else if (verts[0].triangle == true) {
		glBegin(GL_TRIANGLES);
	}
	else if (verts[0].square == true) {
		glBegin(GL_QUADS);
	}

	for (int i = 0; i < nVerts; i++) {
		glColor3ub(255, 0, 0);
		glVertex2i(verts[i].x, verts[i].y);
	}
      
	glEnd();
}

int init(void) {
	// Define a cor do fundo
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Carrega a matriz de projeção
	glMatrixMode(GL_PROJECTION);

	// Define projeção ortgonal 2D
	gluOrtho2D(0.0, 200.0, 0.0, 200.0); // gluOrtho2D(XMIN, YMIN, XMAX, YMAX);
	return 0;
}

void display(void) { // Função callback chamada para desenho
	// Desenha o fundo (Limpa a janela)
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera o atributo de cor
	glColor3ub(0, 255, 255);

	// Desenha um triangulo
	glBegin(GL_TRIANGLES);
		glColor3ub(255, 255, 255);
		glVertex2i(25, 25);

		glColor3ub(255, 255, 255);
		glVertex2i(100, 150);

		glColor3ub(255, 255, 255);
		glVertex2i(175, 25);

	glEnd();

	wcPt2D objectVar[3];
	objectVar[0].x = 25;
	objectVar[0].y = 25;
	objectVar[0].triangle = true;
	objectVar[0].numberOfVerts = 3;
	objectVar[1].x = 100;
	objectVar[1].y = 150;
	objectVar[2].x = 175;
	objectVar[2].y = 25;

	translatePolygon(objectVar, objectVar[0].numberOfVerts, 15.0, 15.0);

	// Esvazia o buffer, enviando todos os comandos emitidos até o momento para a GPU, sem esperar pelo render
	glFlush();
}

int main (int argc, char** argv) {
	glutInit(&argc, argv); // Inicializa o GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define o modo de display
	glutInitWindowPosition(200, 0); // Posição inicial da janela
	glutInitWindowSize(400, 300); // Largura e altura da janela

	glutCreateWindow("Exemplo de programa em OpenGL"); // Cria a janela de exibindo

	init(); // Chama a função de inicialização

	// 
	glutDisplayFunc(display);

	// 
	glutMainLoop();
	return 0;
}