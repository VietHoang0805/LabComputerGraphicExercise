#include <GL/glut.h>

// Bi?n luu tr? h? s? t? l? và t?a d? tâm t? l?
float sx = 1.0f, sy = 1.0f;
float x0 = 0.0f, y0 = 0.0f;

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

// Hàm v? da giác sau khi t? l?
void drawPolygon() {
    glColor3f(1.0f, 0.0f, 0.0f); // Màu d?
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; ++i) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        // Tính t?a d? m?i sau khi t? l?
        float newX = x0 + sx * (x - x0);
        float newY = y0 + sy * (y - y0);
        glVertex2f(newX, newY);
    }
    glEnd();
}

// Hàm hi?n th?
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();    // V? tr?c t?a d?
    drawPolygon(); // V? da giác

    glFlush();
}

// Hàm x? lý s? ki?n phím b?m
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': sy += 0.1f; break; // Tang t? l? theo tr?c Y
        case 's': sy -= 0.1f; break; // Gi?m t? l? theo tr?c Y
        case 'a': sx -= 0.1f; break; // Gi?m t? l? theo tr?c X
        case 'd': sx += 0.1f; break; // Tang t? l? theo tr?c X
        case 27:  exit(0);    break; // Thoát chuong trình khi nh?n phím ESC
    }
    glutPostRedisplay(); // Yêu c?u v? l?i c?nh
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
    glutCreateWindow("2D Scaling with Center");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

