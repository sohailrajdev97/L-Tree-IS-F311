#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "ShapeDrawer.h"

void init() {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Lines");
    glClearColor(0.0, 0.0, 0.0, 0);
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    ShapeDrawer sd;
    
    sd.drawLine(320, 0, 320, 200);
    
    sd.randomizeColour();
    sd.drawCircle(320, 330, 130);
    sd.randomizeColour();
    sd.drawCircle(320, 330, 100);
    sd.randomizeColour();
    sd.drawCircle(320, 330, 70);
    sd.randomizeColour();
    sd.drawCircle(320, 330, 40);
    sd.randomizeColour();
    sd.drawCircle(320, 330, 10);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
