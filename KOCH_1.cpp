#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

GLfloat oldx = -0.7, oldy = 0.5;
int k = 0, c;
int numPoints = 0; // control points 
const int MAX_POINTS = 10;
GLfloat controlPoints[MAX_POINTS][2]; 

void drawkoch(GLfloat dir, GLfloat len, GLint iter, GLfloat lineWidth)
{
    GLdouble dirRad = 0.0174533 * dir;
    GLfloat newx = oldx + len * cos(dirRad);
    GLfloat newy = oldy + len * sin(dirRad);

   
    glLineWidth(lineWidth);

    glBegin(GL_LINE_LOOP);
    if (iter == 0)
    {
        glVertex2f(newx, newy);
        glVertex2f(oldx, oldy);
        oldx = newx;
        oldy = newy;
    }
    else
    {
        iter--;
        drawkoch(dir, len, iter, lineWidth);
        dir += 60;
        drawkoch(dir, len, iter, lineWidth);
        dir -= 120;
        drawkoch(dir, len, iter, lineWidth);
        dir += 60;
        drawkoch(dir, len, iter, lineWidth);
    }
    glEnd();
}
// Function to calculate the midpoint between two points
void midPoint(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat &xm, GLfloat &ym)
{
    xm = (x1 + x2) / 2.0;
    ym = (y1 + y2) / 2.0;
}
void mydisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(10);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < numPoints; i++)
    {
        glVertex2fv(controlPoints[i]);
    }
    glEnd();
}
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        GLfloat glx = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
        GLfloat gly = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);

        // Store the control point
        controlPoints[numPoints][0] = glx;
        controlPoints[numPoints][1] = gly;

        numPoints++; 

        if (numPoints >= MAX_POINTS)
        {
            cout << "Maximum number of control points reached." << endl;
            numPoints = MAX_POINTS; 
        }

        glutPostRedisplay(); 
    }
}
void menu(int value)
{
    switch (value)
    {
    case 1:
        // Draw Koch Snowflake
        cout << "\nEnter the number of iterations for Koch Snowflake: ";
        int n;
        cin >> n;
        glClear(GL_COLOR_BUFFER_BIT);
        drawkoch(0.0, 0.05, n, 1.0);
        drawkoch(-120.0, 0.05, n, 1.0);
        drawkoch(120.0, 0.05, n, 1.0);
        glFlush();
        break;

    case 2:
        exit(0);
        break;
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CURVE DRAWING");
    glutCreateMenu(menu);
    glutAddMenuEntry("Koch Snowflake", 1);
    glutAddMenuEntry("EXIT",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}
