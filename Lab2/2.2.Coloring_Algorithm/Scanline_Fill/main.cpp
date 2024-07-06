#include <GL/glut.h>

// Ð?nh nghia c?u trúc di?m 2D
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// Các d?nh c?a da giác
Point vertices[] = {{0, 400}, {300, 400}, {150, 200}, {10, 300}};
int numVertices = sizeof(vertices) / sizeof(vertices[0]);

// H?ng s? màu
const float RED[] = {1.0, 0.0, 0.0};
const float BLUE[] = {0.0, 0.0, 1.0};
const float WHITE[] = {1.0, 1.0, 1.0};

// Hàm v? da giác
void drawPolygon() {
    glColor3fv(RED); // Màu biên d?
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; ++i) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();
    glFlush();
}

// Hàm x? lý s? ki?n click chu?t
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = glutGet(GLUT_WINDOW_HEIGHT) - y; // Chuy?n d?i t?a d? y

        // Tìm di?m bên trong da giác d? b?t d?u quét (scanline seed)
        int seedX = x;
        int seedY = y;

        // Stack s? d?ng d? luu các di?m c?n x? lý
        struct Stack {
            int top;
            Point *items;
            int maxSize;
        };

        Stack stack;
        stack.top = -1;
        stack.maxSize = 1000; // Gi? s? s? lu?ng di?m t?i da c?n x? lý
        stack.items = (Point *)malloc(stack.maxSize * sizeof(Point));

        // Push di?m seed vào stack
        stack.items[++stack.top] = Point(seedX, seedY);

        // Quét t?ng dòng và tô màu fill
        while (stack.top >= 0) {
            Point current = stack.items[stack.top--];

            // Tô màu t?i di?m hi?n t?i
            glColor3fv(BLUE); // Màu fill xanh duong
            glBegin(GL_POINTS);
            glVertex2i(current.x, current.y);
            glEnd();
            glFlush();

            // Ki?m tra các di?m xung quanh d? push vào stack
            Point neighbors[] = {{current.x - 1, current.y},
                                 {current.x + 1, current.y},
                                 {current.x, current.y - 1},
                                 {current.x, current.y + 1}};

            for (int i = 0; i < 4; ++i) {
                Point neighbor = neighbors[i];
                if (neighbor.x >= 0 && neighbor.x < glutGet(GLUT_WINDOW_WIDTH) &&
                    neighbor.y >= 0 && neighbor.y < glutGet(GLUT_WINDOW_HEIGHT)) {
                    // Ki?m tra n?u di?m là màu tr?ng (n?n)
                    float color[3];
                    glReadPixels(neighbor.x, neighbor.y, 1, 1, GL_RGB, GL_FLOAT, color);
                    if (color[0] == WHITE[0] && color[1] == WHITE[1] && color[2] == WHITE[2]) {
                        stack.items[++stack.top] = neighbor;
                    }
                }
            }
        }

        free(stack.items); // Gi?i phóng b? nh? c?a stack
    }
}

// Hàm hi?n th?
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // V? da giác
    drawPolygon();

    glFlush();
}

// Hàm kh?i t?o
void init() {
    glClearColor(WHITE[0], WHITE[1], WHITE[2], 1.0); // Màu n?n tr?ng
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
}

// Hàm main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Scanline Fill Algorithm with GLUT");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();
    return 0;
}

