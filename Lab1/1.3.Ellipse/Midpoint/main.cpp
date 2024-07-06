#include <GL/glut.h>
#include <iostream>
#include <cmath>

// Bien toan cuc luu tru toa do cua tam và ban kinh lon, ban kinh nho cua ellipse
int centerX, centerY, radiusX, radiusY;
bool isFirstClick = true;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawEllipsePoints(int xc, int yc, int x, int y) {
    setPixel(xc + x, yc + y);
    setPixel(xc - x, yc + y);
    setPixel(xc + x, yc - y);
    setPixel(xc - x, yc - y);
}

void midpointEllipse(int xc, int yc, int rx, int ry) {
    float dx, dy, d1, d2;
    int x, y;
    x = 0;
    y = ry;

    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    while (dx < dy) {
        drawEllipsePoints(xc, yc, x, y);
        x++;
        dx = dx + (2 * ry * ry);
        if (d1 < 0) {
            d1 = d1 + dx + (ry * ry);
        } else {
            y--;
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
         ((rx * rx) * ((y - 1) * (y - 1))) -
         (rx * rx * ry * ry);

    while (y >= 0) {
        drawEllipsePoints(xc, yc, x, y);
        y--;
        dy = dy - (2 * rx * rx);
        if (d2 > 0) {
            d2 = d2 + (rx * rx) - dy;
        } else {
            x++;
            dx = dx + (2 * ry * ry);
            d2 = d2 + dx - dy + (rx * rx);
        }
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
            radiusX = abs(dx);
            radiusY = abs(dy);
            midpointEllipse(centerX, centerY, radiusX, radiusY);
            glFlush();
            isFirstClick = true;
        }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0); // Ellipse mau do
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Midpoint Ellipse Drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

