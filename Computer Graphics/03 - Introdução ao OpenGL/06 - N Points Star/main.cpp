// Write a program in OpenGL that creates any 'n' pointed star. The program should be able to draw any 'n' pointed star, as long as n >= 3.

#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POLYGON);
	int n = 0;
	while (n < 3) {
		cout << "Enter the number of points: (Input must be greater than or equal to 3) \n";
		cin >> n;
	}
	float x, y, r = 0.5;
	
	// draw a star of n points
	for (int i = 0; i < n; i++) {
		x = r * cos(2 * 3.14 * i / n);
		y = r * sin(2 * 3.14 * i / n);
		glVertex2f(x, y);
	}

	glEnd();
	glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Star");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}