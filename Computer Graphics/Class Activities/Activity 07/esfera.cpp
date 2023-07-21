// Crie um programa em que seja desenhado uma esfera e um plano. O usuário poderá interagir com os objetos da seguinte forma:
// - Ao pressionar as teclas direcionais, os objetos deverão ser rotacionados;
// - Ao pressionar as teclas Page Up ou Page Down, os objetos devem ser ampliados ou reduzidos, respectivamente (zoom-in e zoom-out).

#include <stdio.h>
#include <GL/glut.h>

void keyPressed_special(int key, int x, int y);
GLfloat angle_x = 0.0f;
GLfloat angle_y = 0.0f;
GLfloat scale = 1.0f;
GLfloat rx = 0, ry = 0, rz = 0;
GLfloat sx, sy, sz;



int init(void){
    glClearColor(0, 0, 0, 0); // define a cor de fundo
    glEnable(GL_DEPTH_TEST); // remoção de superfície oculta
    // define que a matriz é a de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // carrega a matriz identidade
    glOrtho(-5, 5, -5, 5, -5, 5); // define uma projeção ortográfica

    return 0;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // define que a matriz é a de modelo

    glLoadIdentity(); // carrega a matriz identidade
    glColor3f(1, 1, 0);

    glScalef(scale, scale, scale);
    glRotatef(angle_x, 1, 0, 0);
    glRotatef(angle_y, 0, 1, 0);

    //desenha esfera wired (raio, slices, stacks)
    glutWireSphere(1.0f, 20, 20);
    glColor3f(0, 0, 1);
    glTranslatef(0, -1, 0);
    glScalef(4, 0.1f, 4);
    glutSolidCube(1.0f); //desenha cubo sólido (tamanho do lado)

    glutPostRedisplay();
    glFlush(); // desenha os comandos não executados
}

int main(int argc, char** argv){
    glutInit(&argc,argv); //inicializa o GLUT
    //configura o modo de display
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,0); //seta a posição inicial da janela
    glutInitWindowSize(400,400); //largura e altura da janela
    glutCreateWindow("3D"); //cria a janela de exibição
    init(); //executa função de inicialização
    glutSpecialFunc(keyPressed_special);
    glutDisplayFunc(display);
    glutMainLoop(); //mostre tudo e espere
    return 0;
}

void keyPressed_special(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            angle_x += 5.0f;
            break;
        case GLUT_KEY_DOWN:
            angle_x -= 5.0f;;
            break;
        case GLUT_KEY_LEFT:
            angle_y += 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            angle_y -= 5.0f;
            break;
        case GLUT_KEY_PAGE_UP:
            scale += 0.1f;
            break;
        case GLUT_KEY_PAGE_DOWN:
            scale -= 0.1f;
            break;
    }
    
}

