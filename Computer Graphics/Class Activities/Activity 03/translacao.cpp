// #include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

class wcPt2D {
     public: GLfloat x, y;
};

void translatePolygon(wcPt2D* verts, GLint nVerts, GLfloat tx, GLfloat ty){

    for (int i = 0; i < nVerts; i++)
    {
        verts[i].x = verts[i].x + tx;
        verts[i].y = verts[i].y + ty;
    }

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

    translatePolygon(vertices, 3, 40, 50);

    glBegin(GL_TRIANGLES);
        glColor3ub(0, 255, 0);
        glVertex2i(vertices[0].x, vertices[0].y);

        glColor3ub(255, 0, 0);
        glVertex2i(vertices[1].x, vertices[1].y);

        glColor3ub(0, 0, 255);
        glVertex2i(vertices[2].x, vertices[2].y);
    glEnd();

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
