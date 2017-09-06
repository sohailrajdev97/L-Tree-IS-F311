#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "ShapeDrawer.h"

void init() {
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Lines");
    glClearColor(0.0,0.0,0.0,0);
    gluOrtho2D(0,640,0,480);
    
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    ShapeDrawer sd;
    sd.setColour(1);
    
    sd.drawLine(0,0,640,480);
    sd.drawLine(0, 480, 640, 0);
    sd.drawLine(0, 240, 640, 240);
    sd.drawLine(320, 0, 320, 480);
    
    sd.setColour(0,1);
    sd.drawLine(0, 0, 320, 480);
    sd.drawLine(0, 480, 150, 0);
    sd.drawLine(150, 0, 640, 480);
    
    
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
