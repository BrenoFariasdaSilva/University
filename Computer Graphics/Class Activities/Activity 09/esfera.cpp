// Faça um programa que desenhe uma esfera na tela. 
// Quando o usuário clicar em um ponto na janela de exibição, a esfera deverá movimentar-se até esse ponto.

// Dicas: utilize a função
// void gerenciaMouse(int button, int state, int x, int y);

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float x_esfera = 0.0;
float y_esfera = 0.0;

void gerenciaMouse(int button, int state, int x, int y) {
    // A esfera esta na origem das coordenadas x e y
    // A tela mostra as coordenadas de -100 a 100
    // Logo, para que a esfera se movimente para o ponto clicado,
    // deve-se converter as coordenadas do mouse para as coordenadas da tela
    // xW_min = -100, xW_max = 100, yW_min = -100, yW_max = 100
    // xV_min = 0, xV_max = 500, yV_min = 0, yV_max = 500
    // xW = xV * (xW_max - xW_min) / (xV_max - xV_min) + xW_min
    // yW = yV * (yW_max - yW_min) / (yV_max - yV_min) + yW_min
    // xV_max = 500, xV_min = 0, yV_max = 500, yV_min = 0
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x_esfera = x * (100.0 - (-100.0)) / (500.0 - 0.0) + (-100.0);
        y_esfera = (500 - y) * (100.0 - (-100.0)) / (500.0 - 0.0) + (-100.0);
        glutPostRedisplay();
    }
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenha a esfera
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(x_esfera, y_esfera, 0.0);
    glutWireSphere(20.0, 20, 20);

    glutSwapBuffers();

}

void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0);     //define a cor de fundo
    glMatrixMode(GL_PROJECTION);          //define que a matriz é a de projeção
    glLoadIdentity();
    glOrtho(-100,100,-100, 100,-100,100);
}




int main(int argc, char** argv){
    glutInit(&argc,argv);                           //inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);    //configura o modo de display
    glutInitWindowPosition(200,0);                  //seta a posição inicial da janela
    glutInitWindowSize(500,500);                    //configura a largura e altura da janela de exibição
    glutCreateWindow("Cubo Colorido");                 //cria a janela de exibição
    init();                                         //executa função de inicialização
    glutDisplayFunc(display);
    glutMouseFunc(gerenciaMouse);
    glutMainLoop();                                  //mostre tudo e espere
    return 0;
}
