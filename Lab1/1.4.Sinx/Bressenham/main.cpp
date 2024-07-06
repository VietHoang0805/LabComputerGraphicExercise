#include <GL/glut.h>
#include <cmath>

// Khai báo h?ng s? cho c?a s? OpenGL
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Hàm v? di?m t?i (x, y) v?i màu tr?ng
void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Hàm v? d? th? hàm sin(x) s? d?ng thu?t toán Bresenham
void drawSine(float amplitude)
{
    // Ði?u ch?nh d? v? t? -pi d?n pi
    float startX = -M_PI;
    float endX = M_PI;
    float step = 0.01;

    // Dùng thu?t toán Bresenham d? v? d? th? sin(x)
    for (float x = startX; x <= endX; x += step)
    {
        float y = amplitude * sin(x);
        int pixelX = static_cast<int>((x + M_PI) / (2 * M_PI) * WINDOW_WIDTH); // Scale x to fit window width
        int pixelY = static_cast<int>((y + amplitude) / (2 * amplitude) * WINDOW_HEIGHT); // Scale y to fit window height
        setPixel(pixelX, pixelY);
    }
}

// Hàm display: v? d? th? khi c?a s? c?n v? l?i
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // V? tr?c t?a d?
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(0, WINDOW_HEIGHT / 2);
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    glVertex2i(WINDOW_WIDTH / 2, 0);
    glVertex2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    glEnd();

    // V? d? th? sin(x) v?i amplitude là 200
    glColor3f(1.0, 0.0, 0.0); // Màu d?
    drawSine(200.0);

    glFlush();
}

// Hàm reshape: x? lý s? ki?n thay d?i kích thu?c c?a s?
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

// Hàm kh?i t?o và ch?y chuong trình
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Sin(x) Graph with Bresenham Algorithm");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glClearColor(1.0, 1.0, 1.0, 0.0); // Màu n?n tr?ng
    glLoadIdentity();
    glutMainLoop();
    return 0;
}

