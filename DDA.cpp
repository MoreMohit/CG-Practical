#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;
int option;
void drawLine (int x1, int y1, int x2, int y2, int s)
{
	float x, y, dx, dy, length;
	int i;
	int t = 0;
	dx = (x2 - x1);
	dy = (y2 - y1);
	if (abs (dx) >= abs (dy))
	{
		length = abs (dx);
	}
	
	else
	{
		length = abs (dy);
	}
	dx = dx / length;
	dy = dy / length;
	x = x1;
	y = y1;
	glBegin (GL_POINTS);
	glVertex2i (round (x), round (y));
	glEnd ();
	for (i = 1; i <= length; i++)
	{
		switch (s)
		{
			case 1:
				glBegin (GL_POINTS);
				glVertex2i (x, y);
				glEnd ();
				break;
			case 2:
				if (i % 20 == 0)
				{
					glBegin (GL_POINTS);
					glVertex2i (x, y);
					glEnd ();
					break;
				}
			case 3:
				if (i % 15 == 0)
				{
					if (t == 0)
					{
						t = 1;
					}
					else
					{
						t = 0;
					}
				}
				if (t == 0)
				{
					glBegin (GL_POINTS);
					glVertex2i (x, y);
					glEnd ();
				}
					break;
				case 4:
					glPointSize (3.0);
					glBegin (GL_POINTS);
					glVertex2i (x, y);
					glEnd ();
					break;
				case 5:
					glBegin (GL_POLYGON); //boat base
					glColor3f (0, 1, 0);
					glVertex2i (-150, 0);
					glVertex2i (150, 0);
					glVertex2i (250, 100);
					glVertex2i (-250, 100);
					glEnd ();
					glBegin (GL_TRIANGLES); //boat top
					glColor3f (0, 0, 1);
					glVertex2i (0, 100);
					glVertex2i (0, 300);
					glVertex2i (150, 100);
					glEnd ();
					glColor3f (1, 1, 1);
					break;
		}
		x = x + dx;
		y = y + dy;
	}
}
void display()
{
    glFlush();
}
void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}
void inputKeyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
    case 27:
        exit(0);
    }
}
void inputMouse(int button, int state, int x, int y)
{
    static int x1, x2, y1, y2;
    static int pt = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (pt == 0)
        {
            glColor3f(0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_LINES);
            glVertex2i(-500.0, 0);
            glVertex2i(500.0, 0);
            glVertex2i(0, -500.0);
            glVertex2i(0, 500.0);
            glEnd();
            pt++;
        }
        else
        {
            if (pt == 1)
            {
                x1 = x;
                y1 = y;
                pt++;
            }
            else if(pt==2)
            {
            	x2 = x;
                y2 = y;
                drawLine(-500 + 2 * x1, 500 - 2 * y1, -500 + 2 * x2, 500 - 2 * y2, option);
                pt=0;
            }
            
        }
     }
     glFlush();
}                
void menu(int choice)
{
	option=choice;
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DDA LINE DRAWING ALGORITHM");
	init();
	glutCreateMenu(menu);
	glutAddMenuEntry("DDA Simple", 1);
	glutAddMenuEntry("DDA Dotted", 2);
	glutAddMenuEntry("DDA Dashed", 3);
	glutAddMenuEntry("DDA SOLID", 4);
	glutAddMenuEntry("DDA Object", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMouseFunc(inputMouse);
	glutKeyboardFunc(inputKeyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
