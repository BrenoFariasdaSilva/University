#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

void init();
void display();
void drawCircle();
void drawHourMarkers();

const int centerX = 100, centerY = 100;

void init(void) {
    // Define a cor do fundo
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Carrega a matriz de projeção
    glMatrixMode(GL_PROJECTION);

    // Define projeção ortgonal 2D
    gluOrtho2D(0.0, 200.0, 0.0, 200.0); // gluOrtho2D(XMIN, YMIN, XMAX, YMAX);
}

void display(void) {
    // Desenha o fundo (Limpa a janela)
    glClear(GL_COLOR_BUFFER_BIT);

    drawCircle();
    drawHourMarkers();

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

void drawCircle() {
    glLineWidth(5);
    glColor3ub(0, 0, 0);
    // Seno (Theta) = vertical {Y} / raio -> Seno (Theta) = Y / raio.
    // Cosseno (Theta) = horizontal {X} / raio -> Cosseno (Theta) = X / raio.

    float offsetX = 0, offsetY = 0; // Coordenadas do ponto
    int raio = 75; // 2 * Raio da circunferência;

    for (double i = 0; i <= 72000;) { 
        glBegin(GL_POINTS);
            double radianos = i * (M_PI / 180); // Converte para radianos
            offsetX = raio * cos(radianos); // X = Raio * Cosseno (Theta)
            offsetY = raio * sin(radianos); // Y = Raio * Seno (Theta)
            glVertex2d(centerX + offsetX, centerY + offsetY); // Ponto inicial
            i += .00250;

            radianos = i * (M_PI / 180); // Converte para radianos
            offsetX = raio * cos(radianos); // X = Raio * Cosseno (Theta)
            offsetY = raio * sin(radianos); // Y = Raio * Seno (Theta)
            glVertex2d(centerX + offsetX, centerY + offsetY); // Ponto final
            i += .00250;
        glEnd();
    }
}

// void drawHourMarkers() {
//     const double offsetBigTraces = -70;
//     const int angle = 360 / 60;

//     glTranslatef(centerX, centerY, 0); // ponto fixo para a posição original
//     glRotatef(angle, 0, 0, 0); // rotaciono
//     glTranslatef(-centerX, -centerY, 0); // ponto fixo para a origem

//     for (int i = 0; i < 60; i++) { // ToDo: Passar i para radianos
//         glColor3ub(0, 0, 0);
//         if (!(i % 5)) {
//             glLineWidth(2);
//         } else {
//             glLineWidth(1);
//         }

//         glBegin(GL_LINES);
//             glVertex2i(centerX, centerY);
//             glVertex2i(centerX, centerY + offsetBigTraces);
//         glEnd();

//         glRotatef(angle, 0, 0, 1);
//     }
// }

// void drawHourMarkers() {
//     int currentAngle = 0;
//     const int angle = 360 / 60;
//     float offsetX = 0, offsetY = 0; // Coordenadas do ponto
//     const int raio = 75; // 2 * Raio da circunferência;


//     for (int i = 0; i <= 60; i++) { 
//         if (!(i % 5)) {
//             glLineWidth(2);
//         } else {
//             glLineWidth(1);
//         }

//         glColor3ub(0, 0, 0);
//         glBegin(GL_LINES);
//             double radianos = currentAngle * (M_PI / 180); // Converte para radianos
//             // offsetX = raio * cos(radianos); // X = Raio * Cosseno (Theta)
//             // offsetY = raio * sin(radianos); // Y = Raio * Seno (Theta)
//             glVertex2d(centerX, centerY); // Ponto inicial

//             // radianos = i * (M_PI / 180); // Converte para radianos
//             offsetX = raio * cos(radianos); // X = Raio * Cosseno (Theta)
//             offsetY = raio * sin(radianos); // Y = Raio * Seno (Theta)
//             glVertex2d(centerX + offsetX, centerY + offsetY); // Ponto final
//             currentAngle += angle;
//             glLoadIdentity();
//             glScalef(0.1, 0.1, 0);
//         glEnd();

//         // glColor3ub(255, 255, 255);
//         // glBegin(GL_LINES);
//         //     // offsetX = raio * cos(radianos); // X = Raio * Cosseno (Theta)
//         //     // offsetY = raio * sin(radianos); // Y = Raio * Seno (Theta)
//         //     glVertex2d(centerX, centerY); // Ponto inicial

//         //     // radianos = i * (M_PI / 180); // Converte para radianos
//         //     glVertex2d(centerX + offsetX, centerY + offsetY + 10); // Ponto final
//         // glEnd();

//         // glTranslatef(centerX, centerY, 0); // ponto fixo para a posição original
//         // glTranslatef(-centerX, -centerY, 0); // ponto fixo para a origem
//     }
// }

void drawHourMarkers() {
    int currentAngle = 0;
    const int angle = 360 / 60;
    float offsetX = 0, offsetY = 0; // Coordenadas do ponto
    const int raio = 75; // 2 * Raio da circunferência;


    for (int i = 0; i <= 60; i++) { 
        if (!(i % 5)) {
            glLineWidth(2);
        } else {
            glLineWidth(1);
        }

        glColor3ub(0, 0, 0);
        glBegin(GL_LINES);
            double radianos = currentAngle * (M_PI / 180); // Converte para radianos
            // offsetX = raio * cos(radianos); // X = Raio * Cosseno (Theta)
            // offsetY = raio * sin(radianos); // Y = Raio * Seno (Theta)
            glVertex2d(25, 35); // Ponto inicial

            // radianos = i * (M_PI / 180); // Converte para radianos
            offsetX = raio * cos(radianos); // X = Raio * Cosseno (Theta)
            offsetY = raio * sin(radianos); // Y = Raio * Seno (Theta)
            glVertex2d(centerX + offsetX, centerY + offsetY); // Ponto final
            currentAngle += angle;
            glLoadIdentity();
            glTranslatef(centerX, centerY, 0); // ponto fixo para a posição original
            glRotatef(currentAngle, 0, 0, 1); 
            glTranslatef(-centerX, -centerY, 0); // ponto fixo para a origem
        glEnd();
    }
}