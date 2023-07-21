#include <stdio.h>
#include <GL/glut.h>

int init(void);
void display(void);
void desenhaCasa(void);

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,0); // posição da janela
    glutInitWindowSize(400,300); // largura e altura da janela
    glutCreateWindow("Escala com Ponto Fixo"); // cria a janela
    init(); // executa função de inicialização
    glutDisplayFunc(display); // função "display" como a função de
    // callback de exibição
    glutMainLoop(); // mostre tudo e espere
    return 0;
}

int init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0); // define a cor de fundo
    glMatrixMode(GL_PROJECTION);    // carrega a matriz de projeção
    gluOrtho2D(0, 200, 0, 150);     // define projeção ortogonal 2D que
                                    // mapeia objetos da coordenada do
                                    // mundo para coordenadas da tela
    return 0;
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
    glColor3f(1.0f, 0.0f, 0.0f);    // desenha objetos com a cor vermelha
    glMatrixMode(GL_MODELVIEW);     // carrega a matriz de modelo
                                    // utiliza o primeiro vértice da lista como ponto fixo
    
    glLoadIdentity();               // Zera a matriz de transformação

    glTranslatef(110, 50, 0);       // ponto fixo para a posição original
    glScalef(2.0, 2.0, 1.0);        // faz a escala
    glTranslatef(-110, -50, 0);     // ponto fixo para a origem
    desenhaCasa();
    glFlush();                      // desenha os comandos não executados
}