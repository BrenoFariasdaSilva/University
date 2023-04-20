#include <stdio.h>
#include <GL/glut.h>

void init(void){
	glClearColor(0, 0, 0, 0); // define a cor de fundo
	glEnable(GL_DEPTH_TEST); // remoção de superfície oculta
	// define que a matriz é a de projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // carrega a matriz identidade
	glOrtho(-5, 5, -5, 5, -5, 5); // define uma projeção ortográfica
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); // define que a matriz é a de modelo
	glLoadIdentity(); // carrega a matriz identidade
	glColor3f(1, 1, 0);
	//desenha esfera wired (raio, slices, stacks)
	glutWireSphere(1.0f, 2000, 2000);
	glColor3f(0, 0, 1); 
	glTranslatef(0, -1, 0);
	glScalef(4, 0.1f, 4);
	glutSolidCube(1.0f); //desenha cubo sólido (tamanho do lado)
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
	// glutSpecialFunc(keyPressed_special);
	glutDisplayFunc(display);
	glutMainLoop(); //mostre tudo e espere
	return 0;
}