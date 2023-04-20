#include <stdio.h>
#include <GL/glut.h>

int init(void) {
    // Define a cor do fundo
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Carrega a matriz de projeção
    glMatrixMode(GL_PROJECTION);

    // Define projeção ortgonal 2D
    gluOrtho2D(0.0, 200.0, 0.0, 150.0); // gluOrtho2D(XMIN, YMIN, XMAX, YMAX);
    return 0;
}

void display(void) {
    // Desenha o fundo (Limpa a janela)
    glClear(GL_COLOR_BUFFER_BIT);

    // Altera o atributo de cor
    glColor3ub(0, 0, 0);

    // Desenha um triangulo
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 0, 0);
        glVertex2i(25, 25);

        glColor3ub(0, 255, 0);
        glVertex2i(100, 125);

        glColor3ub(0, 0, 255);
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