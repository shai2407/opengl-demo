#include <iostream>
#include <gl/glut.h>
#include <GL/gl.h>
#include <GL/glU.h>
#include <Windows.h>
#include <math.h>

void displayTrapX(float x,float y) {
    glBegin(GL_POLYGON);
    glColor4f(0, 0.0, 0, 0.5);
    glVertex2f(-x, y);
    glColor4f(0, 0.2, 0.8, 0.5);
    glVertex2f(x, y);
    glColor4f(0, 0.4, 0.6, 0.5);
    glVertex2f(x-0.2, y-0.2);
    glColor4f(0, 0.6, 0.4, 0.5);
    glVertex2f(-x+0.2, y-0.2);
    glEnd();
}

void displayTrapY(float x, float y) {
    glBegin(GL_POLYGON);
    glColor4f(0, 0.0, 0, 0.5);
    glVertex2f(x, -0.3);
    glColor4f(0, 0.2, 0.8, 0.5);
    glVertex2f(x, 0.3);
    glColor4f(0, 0.4, 0.6, 0.5);
    glVertex2f(0.8*x, 0.1);
    glColor4f(0, 0.6, 0.4, 0.5);
    glVertex2f(0.8*x, -0.1);
    glEnd();
}

void displayShapes(void)
{
    // trapezoid
    displayTrapX(0.3, 1);
    displayTrapY(1, 0.3);
    displayTrapY(-1, 0.3);

    // circle
    const int steps = 100;
    const float angle = 2.f * 3.14159 / steps; // angle in radians
    float xPos = 0; float yPos = 0; float radius = 0.3f;
    float prevX = xPos;
    float prevY = yPos - radius;
    for (int i = 0; i < steps+1; i++) {
        float newX = radius * sin(angle * i);
        float newY = -radius * cos(angle * i);

        glBegin(GL_TRIANGLES);
        glColor3f(cos(angle * i), tan(angle * i), sin(angle*i));
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(prevX, prevY, 0.0f);
        glVertex3f(newX, newY, 0.0f);
        glEnd();

        prevX = newX;
        prevY = newY;
    }

    // exit button
    glBegin(GL_POLYGON);
    glColor4f(1, 1.0, 1, 0);
    glVertex2f(-1, -1);
    glVertex2f(-1, -0.9);
    glVertex2f(-0.8, -0.9);
    glVertex2f(-0.8 , -1);
    glEnd();
}

void drawText(const char* text, int length, int x, int y, void* font) {
    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(font, (int)text[i]);        
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

// exit button func
void Mouse(int Button, int State, int X, int Y) {
    if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)
    {
        if (X <= 50 && Y >= 480) {
            exit(0);
        }
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // background color
    glClearColor(0,0, 0, 0); 
    
    // draw shapes
    displayShapes();

    // draw text
    std::string name; std::string course; std::string exit;
    name = "Shaaaaaaai Gal"; course = "20562 - Computer Graphics"; exit = "Exit";
    glColor3f(1, 1, 0);
    drawText(name.data(), name.size(), 5, 50, GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1, 0, 1);
    drawText(course.data(), course.size(), 5, 30, GLUT_BITMAP_9_BY_15);
    glColor3f(1, 0, 0);
    drawText(exit.data(), exit.size(), 5, 5, GLUT_BITMAP_TIMES_ROMAN_24);

    // exit function
    glutMouseFunc(Mouse);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    //create window
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    //title
    glutCreateWindow("Computer Graphics");   
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}