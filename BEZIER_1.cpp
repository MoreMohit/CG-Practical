#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

GLfloat oldx = -0.7, oldy = 0.5;
int k = 0, c;
int numPoints = 0; // control points 


const int MAX_POINTS = 10;
GLfloat controlPoints[MAX_POINTS][2]; 
// Function to calculate the midpoint between two points
void midPoint(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat &xm, GLfloat &ym)
{
    xm = (x1 + x2) / 2.0;
    ym = (y1 + y2) / 2.0;
}
void drawBezier(GLfloat p[][2], int n, GLfloat lineWidth)
{
    GLfloat q[MAX_POINTS][2];
    GLfloat t = 0.0;

    glLineWidth(lineWidth);

    glBegin(GL_LINE_STRIP);
    for (t = 0.0; t <= 1.0; t += 0.01)
    {
        for (int i = 0; i < n; i++)
        {
            q[i][0] = p[i][0];
            q[i][1] = p[i][1];
        }

        for (int k = 1; k < n; k++)
        {
            for (int i = 0; i < n - k; i++)
            {
                q[i][0] = (1 - t) * q[i][0] + t * q[i + 1][0];
                q[i][1] = (1 - t) * q[i][1] + t * q[i + 1][1];
            }
        }

        glVertex2fv(q[0]);
    }
    glEnd();
}

void mydisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(10);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Draw control points as small points
    glColor3f(0.0f, 0.0f, 1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < numPoints; i++)
    {
        glVertex2fv(controlPoints[i]);
    }
    glEnd();

    // Draw Bezier Curve
    if (numPoints >= 3)
    {
        glColor3f(1.0f, 0.0f, 1.0f); // Change color for curve
        drawBezier(controlPoints, numPoints, 4.0);
    }

    glFlush();
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
        // Draw Bezier Curve
        if (numPoints < 3)
        {
            cout << "At least 3 control points are required for Bezier Curve." << endl;
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        drawBezier(controlPoints, numPoints, 1.0);
        glFlush();
        break;

   case 2:
        exit(0);
        break;
    }
}
void createMenu()
{
    glutCreateMenu(menu);
    glutAddMenuEntry("Bezier Curve", 1);
    glutAddMenuEntry("EXIT", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CURVE DRAWING");

    createMenu();

    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}

