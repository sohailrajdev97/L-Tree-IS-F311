#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Lindenmayer.h"

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
    double colors[][3] = {{1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}};
    Lindenmayer tree1;
    tree1.setX(300);
    tree1.setY(0);
    tree1.setAngle(25);
    tree1.setAxiom("FX");
    tree1.addRule("F=C0FF-[C1-F+F]+[C2+F-F]");
    std::cout<<tree1.getAxiom()<<endl;
    tree1.draw(5, colors);
    
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
