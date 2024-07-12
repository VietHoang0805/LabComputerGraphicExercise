#include <GL/glut.h>
#include <cmath>

// �u?ng th?ng y = ax + b
float a = 1.0f, b = 0.0f;

// C�c d?nh c?a da gi�c
GLfloat vertices[][2] = {{100.0f, 100.0f}, {200.0f, 100.0f}, {200.0f, 200.0f}, {100.0f, 200.0f}};

// H�m v? tr?c t?a d? Oxy
void drawAxes() {
    glColor3f(0.0f, 0.0f, 0.0f); // M�u den
    glBegin(GL_LINES);
    // Tr?c X
    glVertex2f(-300.0f, 0.0f);
    glVertex2f(300.0f, 0.0f);
    // Tr?c Y
    glVertex2f(0.0f, -300.0f);
    glVertex2f(0.0f, 300.0f);
    glEnd();
}

// H�m v? du?ng th?ng y = ax + b
void drawLine() {
    glColor3f(0.0f, 0.0f, 1.0f); // M�u xanh
    glBegin(GL_LINES);
    glVertex2f(-300.0f, a * (-300.0f) + b);
    glVertex2f(300.0f, a * 300.0f + b);
    glEnd();
}

// H�m d?i x?ng qua du?ng th?ng y = ax + b
void reflect(float& x, float& y, float a, float b) {
    float d = (x + (y - b) * a) / (1 + a * a);
    x = 2 * d - x;
    y = 2 * d * a - y + 2 * b;
}

// H�m v? da gi�c sau khi d?i x?ng
void drawReflectedPolygon() {
    glColor3f(1.0f, 0.0f, 0.0f); // M�u d?
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; ++i) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        reflect(x, y, a, b);
        glVertex2f(x, y);
    }
    glEnd();
}

// H�m v? da gi�c g?c
void drawPolygon() {
    glColor3f(0.0f, 1.0f, 0.0f); // M�u xanh l�
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; ++i) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

// H�m hi?n th?
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();               // V? tr?c t?a d?
    drawLine();               // V? du?ng th?ng y = ax + b
    drawPolygon();            // V? da gi�c g?c
    drawReflectedPolygon();   // V? da gi�c sau khi d?i x?ng

    glFlush();
}

// H�m x? l� s? ki?n chu?t
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Chuy?n d?i t?a d? c?a s? th�nh t?a d? OpenGL
        float x0 = (float)(x - 300);
        float y0 = (float)(300 - y);

        // C?p nh?t du?ng th?ng y = ax + b v?i di?m nh?p chu?t
        b = y0 - a * x0;

        glutPostRedisplay();
    }
}

// H�m kh?i t?o
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // M�u n?n tr?ng
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300.0f, 300.0f, -300.0f, 300.0f); // H? t?a d? 2D
}

// H�m main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Reflection across Line y=ax+b");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}

