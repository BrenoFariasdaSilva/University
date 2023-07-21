// #include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

class wcPt2D {
     public: GLfloat x, y;
};

void scalePolygon(wcPt2D * verts, GLint nVerts, GLfloat sx, GLfloat sy, GLfloat x_ref, GLfloat y_ref){
    GLint k;
    wcPt2D* vertsEscalado = new wcPt2D;
    for(k = 0; k < nVerts; k++){
        vertsEscalado[k].x = verts[k].x * sx + x_ref*(1 - sx);
        vertsEscalado[k].y = verts[k].y * sy + y_ref*(1 - sy);
    }

    glBegin(GL_POLYGON);
        for(k = 0; k < nVerts; k++){
            glVertex2f(vertsEscalado[k].x , vertsEscalado[k].y);
        }
    glEnd();
}

int init(void){
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);

    return 0;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    
    glBegin(GL_TRIANGLES);
        glColor3ub(0, 255, 0);
        glVertex2i(30, 10);

        glColor3ub(255, 0, 0);
        glVertex2i(150, 10);

        glColor3ub(0, 0, 255);
        glVertex2i(90, 120);
    glEnd();

    wcPt2D vertices[3] = {
        {
            x: 30.0,
            y: 10.0
        },
        {
            x: 150.0,
            y: 10.0
        },
        {
            x: 90.0,
            y: 120.0
        }
    };

    scalePolygon(vertices, 3, 2, 2, 30, 10);

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(400, 300);

    glutCreateWindow("Exemplo de programa OpenGL");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
