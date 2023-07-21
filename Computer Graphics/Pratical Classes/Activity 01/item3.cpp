#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

int init();
void display();
void desenhaCasa();
void transformObject();
void rotate2D(GLfloat rotangle);
void scale2D(GLfloat incx, GLfloat incy, GLfloat maxx, GLfloat minx);
void movimentaObjeto(int horizontal, int vertical);
void desenhaQuadrado();
void desenhaTriangulo();
void desenhaCirculo();
void desenhaObjeto(int objeto);

GLfloat rfx, rfy, sx, sy, angle, tx, ty, objeto;
bool direita, esquerda, cima, baixo, borda;

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
    cima = true;
    esquerda = false;
    baixo = false;
    tx = 0;
    ty = 0;
    borda = false;
    objeto = rand() % 3;
    
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
    movimentaObjeto(1, 1);

    int antigoObjeto = objeto;
    if (borda){
        while(objeto == antigoObjeto){
            objeto = rand() % 3;
        }
        borda = false;
    }
    
    desenhaObjeto(objeto);

    glPopMatrix();

    glutPostRedisplay();    // chama a função display novamente
	glutSwapBuffers();      // troca os buffers
}

void desenhaObjeto(int escolha){
    if (escolha == 0){
        desenhaQuadrado();
    } else if (escolha == 1){
        desenhaTriangulo();
    } else if (escolha == 2){
        desenhaCirculo();
    }
}


void movimentaObjeto(int horizontal, int vertical){
    // Gerar 3 valores aleatorios entre 0 e 1
    float r = (float)rand()/(float)RAND_MAX;
    float g = (float)rand()/(float)RAND_MAX;
    float b = (float)rand()/(float)RAND_MAX;

    // Gerar 1 valor aleatorio inteiro entre 0 e 2
    


   // o quadrado se movimenta da posição x=0 ate x=380 e volta
    if(direita && cima){
        if(tx < 180){
            tx += horizontal;
        }else{
            glClearColor(r, g, b, 0.0);
            borda = true;
            esquerda = true;
            direita = false;
        }

        if(ty < 130){
            ty += vertical;
        }else{
            glClearColor(r, g, b, 0.0);
            borda = true;
            baixo = true;
            cima = false;
        }
    } else if(direita && baixo){
        if(tx < 180){
            tx += horizontal;
        }else{
            glClearColor(r, g, b, 0.0);
            borda = true;
            esquerda = true;
            direita = false;
        }

        if(ty > 0){
            ty -= vertical;
        }else{
            glClearColor(r, g, b, 0.0);
            borda = true;
            cima = true;
            baixo = false;
        }
    } else if(esquerda && cima){
        if(tx > 0){
            tx -= horizontal;
        }else{
            glClearColor(r, g, b, 0.0);
            borda = true;
            direita = true;
            esquerda = false;
        }

        if(ty < 130){
            ty += vertical;
        }else{
            glClearColor(r, g, b, 0.0);
            borda = true;
            baixo = true;
            cima = false;
        }
    } else if(esquerda && baixo){
        if(tx > 0){
            tx -= horizontal;
        }else{
            glClearColor(r, g, b, 0.0);
            borda = true;
            direita = true;
            esquerda = false;
        }

        if(ty > 0){
            ty -= vertical;
        }else{
            glClearColor(r, g, b, 0.0);
            borda = true;
            cima = true;
            baixo = false;
        }
    }


    glTranslatef(tx, ty, 0);

}

void desenhaQuadrado(void){
    glBegin(GL_QUADS);
        glVertex2f(0, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 0);
        glVertex2f(0, 0);
    glEnd();
}

void desenhaTriangulo(void){
    glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(10, 20);
        glVertex2f(20, 0);
    glEnd();
}

void desenhaCirculo(void){
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++){
            float degInRad = i*180.0f/3.14159f;
            glVertex2f(cos(degInRad)*10.0f + 10, sin(degInRad)*10.0f + 10);
        }
    glEnd();
}

