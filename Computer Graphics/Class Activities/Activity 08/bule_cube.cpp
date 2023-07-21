// Crie um programa em OpenGL que contém dois objetos um cubo e
// um bule que estão lado a lado
// ■ Se o usuário digitar a tecla ‘1’ ele estará selecionando o cubo
// ■ Se o usuário digitar a tecla ‘2’ ele estará selecionando o bule

// Ao pressionar as teclas ← e →, o objeto selecionado será
// rotacionado nos sentidos horário e anti-horário respectivamente,
// utilizando o centroide como ponto fixo
// ■ O cubo deve sempre rotacionar em torno do eixo <1,1,1>
// ■ O bule deve sempre rotacionar em torno do eixo <1,0,1>



#include <stdio.h>
#include <GL/glut.h>

void keyPressed_special(int key, int x, int y);
void keyPressed_keyboard(unsigned char key, int x, int y);

float cube_angulo_x = 0, cube_angulo_y = 0;
float bule_angulo_x = 0, bule_angulo_y = 0;
int objeto_selecionado = 0;

int init(void){
	glClearColor(0, 0, 0, 0);		// define a cor de fundo
	glEnable(GL_DEPTH_TEST);		// remoção de superfície oculta
	// define que a matriz é a de projeção
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();				// carrega a matriz identidade
	glOrtho(-5, 5, -5, 5, -5, 5);	// define uma projeção ortográfica
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);	// define que a matriz é a de modelo
	glLoadIdentity();				// carrega a matriz identidade

	glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(3, 0, 0);
    glRotatef(bule_angulo_x, 1, 0, 0);
    glRotatef(bule_angulo_y, 0, 1, 0);
    glutWireTeapot(1.0);
    glPopMatrix();

    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-3, 0, 0);
    glRotatef(cube_angulo_x, 1, 0, 1);
    glRotatef(cube_angulo_y, 1, 0, 1);
    glutWireCube(1.0);

	glFlush();						// desenha os comandos não executados
}

int main(int argc, char** argv){
    glutInit(&argc,argv);			//inicializa o GLUT
	//configura o modo de display
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,0);	//seta a posição inicial da janela
    glutInitWindowSize(400,400); 	//largura e altura da janela
    glutCreateWindow("3D");			//cria a janela de exibição

    init();							//executa função de inicialização
    glutSpecialFunc(keyPressed_special);
    glutKeyboardFunc(keyPressed_keyboard);
    glutDisplayFunc(display);
    glutMainLoop();					//mostre tudo e espere
    return 0;
}

void keyPressed_keyboard(unsigned char key, int x, int y){
    switch(key){
        case '1':
            objeto_selecionado = 1;
            break;
        case '2':
            objeto_selecionado = 2;
            break;
    }

}

void keyPressed_special(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            if(objeto_selecionado == 1){
                cube_angulo_y -= 5;
            }else if(objeto_selecionado == 2){
                bule_angulo_y -= 5;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(objeto_selecionado == 1){
                cube_angulo_y += 5;
            }else if(objeto_selecionado == 2){
                bule_angulo_y += 5;
            }
            break;
    }
    glutPostRedisplay();
}
