#include <GL/freeglut.h>

GLfloat width = 600, height = 600;
GLfloat angle = 0.0f;

void gira(){
    angle += 0.5f;
    if(angle > 360.0f)
        angle = 0.0f;
    glutPostRedisplay();
}

int init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //limpa o buffer
    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view

    // Primeiro quadrante (inferior esquerdo) - sobre o eixo x
    glViewport(0, 0, width/2, height/2);
    glLoadIdentity();
    gluLookAt(
        3.0, 0.0, 0.0,  //posição da câmera
        0.0, 0.0, 0.0, //para onde a câmera está olhando
        0.0, 1.0, 0.0   //vetor up
    );
    glColor3f(1.0f, 0.0f, 0.0f);
    glutWireTeapot(1.5);

    // Segundo quadrante (superior esquerdo) - eixo z
    glViewport(0, height/2, width/2, height/2);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, 3.0,  //posição da câmera
        0.0, 0.0, 0.0, //para onde a câmera está olhando
        0.0, 1.0, 0.0   //vetor up
    );
    glutWireTeapot(1.5);

    // Terceiro quadrante (inferior direito) - sobre o eixo y
    glViewport(width/2, 0, width/2, height/2);
    glLoadIdentity();
    gluLookAt(
        0.0, 2.0, 0.0,  //posição da câmera
        0.0, 0.0, 0.0, //para onde a câmera está olhando
        0.0, 0.0, 1.0   //vetor up
    );
    glutWireTeapot(1.5);

    // Quarto quadrante (superior direito) - rotacionado
    glMatrixMode(GL_PROJECTION);
    glViewport(width/2, height/2, width/2, height/2);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 20.0);
    gluLookAt(
        0.0, 0.0, 3.0,  //posição da câmera
        0.0, -1.0, 0.0, //para onde a câmera está olhando
        0.0, 1.0, 0.0   //vetor up
    );
    glRotatef(angle, 0.0f, 1.0f, 1.0f);
    glutWireTeapot(1.5);


    
    glutSwapBuffers();			//força o desenho das primitivas
}

int main(int argc, char** argv){
    glutInit(&argc,argv);                       //inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //configura o modo de
												 //display
    glutInitWindowPosition(300,0);     //seta a posição inicial da janela
    glutInitWindowSize(width,height);       //configura a largura e altura da
									   // janela de exibição
	//cria a janela de exibição
    glutCreateWindow("Exercício 1 – Viewports múltiplas");

    init();                           //executa função de inicialização
    glutDisplayFunc(display);
    glutIdleFunc(gira);               //executa a função enquanto o programa está ocioso
    glutMainLoop();                   //mostre tudo e espere
    return 0;
}



