///////////////////////////////////////////////////////////////////////////////////////////////////////
// texturedSquare.cpp
//
// This stripped-down program shows how to load both external and program-generated images as textures.
//
// Interaction:
// Press the left and right arrow keys to rotate the square.
// Press space to toggle between textures.
// Press delete to reset.
//
// Sumanta Guha
//
// Texture Credits: See ExperimenterSource/Textures/TEXTURE_CREDITS.txt
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "getBMP.h"

#define BASE 20

// Globals.
static unsigned int texture[3]; // Array of texture ids.
static unsigned char chessboard[64][64][4]; // Storage for chessboard image.
static unsigned char strippedPattern[64][64][4]; // Storage for stripped pattern image.
static float angle = 0.0; // Angle to rotate textured square.
static int id = 0; // Currently displayed texture id.
float width_tex = 0.0;
float height_tex = 0.0;
float aspect_tex = 0.0;
float X = 0.0;
float Y = 0.0;


// Load external textures.
void loadTextures()
{
	// Local storage for image data.
	imageFile *image[1];

	// Load the image.
	image[0] = getBMP("./Textures/cray2.bmp");

	width_tex = image[0]->width;
	height_tex = image[0]->height;
	aspect_tex = width_tex / height_tex;
	X = (BASE * aspect_tex)/2;
	Y = BASE/2;

	// Create texture object texture[0].
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Specify image data for currently active texture object.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
	           	 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Create 64 x 64 RGBA image of a chessboard.
void createChessboard(void)
{
	int i, j;
	for (i = 0; i < 64; i++)
		for (j = 0; j < 64; j++)
			if ((((i / 8) % 2) && ((j / 8) % 2)) || (!((i / 8) % 2) && !((j / 8) % 2)))
			{
				chessboard[i][j][0] = 0x00;
				chessboard[i][j][1] = 0x00;
				chessboard[i][j][2] = 0x00;
				chessboard[i][j][3] = 0xFF;
			}
			else
			{
				chessboard[i][j][0] = 0xDD;
				chessboard[i][j][1] = 0xDD;
				chessboard[i][j][2] = 0xDD;
				chessboard[i][j][3] = 0xFF;
			}
}

// Create 64 x 64 RGBA image of a diagonal stripped pattern.
void createstrippedPattern(void)
{
	int i, j;
	for (i = 0; i < 64; i++)
		for (j = 0; j < 64; j++)
			if ((i + j)/8 % 2 == 0)
			{
				strippedPattern[i][j][0] = 0x00;
				strippedPattern[i][j][1] = 0x00;
				strippedPattern[i][j][2] = 0x00;
				strippedPattern[i][j][3] = 0xFF;
			}
			else
			{
				strippedPattern[i][j][0] = 0xDD;
				strippedPattern[i][j][1] = 0xDD;
				strippedPattern[i][j][2] = 0xDD;
				strippedPattern[i][j][3] = 0xFF;
			}
}

// Routine to load a program-generated image as a texture.
void loadChessboardTexture()
{
	// Generate internal texture.
	createChessboard();

	// Create texture object texture[1].
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	// Specify image data for currently active texture object.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, chessboard);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void loadstrippedPatternTexture()
{
	// Generate internal texture.
	createstrippedPattern();

	// Create texture object texture[1].
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	// Specify image data for currently active texture object.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, strippedPattern);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Create texture ids.
	glGenTextures(2, texture);

	// Load external texture.
	loadTextures();

	// Load internal texture.
	loadChessboardTexture();

	loadstrippedPatternTexture();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);

	// Activate texture object.
	glBindTexture(GL_TEXTURE_2D, texture[id]);

	// Map the texture onto a square polygon.
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-X, -Y, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(X, -Y, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(X, Y, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-X, Y, 0.0);
	glEnd();

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		id++;
		if (id == 3) id = 0;
		glutPostRedisplay();
		break;
	case 127:
		angle = 0.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		angle -= 5.0;
		if (angle < 0.0) angle += 360.0;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		angle += 5.0;
		if (angle > 360.0) angle -= 360.0;
	}
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the left and right arrow keys to rotate the square." << std::endl
		<< "Press space to toggle between textures." << std::endl
		<< "Press delete to reset." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	//glutInitContextVersion(4, 3);
	//glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("texturedSquare.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
