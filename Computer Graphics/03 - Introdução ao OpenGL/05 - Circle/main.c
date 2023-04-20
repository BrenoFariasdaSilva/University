#include <stdio.h>
#include <math.h>
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

    glColor3ub(10, 149, 255); // Cor da linha - Azul Ciano

    float offsetX = 0, offsetY = 0; // Coordenadas do ponto
    int hipotenusa = 75; // Raio da circunferência;
    int origemX = 100; // Centro X
    int origemY = 100; // Centro Y

    // Seno (Theta) = vertical {Y} / hipotenusa -> Seno (Theta) = Y / hipotenusa.
    // Cosseno (Theta) = horizontal {X} / hipotenusa -> Cosseno (Theta) = X / hipotenusa.

    for (double i = 0; i <= 72000;){ // ToDo: Passar i para radianos
        glBegin(GL_POINTS);
            double radianos = i * (M_PI / 180); // Converte para radianos
            offsetX = hipotenusa * cos(radianos); // X = Raio * Cosseno (Theta)
            offsetY = hipotenusa * sin(radianos); // Y = Raio * Seno (Theta)
            glVertex2d(origemX + offsetX, origemY + offsetY); // Ponto inicial
            i += .00250;

            radianos = i * (M_PI / 180); // Converte para radianos
            offsetX = hipotenusa * cos(radianos); // X = Raio * Cosseno (Theta)
            offsetY = hipotenusa * sin(radianos); // Y = Raio * Seno (Theta)
            glVertex2d(origemX + offsetX, origemY + offsetY); // Ponto final
            i += .00250;
        glEnd();
    }

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

    // Registra a função de callback de desenho
    glutDisplayFunc(display);

    // Inicia o loop de eventos
    glutMainLoop();
    
    return 0;
}