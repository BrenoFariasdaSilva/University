// Faça uma animação que simule o sistema solar contendo o Sol, a
// Terra e a Lua, sabendo que:
// ■ A Terra faz um giro completo ao redor do Sol em 365 dias (não considere anos bissextos);
// ■ A Lua gira completamente em torno de si mesma e em torno da Terra em 28 dias.
// ■ O Sol gira em torno do seu eixo em 27 dias.

#include <stdio.h>
#include <GL/glut.h>

// Variaveis globais
float anguloTerra = 0.0;
float anguloLua = 0.0;
float anguloSol = 0.0;

// Funcao callback chamada para fazer o desenho


void Timer(int value){

    anguloTerra += 0.1*100;
    anguloLua += 0.5*100;
    anguloSol += 0.01*100;


    // atualiza a cena após a modificação dos objetos
    glutPostRedisplay();
    // chama a própria função para continuar animando os objetos
    glutTimerFunc(40, Timer, 1);

}

int init(void){
    glClearColor(0, 0, 0, 0); // define a cor de fundo
    // define que a matriz é a de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // carrega a matriz identidade
    glOrtho(-5, 5, -5, 5, -5, 5); // define uma projeção ortográfica
}

void display(void){
    //limpa o buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(  0.0,1.0,0.0,    // posição da câmera
                0.0,0.0,0.0,    // para onde a câmera aponta
                1.0,0.0,0.0);   // vetor view-up

    


    glColor4f(1.0, 1.0, 0.0, 1.0);      // define a cor do objeto
    glRotatef(anguloSol, 0.0, 1.0, 0.0); // rotaciona o objeto
    glutWireSphere(1,20,20);            // desenha o Sol

    glColor4f(0.0, 0.0, 1.0, 1.0);      // define a cor do objeto
    glTranslatef(4,0,0);                // translada a Terra
    glRotatef(anguloTerra, 0.0, 1.0, 0.0); // rotaciona a Terra
    glutWireSphere(0.5,10,10);          // desenha a Terra

    glColor4f (0.81, 0.78, 0.79, 1.0);  // define a cor do objeto
    glTranslatef(1.0,0.0,0.0);          // translada a Lua
    glRotatef(anguloLua, 0.0, 1.0, 0.0); // rotaciona a Lua
    glutWireSphere(0.2,5,5);            // desenha a Lua

    glutSwapBuffers();                  // troca os buffers
}

int main(int argc, char** argv){
    glutInit(&argc,argv); //inicializa o GLUT
    //configura o modo de display
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //seta a posição inicial da janela
    glutInitWindowPosition(200,0);
    //configura a largura e altura da janela de exibição
    glutInitWindowSize(800,800);
    //cria a janela de exibição
    glutCreateWindow("Sistema Solar");
    init(); //executa função de inicialização
    glutDisplayFunc(display);
    glutTimerFunc(40, Timer, 1);
    glutMainLoop(); //mostre tudo e espere
    return 0;
}