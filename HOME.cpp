#include <iostream> //including the header files
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0); //specifying clear values for the color buffer
	glColor3f(0.0f,1.0f,0.0f); //sets the current color
	glPointSize(5.0); //sets the size of the line
	glMatrixMode(GL_PROJECTION); //specifying current matrix mode
	glLoadIdentity(); //replaces the current matrix with the identity matrix
	gluOrtho2D(0.0,640.0,0.0,480.0); //defines a 2D orthographic projection matrix
} 

void display(void)  //definition of display method
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);g
	glVertex2i(100,100);
	glVertex2i(100,150);
	glVertex2i(100,150);
	glVertex2i(150,150);
	glVertex2i(150,150);
	glVertex2i(150,100);
	glVertex2i(150,100);
	glVertex2i(100,100);
	glVertex2i(100,150);
	glVertex2i(125,175); //triangle top
	glVertex2i(150,150);
	glVertex2i(125,175);
	glVertex2i(120,100);
	glVertex2i(120,110);
	glVertex2i(120,110);
	glVertex2i(130,110);
	glVertex2i(130,110);
	glVertex2i(130,100);
	glEnd();
	glFlush();
}

int main(int argc ,char **argv)  //main method
{
	glutInit(&argc , argv);  //initializing the library
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);  //display window at a specific size
	glutInitWindowPosition(100,150);  //display window at a specific position
	glutCreateWindow("OpenGL Program");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}

