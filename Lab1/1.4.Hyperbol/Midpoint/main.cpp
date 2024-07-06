#include <GL/glut.h>
#include <iostream>
#include <cmath>

// Luu y su dung midpoint khong ve duoc hyperbol
void print_pixel(int x, int y, int x1, int y1)
{
    glVertex2i(x1 + x, y1 + y);
    glVertex2i(x1 + x, y1 - y);
    glVertex2i(x1 - x, y1 - y);
    glVertex2i(x1 - x, y1 + y);
}

void print_hyperbola_midpoint(int x1, int y1, int a, int b)
{
    int x = 0, y = b;
    float d1 = b * b - a * a * b + 0.25 * a * a;
    glBegin(GL_POINTS);
    glVertex2i(x1 + x, y1 + y);
    glVertex2i(x1 + x, y1 - y);
    while (a * a * (y - 0.5) > b * b * (x + 1))
    {
        if (d1 < 0)
        {
            d1 += b * b * (2 * x + 3);
        }
        else
        {
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            y--;
        }
        x++;
        glVertex2i(x1 + x, y1 + y);
        glVertex2i(x1 + x, y1 - y);
        glVertex2i(x1 - x, y1 + y);
        glVertex2i(x1 - x, y1 - y);
    }

    float d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while (y > 0)
    {
        if (d2 < 0)
        {
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
        }
        else
        {
            d2 += a * a * (-2 * y + 3);
        }
        y--;
        glVertex2i(x1 + x, y1 + y);
        glVertex2i(x1 + x, y1 - y);
        glVertex2i(x1 - x, y1 + y);
        glVertex2i(x1 - x, y1 - y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    static int x1, y1, a, b, c, d;
    static bool first_click = true;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (first_click)
        {
            x1 = x - 320;
            y1 = 240 - y;
            first_click = false;
        }
        else
        {
            a = x - 320;
            b = 240 - y;
            float maj_axis = sqrt(pow((a - x1), 2) + pow((b - y1), 2));
            float min_axis = sqrt(pow((c - x1), 2) + pow((d - y1), 2));
            glBegin(GL_LINES);
            glVertex2i(-320, y1);
            glVertex2i(320, y1);
            glVertex2i(x1, -240);
            glVertex2i(x1, 240);
            glEnd();
            print_hyperbola_midpoint(x1, y1, maj_axis, min_axis);
            first_click = true;
            glFlush();
        }
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hyperbola using GLUT (Midpoint)");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

