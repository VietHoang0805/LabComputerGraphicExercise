#include <GL/glut.h>
#include <iostream>
#include <cmath>

// BBien toan cuc luu tru toa do ban kinh duong tron
int centerX, centerY, radius;
bool isFirstClick = true;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawCirclePoints(int xc, int yc, int x, int y) {
    setPixel(xc + x, yc + y);
    setPixel(xc - x, yc + y);
    setPixel(xc + x, yc - y);
    setPixel(xc - x, yc - y);
    setPixel(xc + y, yc + x);
    setPixel(xc - y, yc + x);
    setPixel(xc + y, yc - x);
    setPixel(xc - y, yc - x);
}

void bresenhamCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    drawCirclePoints(xc, yc, x, y);

    while (y >= x) {
        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }

        drawCirclePoints(xc, yc, x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouse(int button, int state, int mouseX, int mouseY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (isFirstClick) {
            centerX = mouseX;
            centerY = 480 - mouseY; // Chuy?n d?i t?a d? y t? c?a s? OpenGL
            isFirstClick = false;
        } else {
            int dx = mouseX - centerX;
            int dy = (480 - mouseY) - centerY;
            radius = sqrt(dx * dx + dy * dy);
            bresenhamCircle(centerX, centerY, radius);
            glFlush();
            isFirstClick = true;
        }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0); // Duong tron mau do
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bresenham Circle Drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

