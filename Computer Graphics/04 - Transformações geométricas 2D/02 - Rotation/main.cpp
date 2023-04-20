#include <GL/gl.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

class wcPt2D {
	public: GLfloat x, y;
	public: bool point = false;
	public: bool lines = false;
	public: bool triangle = false;
	public: bool square = false;
	public: bool radian = false;
	public: int numberOfVerts = 0;
	public: double radius = 0;
	public: double defaultAngle = 0;
};

void rotatePolygon(wcPt2D* verts, GLint nVerts, GLdouble theta) {
	GLdouble thetaRadian = theta;

	if (verts[0].radian == false) {
		thetaRadian = theta * M_PI / 180;
	}

	for (int i = 0; i < nVerts; i++) {
		GLdouble NewX = (verts[i].x * cos(thetaRadian)) - (verts[i].y * sin(thetaRadian));
		GLdouble NewY = (verts[i].x * sin(thetaRadian)) + (verts[i].y * cos(thetaRadian));

		// printf("X: %f Y: %f\n", verts[i].x, verts[i].y);
		verts[i].x = NewX;
		verts[i].y = NewY;
		// printf("NewX: %f NewY: %f\n\n", NewX, NewY);
	}

	if (verts[0].point == true) {
		glBegin(GL_POINT);
	} else if (verts[0].lines == true) {
		glBegin(GL_LINES);
	} else if (verts[0].triangle == true) {
		glBegin(GL_TRIANGLES);
	} else if (verts[0].square == true) {
		glBegin(GL_QUADS);
	} else {
		glBegin(GL_POLYGON);
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

	double degreeTheta = 30.0; //  in Degrees

	wcPt2D objectVar[3];
	objectVar[0].triangle = true;
	objectVar[0].numberOfVerts = 3;
	objectVar[0].defaultAngle = 0.0;
	objectVar[0].radian = false;
	objectVar[0].x = 25;
	objectVar[0].y = 25;
	objectVar[1].x = 100;
	objectVar[1].y = 150;
	objectVar[2].x = 175;
	objectVar[2].y = 25;

	rotatePolygon(objectVar, objectVar[0].numberOfVerts, degreeTheta);

	// Esvazia o buffer, enviando todos os comandos emitidos até o momento para a GPU, sem esperar pelo render
	glFlush();
}

int main (int argc, char** argv) {
	glutInit(&argc, argv); // Inicializa o GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define o modo de display
	glutInitWindowPosition(200, 0); // Posição inicial da janela
	glutInitWindowSize(400, 400); // Largura e altura da janela

	glutCreateWindow("Exemplo de programa em OpenGL"); // Cria a janela de exibindo

	init(); // Chama a função de inicialização

	// Registra a função callback de desenho
	glutDisplayFunc(display);

	// Inicia o programa
	glutMainLoop();
	return 0;
}