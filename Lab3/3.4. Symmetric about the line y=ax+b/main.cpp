#include <GL/glut.h>
#include <cmath>

// Ðu?ng th?ng y = ax + b
float a = 1.0f, b = 0.0f;

// Các d?nh c?a da giác
GLfloat vertices[][2] = {{100.0f, 100.0f}, {200.0f, 100.0f}, {200.0f, 200.0f}, {100.0f, 200.0f}};

// Hàm v? tr?c t?a d? Oxy
void drawAxes() {
    glColor3f(0.0f, 0.0f, 0.0f); // Màu den
    glBegin(GL_LINES);
    // Tr?c X
    glVertex2f(-300.0f, 0.0f);
    glVertex2f(300.0f, 0.0f);
    // Tr?c Y
    glVertex2f(0.0f, -300.0f);
    glVertex2f(0.0f, 300.0f);
    glEnd();
}

// Hàm v? du?ng th?ng y = ax + b
void drawLine() {
    glColor3f(0.0f, 0.0f, 1.0f); // Màu xanh
    glBegin(GL_LINES);
    glVertex2f(-300.0f, a * (-300.0f) + b);
    glVertex2f(300.0f, a * 300.0f + b);
    glEnd();
}

// Hàm d?i x?ng qua du?ng th?ng y = ax + b
void reflect(float& x, float& y, float a, float b) {
    float d = (x + (y - b) * a) / (1 + a * a);
    x = 2 * d - x;
    y = 2 * d * a - y + 2 * b;
}

// Hàm v? da giác sau khi d?i x?ng
void drawReflectedPolygon() {
    glColor3f(1.0f, 0.0f, 0.0f); // Màu d?
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; ++i) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        reflect(x, y, a, b);
        glVertex2f(x, y);
    }
    glEnd();
}

// Hàm v? da giác g?c
void drawPolygon() {
    glColor3f(0.0f, 1.0f, 0.0f); // Màu xanh lá
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; ++i) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

// Hàm hi?n th?
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();               // V? tr?c t?a d?
    drawLine();               // V? du?ng th?ng y = ax + b
    drawPolygon();            // V? da giác g?c
    drawReflectedPolygon();   // V? da giác sau khi d?i x?ng

    glFlush();
}

// Hàm x? lý s? ki?n chu?t
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Chuy?n d?i t?a d? c?a s? thành t?a d? OpenGL
        float x0 = (float)(x - 300);
        float y0 = (float)(300 - y);

        // C?p nh?t du?ng th?ng y = ax + b v?i di?m nh?p chu?t
        b = y0 - a * x0;

        glutPostRedisplay();
    }
}

// Hàm kh?i t?o
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Màu n?n tr?ng
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300.0f, 300.0f, -300.0f, 300.0f); // H? t?a d? 2D
}

// Hàm main
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

