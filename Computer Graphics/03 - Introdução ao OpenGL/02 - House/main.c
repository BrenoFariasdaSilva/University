#include <stdio.h>
#include <GL/glut.h>

int init(void) {
    // Define a cor do fundo
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Carrega a matriz de projeção
    glMatrixMode(GL_PROJECTION);

    // Define projeção ortgonal 2D
    gluOrtho2D(0.0, 200.0, 0.0, 200.0); // gluOrtho2D(XMIN, YMIN, XMAX, YMAX);
    return 0;
}

void display(void) {
    // Desenha o fundo (Limpa a janela)
    glClear(GL_COLOR_BUFFER_BIT);

    // Altera o atributo de cor
    glColor3ub(0, 255, 255);

    // Desenha a reta da esquerda
    glBegin(GL_LINES);
        glColor3ub(102, 204, 0);
        glVertex2i(0, 25);

        glColor3ub(102, 204, 0);
        glVertex2i(25, 25);
    glEnd();

    // Desenha uma reta da direita
    glBegin(GL_LINES);
        glColor3ub(102, 204, 0);
        glVertex2i(175, 25);

        glColor3ub(102, 204, 0);
        glVertex2i(200, 25);
    glEnd();

    // Desenha um quadrado
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 255);
        glVertex2i(25, 25);

        glColor3ub(255, 255, 255);
        glVertex2i(175, 25);

        glColor3ub(255, 255, 255);
        glVertex2i(175, 150);

        glColor3ub(255, 255, 255);
        glVertex2i(25, 150);
    glEnd();

    // Desenha um retangulo -> Porta
    glBegin(GL_QUADS);
        glColor3ub(204, 102, 0);
        glVertex2i(85, 25);

        glColor3ub(204, 102, 0);
        glVertex2i(115, 25);

        glColor3ub(204, 102, 0);
        glVertex2i(115, 100);

        glColor3ub(204, 102, 0);
        glVertex2i(85, 100);
    glEnd();

    // Desenha um quadrado -> Janela Esquerda
    glBegin(GL_QUADS);
        glColor3ub(0, 255, 255);
        glVertex2i(45, 85);

        glColor3ub(0, 255, 255);
        glVertex2i(45, 100);

        glColor3ub(0, 255, 255);
        glVertex2i(60, 100);

        glColor3ub(0, 255, 255);
        glVertex2i(60, 85);
    glEnd();

    // Desenha um quadrado -> Janela Direito
    glBegin(GL_QUADS);
        glColor3ub(0, 255, 255);
        glVertex2i(145, 85);

        glColor3ub(0, 255, 255);
        glVertex2i(145, 100);

        glColor3ub(0, 255, 255);
        glVertex2i(160, 100);

        glColor3ub(0, 255, 255);
        glVertex2i(160, 85);
    glEnd();

    // Desenha um triangulo -> Telhado
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 0, 0);
        glVertex2i(25, 150);

        glColor3ub(255, 0, 0);
        glVertex2i(100, 200);

        glColor3ub(255, 0, 0);
        glVertex2i(175, 150);
    glEnd();

    // Desenha a reta da borda esquerda da casa
    glBegin(GL_LINES);
        glColor3ub(153, 76, 0);
        glVertex2i(25, 25);

        glColor3ub(153, 76, 0);
        glVertex2i(25, 150);
    glEnd();

    // Desenha a reta da borda direita da casa
    glBegin(GL_LINES);
        glColor3ub(153, 76, 0);
        glVertex2i(175, 25);

        glColor3ub(153, 76, 0);
        glVertex2i(175, 150);
    glEnd();

    // Desenha a reta do chão esquerdo da casa
    glBegin(GL_LINES);
        glColor3ub(153, 76, 0);
        glVertex2i(25, 25);

        glColor3ub(153, 76, 0);
        glVertex2i(85, 25);
    glEnd();

    // Desenha a reta do chão direito da casa
    glBegin(GL_LINES);
        glColor3ub(153, 76, 0);
        glVertex2i(115, 25);

        glColor3ub(153, 76, 0);
        glVertex2i(175, 25);
    glEnd();

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