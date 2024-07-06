#include <GL/glut.h>
#include <cmath>
#include <algorithm> // Ð? s? d?ng std::min và std::max

typedef struct {
    int x, y;
} Point;

Point A, B, wmax, wmin;
float goc;
char chuot;

void KhoiTao() {
    glClearColor(0, 0, 0, 0);
    glLineWidth(2);

    wmin.x = 0; wmin.y = 0;
    wmax.x = 200; wmax.y = 120;
    A.x = 300; A.y = 200;
    B.x = 50; B.y = -100;

    goc = 0;
    chuot = 0;
}

int Ma(Point M) {
    int m = 0;
    if (M.x < wmin.x) m |= 1;
    if (M.x > wmax.x) m |= 2;
    if (M.y < wmin.y) m |= 4;
    if (M.y > wmax.y) m |= 8;
    return m;
}

void HoanVi(Point *A, Point *B) {
    Point T;
    T = *A; *A = *B; *B = T;
}

Point Xoay(Point A, int g) {
    float goc_rad = g * M_PI / 180;
    Point T;
    T.x = A.x * cos(goc_rad) - A.y * sin(goc_rad);
    T.y = A.x * sin(goc_rad) + A.y * cos(goc_rad);
    return T;
}

void VeDuongThang(Point A, Point B) {
    glBegin(GL_LINES);
    glVertex2i(A.x, A.y);
    glVertex2i(B.x, B.y);
    glEnd();
}

void VeHCN(Point wmin, Point wmax, int g) {
    Point A, B, C, D;
    A = wmin;
    C = wmax;
    B.x = wmax.x; B.y = wmin.y;
    D.x = wmin.x; D.y = wmax.y;

    A = Xoay(A, g);
    B = Xoay(B, g);
    C = Xoay(C, g);
    D = Xoay(D, g);

    glBegin(GL_LINE_LOOP);
    glVertex2i(A.x, A.y);
    glVertex2i(B.x, B.y);
    glVertex2i(C.x, C.y);
    glVertex2i(D.x, D.y);
    glEnd();
}

void ClipCohen(Point A, Point B, Point wmin, Point wmax, int g) {
    int x_min = std::min(wmin.x, wmax.x);
    int x_max = std::max(wmin.x, wmax.x);
    int y_min = std::min(wmin.y, wmax.y);
    int y_max = std::max(wmin.y, wmax.y);

    int outcode0 = Ma(A);
    int outcode1 = Ma(B);
    int accept = 0;
    double x, y;

    while (true) {
        if (!(outcode0 | outcode1)) {
            accept = 1;
            break;
        } else if (outcode0 & outcode1) {
            break;
        } else {
            int outcode_out = outcode0 ? outcode0 : outcode1;

            if (outcode_out & 8) { // top
                x = A.x + (B.x - A.x) * (y_max - A.y) / (B.y - A.y);
                y = y_max;
            } else if (outcode_out & 4) { // bottom
                x = A.x + (B.x - A.x) * (y_min - A.y) / (B.y - A.y);
                y = y_min;
            } else if (outcode_out & 2) { // right
                y = A.y + (B.y - A.y) * (x_max - A.x) / (B.x - A.x);
                x = x_max;
            } else if (outcode_out & 1) { // left
                y = A.y + (B.y - A.y) * (x_min - A.x) / (B.x - A.x);
                x = x_min;
            }

            if (outcode_out == outcode0) {
                A.x = x;
                A.y = y;
                outcode0 = Ma(A);
            } else {
                B.x = x;
                B.y = y;
                outcode1 = Ma(B);
            }
        }
    }

    if (accept) {
        VeDuongThang(Xoay(A, g), Xoay(B, g));
    }
}

void Mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);
    VeHCN(wmin, wmax, goc);

    glColor3f(0.0, 0.0, 1.0);
    VeDuongThang(A, B);

    glColor3f(1.0, 0.0, 0.0);
    ClipCohen(Xoay(A, -goc), Xoay(B, -goc), wmin, wmax, goc);

    glFlush();
}

void KeyboardEventHandler(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        goc += 10;
        if (goc > 360) goc = 0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        goc -= 10;
        if (goc < 0) goc = 360;
        glutPostRedisplay();
        break;
    }
}

void MouseEventHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        if (chuot == 0) {
            A.x = x - 300;
            A.y = 300 - y;
            chuot = 1;
        } else {
            B.x = x - 300;
            B.y = 300 - y;
            chuot = 0;
            glutPostRedisplay();
        }
}

int main(int argc, char* arg[]) {
    glutInit(&argc, arg);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Thuat Toan Xen Hinh");
    gluOrtho2D(-300, 300, -300, 300);
    KhoiTao();
    glutMouseFunc(MouseEventHandler);
    glutDisplayFunc(Mydisplay);
    glutSpecialFunc(KeyboardEventHandler);
    glutMainLoop();
    return 0;
}

