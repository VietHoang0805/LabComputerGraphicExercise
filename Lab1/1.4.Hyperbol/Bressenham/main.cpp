#include <GL/glut.h>
#include <iostream>
#include <cmath>

void print_pixel(int x, int y, int x1, int y1)
{
    glVertex2i(x1 + x, y1 + y);
    glVertex2i(x1 + x, y1 - y);
    glVertex2i(x1 - x, y1 - y);
    glVertex2i(x1 - x, y1 + y);
}

void print_hyperbola_bresenham(int x1, int y1, int a, int b)
{
    int x = a, y = 0;
    int d = 2 * a * a - 2 * a * b * b - b * b;

    glBegin(GL_POINTS);
    while (y <= b * b * x / (a * a))
    {
        print_pixel(x, y, x1, y1);
        if (d < 0)
        {
            d += 2 * a * a * (2 * y + 3);
        }
        else
        {
            d += 2 * a * a * (2 * y + 3) - 4 * b * b * (x + 1);
            x++;
        }
        y++;
    }

    int init = 100;
    while (init--)
    {
        if (d < 0)
        {
            d += 2 * b * b * (3 + 2 * x);
        }
        else
        {
            d += 2 * b * b * (3 + 2 * x) - 4 * a * a * (y + 1);
            y++;
        }
        x++;
        print_pixel(x, y, x1, y1);
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
            print_hyperbola_bresenham(x1, y1, maj_axis, min_axis);
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
    glutCreateWindow("Hyperbola using GLUT (Bresenham)");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

