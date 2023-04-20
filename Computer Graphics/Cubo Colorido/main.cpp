#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

// Constantes
#define FACE_CUBE 50 // Antes era 20
#define FACES 6
#define VERTEX 4
#define DIMENSIONS 3

// Variáveis globais
int last_x = 0, last_y = 0;
int angulo_x = 0, angulo_y = 0;
bool depth = false;

int face_color[FACES][DIMENSIONS] = {0};
int cube[FACES][VERTEX][DIMENSIONS] = {
	{ // Frente
		{FACE_CUBE, FACE_CUBE, -FACE_CUBE},
		{-FACE_CUBE, FACE_CUBE, -FACE_CUBE},
		{-FACE_CUBE, -FACE_CUBE, -FACE_CUBE},
		{FACE_CUBE, -FACE_CUBE, -FACE_CUBE},
	},
	{ // Direito
		{-FACE_CUBE, FACE_CUBE, -FACE_CUBE},
		{-FACE_CUBE, -FACE_CUBE, -FACE_CUBE},
		{-FACE_CUBE, -FACE_CUBE, FACE_CUBE},
		{-FACE_CUBE, FACE_CUBE, FACE_CUBE},
	},
	{ // Trás
		{FACE_CUBE, FACE_CUBE, FACE_CUBE},
		{-FACE_CUBE, FACE_CUBE, FACE_CUBE},
		{-FACE_CUBE, -FACE_CUBE, FACE_CUBE},
		{FACE_CUBE, -FACE_CUBE, FACE_CUBE},
	},
	{ // Esquerdo
		{FACE_CUBE, FACE_CUBE, FACE_CUBE},
		{FACE_CUBE, FACE_CUBE, -FACE_CUBE},
		{FACE_CUBE, -FACE_CUBE, -FACE_CUBE},
		{FACE_CUBE, -FACE_CUBE, FACE_CUBE},
	},
	{ // Topo
		{-FACE_CUBE, -FACE_CUBE, FACE_CUBE},
		{-FACE_CUBE, -FACE_CUBE, -FACE_CUBE},
		{FACE_CUBE, -FACE_CUBE, -FACE_CUBE},
		{FACE_CUBE, -FACE_CUBE, FACE_CUBE},
	},
	{ // Baixo
		{FACE_CUBE, FACE_CUBE, FACE_CUBE},
		{FACE_CUBE, FACE_CUBE, -FACE_CUBE},
		{-FACE_CUBE, FACE_CUBE, -FACE_CUBE},
		{-FACE_CUBE, FACE_CUBE, FACE_CUBE},
	},
};

// Protótipos
void init(void);
void display(void);
void gerenciaMovimento(int x_atual, int y_atual);
void gerenciaMouse(int button, int state, int x, int y); 
void keyboardKeys(unsigned char keyboard_key, int x, int y);
void generateCubeColors();
void desenhaCubo(void);

// Função principal
int main (int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
		glutInitWindowSize(400, 400);
		glutInitWindowPosition(200, 0);
		glutCreateWindow("Cubo Colorido");
		generateCubeColors();
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboardKeys);
		glutMouseFunc(gerenciaMouse);
		glutMotionFunc(gerenciaMovimento);
		init();
		glutMainLoop();
		return 0;
}

// Funções Auxiliares
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0); // Cor de fundo da janela que é branco
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
	glEnable(depth);
}

void display(void) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	desenhaCubo();
	glutSwapBuffers();
}

void gerenciaMovimento(int x_atual, int y_atual) {
	angulo_x += x_atual - last_x;
	angulo_y += y_atual - last_y;
	last_x = x_atual;
	last_y = y_atual;
	glutPostRedisplay();
}

void gerenciaMouse(int button, int state, int x, int y) {
	if (!state) {
		last_x = x;
		last_y = y;
	}
}

void keyboardKeys(unsigned char keyboard_key, int x, int y) {
	if (keyboard_key == 'p') {
		if (!depth)
			glEnable(depth);
		else
			glDisable(depth);

		depth = !depth;
		glutPostRedisplay();
	}
}

void generateCubeColors() {
	int last_color = 0;
	for (int i = 0; i < FACES; i++) {
		int color = rand() % 3;
		while (color == last_color) {
			color = rand() % 3;
		}
		last_color = color;
		for (int j = 0; j < VERTEX; j++) {
			face_color[i][color] = rand() % 256;
		}
	}
}

void desenhaCubo(void) {
	glRotatef(angulo_x, 0, 1, 0);
	glRotatef(angulo_y, 1, 0, 0);
	for (int i = 0; i < FACES; i++) {
		glBegin(GL_POLYGON);
			glColor3ub(face_color[i][0], face_color[i][1], face_color[i][2]);
			for (int j = 0; j < VERTEX; j++) {
				glVertex3f(cube[i][j][0], cube[i][j][1], cube[i][j][2]);
			}
		glEnd();
	}
}