#include <GL/freeglut.h>
int init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(
        0.25, 0.25, 0.0,
        0.0, 0.0, -1.0,
        0.0, 1.0, 0.0
    );
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); //define uma projeção ortogonal
}
void display(){
    //limpa o buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //define que a matrix é a de modelo
    glMatrixMode(GL_MODELVIEW);
    //desenha um cubo
    glColor3f(1.0f, 0.0f, 0.0f);
    glutWireCube(1.0f);
    //força o desenho das primitivas
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc,argv); //inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB); //configura o modo de
    //display
    glutInitWindowPosition(200,0); //seta a posição inicial da janela
    glutInitWindowSize(500,500); //configura a largura e altura da
    // janela de exibição
    //cria a janela de exibição
    glutCreateWindow("Exemplo 1 - Projeção Ortogonal");
    init(); //executa função de inicialização
    glutDisplayFunc(display);
    glutMainLoop(); //mostre tudo e espere
    return 0;
}