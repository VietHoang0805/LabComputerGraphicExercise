#include <GL/glut.h>
#include <iostream>
#include <cmath>

void print_pixel(int x1, int y1, int x, int y)
{
    glVertex2i(x1 + x, y1 - y); // Chuy?n d?i t?a d? d? phù h?p v?i h? t?a d? OpenGL và d?i x?ng qua tr?c Ox
    glVertex2i(x1 + x, y1 + y);
}

void parabola_bresenham(int x1, int y1, float a)
{
    float p = 1 - 4 * a, x = 0, y = 0;
    glBegin(GL_POINTS);
    while (y <= 2 * a)
    {
        print_pixel(x1, y1, x, y);
        if (p < 0)
        {
            p += 2 + 4 * y;
        }
        else
        {
            p += 2 + 4 * y - 8 * a;
            x++;
        }
        y++;
    }
    p = 1 - 4 * a;
    while (x <= 2 * a)
    {
        print_pixel(x1, y1, x, y);
        if (p > 0)
        {
            p -= 8 * a;
        }
        else
        {
            p += 4 + 4 * y - 8 * a;
            y++;
        }
        x++;
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
    static int x1, y1, x2, y2;
    static bool first_click = true;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (first_click)
        {
            x1 = x - 320; // Chuy?n d?i t?a d? chu?t d? phù h?p v?i h? t?a d? c?a c?a s?
            y1 = 240 - y;
            first_click = false;
        }
        else
        {
            x2 = x - 320;
            y2 = 240 - y;
            float a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
            glBegin(GL_LINES);
            glVertex2i(-320, y1); // V? tr?c y
            glVertex2i(320, y1);
            glVertex2i(x1, -240); // V? tr?c x
            glVertex2i(x1, 240);
            glEnd();
            parabola_bresenham(x1, y1, a);
            first_click = true;
            glFlush();
        }
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // Màu n?n tr?ng
    glColor3f(0.0, 0.0, 0.0);         // Màu den
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0); // Ð?t h? t?a d?
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Parabola using GLUT (Bresenham)");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

