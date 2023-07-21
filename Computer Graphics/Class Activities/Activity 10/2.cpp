#include <GL/freeglut.h>
int init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(1.0, 0.5, 0.5, //posição da câmera
    0.0, 0.0, 0.0, //para onde a câmera aponta
    0.0, 1.0, 0.0); //vetor view-up
    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    //define uma projeção ortogonal
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.25, 2.5);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a de modelo
    glColor3f(1.0f, 0.0f, 0.0f); //desenha um cubo
    glutWireCube(1.0f);
    glFlush(); //força o desenho das primitivas
}

int main(int argc, char** argv){
    glutInit(&argc,argv); //inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB); //configura o modo de
    //display
    glutInitWindowPosition(200,0); //seta a posição inicial da janela
    glutInitWindowSize(500,500); //configura a largura e altura da
    // janela de exibição
    //cria a janela de exibição
    glutCreateWindow("Exemplo 2 – Transformação de Visão");
    init(); //executa função de inicialização
    glutDisplayFunc(display);
    glutMainLoop(); //mostre tudo e espere
    return 0;
}