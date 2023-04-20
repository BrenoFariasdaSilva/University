#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constantes
#define pontos 10

// Protótipos
void init(void);
void display(void);

// Função principal
int main (int argc, char** argv) {
	glutInit(&argc, argv); // Inicializa a GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Define o modo de exibição
	glutInitWindowSize(400, 400); // Define o tamanho da janela
	glutInitWindowPosition(200, 0); // Define a posição da janela
	glutCreateWindow("Estrela N Pontas"); // Cria a janela
	glutDisplayFunc(display); // Define a função de exibição
	init(); // Executa a função init
	glutMainLoop(); // Inicia o loop de exibição
	return 0;
}

// Funções auxiliares
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0); // Define a cor de fundo da tela, que é preta
	glMatrixMode(GL_PROJECTION); // Define a matriz de projeção
	gluOrtho2D(0, 200, 0, 200); // Define a área de visualização
}

void display(void) {
	int ponto_externo = 90 - 360 / pontos; // Calcula o ângulo do primeiro ponto externo que é 90 graus menos o ângulo de cada ponto
	int ponto_interno = ((ponto_externo + 90) / 2) + 1;  // Calcula o ângulo do primeiro ponto interno que é a metade do ângulo entre o primeiro ponto externo e o segundo ponto externo
	const int centroX = 100, centroY = 100; // Define o centro da estrela
	
	glClear(GL_COLOR_BUFFER_BIT); // Limpa a tela com a cor de fundo

	glBegin(GL_LINE_LOOP); // Uso do GL_LINE_LOOP para desenhar a estrela pois o GL_LINES não conecta os pontos
		glColor3f(1.0, 0.0, 0.0);  // Cor vermelha
		for (int i = 0; i <= 360; i+= (360 / (pontos * 2))) { // Loop para desenhar a estrela
			// int ponto_externo_x = centroX + 50 * cos(ponto_externo * (M_PI / 180)); // Calcula a posição x do ponto externo
			// int ponto_externo_y = centroY + 50 * sin(ponto_externo * (M_PI / 180)); // Calcula a posição y do ponto externo
			// int ponto_interno_x = centroX + 20 * cos(ponto_interno * (M_PI / 180)); // Calcula a posição x do ponto interno
			// int ponto_interno_y = centroY + 20 * sin(ponto_interno * (M_PI / 180)); // Calcula a posição y do ponto interno

			// glVertex2i(ponto_externo_x, ponto_externo_y); // Desenha os pontos da estrela
			// glVertex2i(ponto_interno_x, ponto_interno_y); // Desenha os pontos da estrela

			// ponto_interno += delta; // Incrementa o ângulo do ponto interno
			// ponto_externo += delta; // Incrementa o ângulo do ponto externo
			glVertex2f(centroX + 50 * cos(ponto_externo * M_PI / 180), centroY + 50 * sin(ponto_externo * M_PI / 180)); // Desenha o ponto externo
			glVertex2f(centroX + 25 * cos(ponto_interno * M_PI / 180), centroY + 25 * sin(ponto_interno * M_PI / 180)); // Desenha o ponto interno
			ponto_externo += 360 / pontos; // Incrementa o ângulo do ponto externo
			ponto_interno += 360 / pontos; // Incrementa o ângulo do ponto interno
		}	
	glEnd(); // Fim do desenho
	glFlush(); // Executa os comandos OpenGL
}