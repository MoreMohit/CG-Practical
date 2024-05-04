#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
GLfloat house[3][9] = {{50,50,125,200,200,100,100,150,150}, // Define the vertices of the house
                       {50,200,300,200,50,50,100,100,50},
                       {1,1,1,1,1,1,1,1,1}};
GLfloat t_mat[3][3] = {{0}};// Transformation matrix
GLfloat result[3][9] = {{0}};// Resultant matrix after transformation
GLfloat theta;// Angle for rotation

int option, h = 0, k = 0;// Transformation options and parameters
GLfloat sx, sy, tx, ty, shx,shy; // Changed data type to GLfloat for scaling factors and translation
void multiply() {// Function to perform matrix multiplication
    int i, j, l;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++) {
            result[i][j] = 0;
            for (l = 0; l < 3; l++) {
                result[i][j] += t_mat[i][l] * house[l][j];
            }
        }
    }
}
void scale() { // Scaling function
    t_mat[0][0] = sx;
    t_mat[0][1] = 0;
    t_mat[0][2] = (1 - sx) * h;  // Modify scaling matrix to scale about fixed point (h, k)
    t_mat[1][0] = 0;
    t_mat[1][1] = sy;
    t_mat[1][2] = (1 - sy) * k;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}
void rotate() { // Rotation function
    GLfloat m, n;
    m = -h * (cos(theta) - 1) + k * (sin(theta));
    n = -k * (cos(theta) - 1) - h * (sin(theta));
    t_mat[0][0] = cos(theta);
    t_mat[0][1] = -sin(theta);
    t_mat[0][2] = m;
    t_mat[1][0] = sin(theta);
    t_mat[1][1] = cos(theta);
    t_mat[1][2] = n;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}
void reflectionx() { // Reflection about X-axis function
    t_mat[0][0] = 1;
    t_mat[0][1] = 0;
    t_mat[0][2] = 0;
    t_mat[1][0] = 0;
    t_mat[1][1] = -1;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}
void reflectiony() { // Reflection about Y-axis function
    t_mat[0][0] = -1;
    t_mat[0][1] = 0;
    t_mat[0][2] = 0;
    t_mat[1][0] = 0;
    t_mat[1][1] = 1;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}
void drawhouse(GLfloat house[3][9]) {  // Function to draw the house
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
    glBegin(GL_LINE_LOOP);
    glVertex2f(house[0][0], house[1][0]);
    glVertex2f(house[0][1], house[1][1]);
    glVertex2f(house[0][3], house[1][3]);
    glVertex2f(house[0][4], house[1][4]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(house[0][5], house[1][5]);
    glVertex2f(house[0][6], house[1][6]);
    glVertex2f(house[0][7], house[1][7]);
    glVertex2f(house[0][8], house[1][8]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(house[0][1], house[1][1]);
    glVertex2f(house[0][2], house[1][2]);
    glVertex2f(house[0][3], house[1][3]);
    glEnd();  
}
void menu(int choice) {
    option = choice;
}
void inputMouse(int button, int state, int x, int y) {    // Function for handling mouse input
    static int n,pt = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (pt == 0) {
            glColor3f(0.0, 0.0, 0.0);// Draw original house
            drawhouse(house);
            pt++;
        } else {
            switch (option) {  // Apply transformation based on selected option
                
                case 1:// Scaling
                    cout<<"Choose 1.Uniform Scaling 2.Differential Scaling ";
                    cin>>n;
                    if (n==1)
                    {
                    	cout<<"Enter scaling factor: ";
                        cin>>sx;
                        sy=sx;// Assume uniform scaling
                    }
                    else
                    {	
                    	cout << "Enter scaling about x: ";
                    	cin >> sx;
                    	cout << "Enter scaling about y: ";
                    	cin >> sy;
                    }
                    	scale();
                    	break;
                    	
                case 2: // Rotation about given point
                    	cout << "Enter rotation angle: ";
                    	cin >> theta;
                    	theta = theta * (3.142 / 180.0);
                    	cout << "Enter x coordinate of arbitrary point: ";
                    	cin >> h;
                    	cout << "Enter y coordinate of arbitrary point: ";
                    	cin >> k;
                    	rotate();
                    	break;
                    	
                case 3:
                    	reflectionx();// Reflection about x Axis
                    	break;
                case 4:
                    	reflectiony();// Reflection about Y Axis
                    	break;    	
            }
           glColor3f(0.0, 1.0, 0.0); // Draw transformed house
           drawhouse(result);
           pt = 0;
        }
    }
    glFlush();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(-500.0, 0);
    glVertex2i(500.0, 0);
    glVertex2i(0, -500.0);
    glVertex2i(0, 500.0);
    glEnd();
    drawhouse(house);
    glFlush();
}
void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
}
int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("House Transformation");
    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Scaling", 1);
    glutAddMenuEntry("Rotation about given point", 2);
    glutAddMenuEntry("Reflection about X Axis", 3);
    glutAddMenuEntry("Reflection about Y Axis", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(inputMouse);
    glutMainLoop();
    return 0;
}
