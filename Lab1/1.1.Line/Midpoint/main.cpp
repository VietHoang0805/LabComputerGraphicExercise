#include <GL/glut.h>
#include <iostream>
#include <cmath>

// Bien toan cuc luu tru toa do cua 2 diem
int startX, startY, endX, endY;
bool isFirstClick = true;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void midpointLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int d = 2 * dy - dx;
    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);

    int x = x1;
    int y = y1;

    int xEnd = x2;

    // Ðoi x, y neu x1 > x2 de dam bao ve tu trai sang phai
    if (x1 > x2) {
        std::swap(x, xEnd);
        y = y2;
    }

    setPixel(x, y);

    while (x < xEnd) {
        if (d <= 0) {
            d += incrE;
            x++;
        } else {
            d += incrNE;
            x++;
            y += (y2 > y1) ? 1 : -1;
        }
        setPixel(x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouse(int button, int state, int mouseX, int mouseY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (isFirstClick) {
            startX = mouseX;
            startY = 480 - mouseY; // Chuyen doi toa do y tu cua so OpenGL
            isFirstClick = false;
        } else {
            endX = mouseX;
            endY = 480 - mouseY; // Chuyen doi toa do y tu cua so OpenGL
            midpointLine(startX, startY, endX, endY);
            glFlush();
            isFirstClick = true;
        }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0); // Ve doan thang mau do
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Midpoint Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

