#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>
	
using namespace std;

float hourAngle = 90.0;   //  hour hand
float minuteAngle = 90.0; // minute hand
float secondAngle = 90.0; // second hand

float pendulumAngle = 0.0; // Initial angle for pendulum
float pendulumInc = 0.002;   // Increment for pendulum angle

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}
void drawClock()
{
	glColor3f(0.6, 0.4, 0.2);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (int i = 0; i <= 360; i += 10)
	{
		float angleRad = i * 3.14159 / 180.0;
        	float x = 100 * cos(angleRad);
        	float y = 100 * sin(angleRad);
        	glVertex2f(x, y);
    	}
    	glEnd();
    	
    	glColor3f(1.0, 0.0, 0.0);
    	glPointSize(5.0);
    	glBegin(GL_POINTS);
    	for (int i = 1; i <= 12; ++i)
    	{
        	float angleRad = i * 30 * 3.14159 / 180.0;
        	float x = 90 * cos(angleRad);
        	float y = 90 * sin(angleRad);
        	glVertex2f(x, y);
    	}
    	glEnd();
}
void drawHand(float angle, float length, float width)
{
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	float radian = angle * 3.14159 / 180.0;
	float x = length * cos(radian);
	float y = length * sin(radian);
	glVertex2f(x, y);
	glEnd();
}
void drawPendulum()
{
	// Draw pendulum rod
	glColor3f(0.0, 0.0, 0.0);
    	glLineWidth(3.0);
    	glBegin(GL_LINES);
    	glVertex2f(0, -100); 
    	glVertex2f(0, -200); 
    	glEnd();

    	// Draw pendulum bob
    	glTranslatef(0, -200, 0);
    	glColor3f(1.0, 0.2, 0.5);
    	glBegin(GL_TRIANGLE_FAN);
    	for (int i = 0; i <= 360; i += 10) 
    	{
        	float angleRad = i * 3.14159 / 180.0;
        	float x = 25 * cos(angleRad);
        	float y = 25 * sin(angleRad);
        	glVertex2f(x, y);
    	}
    	glEnd();
    	glTranslatef(0, 200, 0);
}
void display() 
{
    	glClear(GL_COLOR_BUFFER_BIT);
    	drawClock();

    	// Get current time
    	time_t currentTime = time(NULL);
    	struct tm *localTime = localtime(&currentTime);

    	// Calculate angles for hour, minute, and second hands
    	int hours = localTime->tm_hour;
    	int minutes = localTime->tm_min;
    	int seconds = localTime->tm_sec;

    	hourAngle = 90.0 - (hours % 12 + minutes / 60.0) * 30.0;
    	minuteAngle = 90.0 - minutes * 6.0;
    	secondAngle = 90.0 - seconds * 6.0;

    	// Draw clock hands
    	glColor3f(0.0, 0.0, 1.0);
    	drawHand(hourAngle, 50.0, 3.0);

    	glColor3f(0.0, 1.0, 0.0);
    	drawHand(minuteAngle, 70.0, 2.0);

    	glColor3f(0.0, 0.0, 0.0);
    	drawHand(secondAngle, 90.0, 1.0);

    	// Draw pendulum
    	glPushMatrix();
    	glRotatef(pendulumAngle, 0, 0, 1);
    	drawPendulum();
    	glPopMatrix();

    	glFlush();
    	glutPostRedisplay();

    	// Update pendulum angle for swinging
    	pendulumAngle += pendulumInc;
    	if (pendulumAngle >= 15 || pendulumAngle <= -15)
        pendulumInc = -pendulumInc;
}
void keyboard(unsigned char key, int x, int y)
{
    	if (key == 27)
        	exit(0);
}
void Timer(int value)
{
    	glutTimerFunc(500, Timer, 0); 
    	glutPostRedisplay();
}

int main(int argc, char **argv) 
{
    	glutInit(&argc, argv);
    	glutInitWindowSize(500, 500);
    	glutInitWindowPosition(0, 0);
    	glutCreateWindow("Clock");
    	init();
    	glutDisplayFunc(display);
    	glutKeyboardFunc(keyboard);
    	glutTimerFunc(0, Timer, 0);
    	glutMainLoop();
    	return 0;
}

