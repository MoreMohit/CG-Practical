#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;
int xc, yc, radius, option = 0; // Global variables to store circle center and radius, and the option selected
void drawCircle(int xx1, int yy1, int r)
{
    int x = 0, y = r;
    float d = 3 - 2 * r;
    do
    {
        glBegin(GL_POINTS);
        glVertex2i(xx1 + x, yy1 + y);
        glVertex2i(xx1 + x, yy1 - y); // Plot points based on symmetry
        glVertex2i(xx1 + y, yy1 + x);
        glVertex2i(xx1 + y, yy1 - x);
        glVertex2i(xx1 - x, yy1 + y);
        glVertex2i(xx1 - x, yy1 - y);
        glVertex2i(xx1 - y, yy1 - x);
        glVertex2i(xx1 - y, yy1 + x);
        
        glEnd();
        if (d <= 0)
        {
            d = d+4*x+6; // Mid-point algorithm condition
        }
        else
        {
            d = d+4*(x - y)+10;
            y--;
        }
        x++;
    } while (x < y);
}
void drawSpiral(int hc, int k, int x, int y, int a)
{
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
    for (int i = 0; i < 10; i++)
    {
        if (a % 2 == 0)
        {
            glVertex2i(hc + x, k + y);
            glVertex2i(hc - x, k + y);
            glVertex2i(hc + y, k + x);
            glVertex2i(hc - y, k + x);
        }
        if (a % 2 != 0)
        {
            glVertex2i(hc + x, k - y);
            glVertex2i(hc - x, k - y);
            glVertex2i(hc + y, k - x);
            glVertex2i(hc - y, k - x);
        }
    }
    glEnd();
    glFlush();
}
void Spiral(int r, int hc, int k, int a) {
    int x = 0, y = r; 
    int d = 3 - 2 * r;
    drawSpiral(hc, k, x, y, a);
    while (y >= x) {
        x++;
        if (d <= 0) {
            d = d + 4 * x + 6;
        }
        else {
            d = d + 4 * (x - y) + 10;
            y = y - 1;
        }
        drawSpiral(hc, k, x, y, a);
    }
}
void display()
{
    glBegin(GL_LINES);
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
    glFlush();
}
void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0); // Set up the viewing volume orthographically
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
}
void inputKeyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
    case 27: // Escape key
        exit(0);
    }
}
void inputMouse(int button, int state, int x, int y)
{
    static int x1, x2, y1, y2;
    static int pt = 0;
    int k = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (pt == 0)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_LINES);
            glVertex2i(-500.0, 0);
            glVertex2i(500.0, 0);
            glVertex2i(0, -500.0);
            glVertex2i(0, 500.0);
            glEnd();
            if (option == 3) // SPIRAL
            {
                int distance = abs(sqrt((x2 - xc) * (x2 - xc) + (y2 - yc) * (y2 - yc)));

                int r = 50;
                int hc = 0;
                k = 0;
                for (int i = 0; i < 20; i++)
                {
                    Spiral(r, hc, k, i);

                    if (i % 2 == 0)
                    {
                        hc = hc - 10;
                        r += 10;
                    }
                    if (i % 2 != 0)
                    {
                        hc = hc + 10;
                        r = r + 10;
                    }
                }
                pt = 0;
            }
            else
            {
                pt++;
            }
        }
        else
        {
            if (pt == 1)
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glBegin(GL_LINES);
                glVertex2i(-500.0, 0);
                glVertex2i(500.0, 0);
                glVertex2i(0, -500.0);
                glVertex2i(0, 500.0);
                glEnd();
                xc = -250 + x;
                yc = 250 - y;
                pt++;
            }
	    else if (pt == 2)
            {
                x2 = -250 + x;
                y2 = 250 - y;
	        int distance = sqrt((x2 - xc) * (x2 - xc) + (y2 - yc) * (y2 - yc));
		if (option == 1) // Circle
                {
                    drawCircle(xc, yc, distance);
                    pt = 0;
                }
                else if (option == 2) // Concentric circles
                {
                    while (distance <= 500)
                    {
                        drawCircle(xc, yc, distance);
                        distance += 100;
                    }
		    pt = 0;
                }
                else if (option == 4) // Olympic rings
                {
                    int distance = abs(sqrt((x2 - xc) * (x2 - xc) + (y2 - yc) * (y2 - yc)));
                    drawCircle(xc, yc, 2 * distance);
                    drawCircle(xc + (4.35 * distance), yc, (2 * distance));
                    drawCircle(xc + (8.75 * distance), yc, (2 * distance));
                    drawCircle(xc + (2.15 * distance), yc - (2.5 * distance), 2 * distance);
                    drawCircle(xc + (6.5 * distance), yc - (2.5 * distance), 2 * distance);
                    pt = 0;
                }
            }
        }
    }
    glFlush();
}
void menu(int choice)
{
    option = choice;
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham's Circle");
    init();
    glutCreateMenu(menu);
    glutAddMenuEntry("Circle", 1);
    glutAddMenuEntry("Concentric", 2);
    glutAddMenuEntry("Spiral", 3);
    glutAddMenuEntry("Olympic Rings", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(inputMouse);
    glutKeyboardFunc(inputKeyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
