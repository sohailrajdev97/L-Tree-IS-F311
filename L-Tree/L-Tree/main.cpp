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
    Lindenmayer tree1;
    tree1.setAxiom("peg");
    tree1.addRule("e=eie");
    std::cout<<tree1.getAxiom()<<endl;
    tree1.draw(3);
    
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
