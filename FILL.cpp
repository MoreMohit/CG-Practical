#include<iostream> 
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

using namespace std;
int option=1;
struct Point
{
	GLint x;
	GLint y;
};

struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};
void menu(int index) {
   option=index;
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}
Color getPixelColor(GLint x,GLint y)
{
	Color color;
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&color);
	return color;
}
void setPixelColor(GLint x,GLint y,Color color)
{
	glColor3f(color.r,color.g,color.b);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void floodFill(GLint x,GLint y,Color oldColor,Color newColor)
{
	Color color;
	color = getPixelColor(x,y);
	
	if(color.r == oldColor.r && color.g == oldColor.g && color.b==oldColor.b)
	{
		
		 setPixelColor(x,y,newColor);
		 floodFill(x+1,y,oldColor,newColor);
		 floodFill(x,y+1,oldColor,newColor);
		 floodFill(x-1,y,oldColor,newColor);
		 floodFill(x,y-1,oldColor,newColor);
	}
	return;
}
void boundaryFill(GLint x,GLint y,Color fColor,Color bColor)
{
	Color color;
	color = getPixelColor(x,y);
	
	if((color.r != fColor.r || color.g != fColor.g || color.b != fColor.b)&&
	 (color.r != bColor.r || color.g != bColor.g || color.b != bColor.b))
	 {
	 	setPixelColor(x,y,fColor);
	 	boundaryFill(x+1,y,fColor,bColor);
	 	boundaryFill(x,y+1,fColor,bColor);
	 	boundaryFill(x-1,y,fColor,bColor);
	 	boundaryFill(x,y-1,fColor,bColor);
	 	
	 }
	 return;
}
void onMouseClick(int button,int state,int x,int y)
{
	Color newColor={0.0f,1.0f,0.0f};
	Color oldColor={0.0f,0.0f,0.0f};
	Color bColor={1.0f,1.0f,1.0f};
	Color fColor={0.0f,0.0f,1.0f};
	if(option==1)
	 floodFill(x,500-y,oldColor,newColor);
	else
	 boundaryFill(x,500-y,fColor,bColor);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	  
	glBegin(GL_LINE_LOOP);  //DRAW POLYGON
	
	glVertex2i(150,150);
	glVertex2i(150,300);
	glVertex2i(300,300);
	glVertex2i(300,150);
	glEnd();
	glFlush();
	 
}
int main(int argc, char **argv)
{
     
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Polygon Filling");
	init();
        glutCreateMenu(menu);
        glutAddMenuEntry("FLOOD FILL", 1);
        glutAddMenuEntry("BOUNDARY FILL", 2);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	
	return 0;
}

