#include <iostream>
#include <GL/glut.h>
using namespace std;
int width = 400, height = 400, option=1 ;

struct Color{
 float r,g,b;
 };
 
void setPixel(int x, int y, Color c ) {
    glColor3f(c.r, c.g , c.b );
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

Color getPixel(int x, int y) {
    Color p;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &p);
    return p ;
}

void drawSquare() {
    glColor3f(0.0, 0.0, 0.0);
   
   int row, col;
    int size = 50; // Size of each square

    // Draw horizontal lines
    //glColor3f(1.0, 1.0, 1.0); // White color
    for(row = 0; row <= 8; row++) {
        glBegin(GL_LINES);
        glVertex2i(0, row * size);
        glVertex2i(8 * size, row * size);
        glEnd();
    }
    // Draw vertical lines
    for(col = 0; col <= 8; col++) {
        glBegin(GL_LINES);
        glVertex2i(col * size, 0);
        glVertex2i(col * size, 8 * size);
        glEnd();
    }
    glFlush();
}

void boundaryFill4(int x, int y, Color fillColor, Color borderColor) {
    Color pixel = getPixel(x, y);
    if ((pixel.r != borderColor.r || pixel.g != borderColor.g || pixel.b != borderColor.b ) &&
        ( pixel.r != fillColor.r || pixel.g != fillColor.g || pixel.b != fillColor.b )) {
        setPixel(x, y, fillColor);
        boundaryFill4(x + 1, y, fillColor, borderColor);
        boundaryFill4(x - 1, y, fillColor, borderColor);
        boundaryFill4(x, y + 1, fillColor, borderColor);
        boundaryFill4(x, y - 1, fillColor, borderColor);
    }
}

void floodFill4(int x, int y, Color fillColor, Color oldColor) {
    Color pixel = getPixel(x, y);
    if (pixel.r == oldColor.r && pixel.g == oldColor.g && pixel.b == oldColor.b) {
        setPixel(x, y, fillColor);
        floodFill4(x + 1, y, fillColor, oldColor);
        floodFill4(x - 1, y, fillColor, oldColor);
        floodFill4(x, y + 1, fillColor, oldColor);
        floodFill4(x, y - 1, fillColor, oldColor);
    }
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    glFlush();
}

void menu(int index) {
   option=index;
}

void mouse(int button, int state, int x, int y) {
	int n;
Color newColor={0.0f,1.0f,0.0f};
	Color oldColor={1.0f,1.0f,1.0f};
	Color borderColor={0.0f,0.0f,0.0f};
	Color fillColor={0.0f,0.0f,1.0f};
	Color fillColor2={1.0f,0.0f,1.0f};
	if(option==1)
	{
	/* cout<< "CHOOSE COLOR : 1) R 2) G 3) B 4) PINK ";
	 cin>>n;
	 if (n==1) fillColor={1.0f,0.0f,0.0f};
	 if (n==2) fillColor={0.0f,1.0f,0.0f};
	 if (n==3) fillColor={0.0f,0.0f,1.0f};
	 if (n==4) fillColor={1.0f,0.0f,1.0f};*/
	 floodFill4(x,400-y,fillColor,oldColor);
	}
	else
	 boundaryFill4(x,400-y,fillColor2,borderColor);
	 
	 glFlush();
    
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Simple Polygon Filling");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutCreateMenu(menu);
    glutAddMenuEntry("Flood Fill", 1);
    glutAddMenuEntry("Boundary Fill", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}

