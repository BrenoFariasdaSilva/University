#include <stdio.h>
#include <GL/glut.h>
#include <iostream>

int init();
void display();
void desenhaCasa();
void transformObject();
void rotate2D(GLfloat rotangle);
void scale2D(GLfloat incx, GLfloat incy, GLfloat maxx, GLfloat minx);
void movimentaQuadrado();
void desenhaQuadrado();

GLfloat rfx, rfy, sx, sy, angle, tx;
bool direita;

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
    direita = true;
    
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
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);


    glPushMatrix();

    glLoadIdentity();
    movimentaQuadrado();
    desenhaQuadrado();

    glPopMatrix();

    glutPostRedisplay();    // chama a função display novamente
	glutSwapBuffers();      // troca os buffers
}




void movimentaQuadrado(void){
   // o quadrado se movimenta da posição x=0 ate x=380 e volta
    if(direita){
        if(tx < 180){
            tx += 1;
        }else{
            direita = false;
        }
    }
    else{
        if(tx > 0){
            tx -= 1;
        }else{
            direita = true;
        }
    }
    glTranslatef(tx, 0, 0);



}

void desenhaQuadrado(void){
    glBegin(GL_QUADS);
        glVertex2f(0, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 0);
        glVertex2f(0, 0);
    glEnd();
}