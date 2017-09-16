#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Lindenmayer.h"

void init();
void draw();
void processKeys(unsigned char, int, int);

int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    init();
    glutMainLoop();
    return 0;
    
}

void init() {
    
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("L-Systems");
    
    glutKeyboardFunc(processKeys);
    glutDisplayFunc(draw);
    
    glClearColor(0.0, 0.0, 0.0, 0);
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glutFullScreen();
    
}

void draw() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    double colors[][3] = {{1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}};
    Lindenmayer tree1;
    tree1.setX(500);
    tree1.setY(0);
    tree1.setAngle(25);
    tree1.setAxiom("FX");
    tree1.addRule("F=C0FF-[C1-F+F]+[C2+F-F]");
    tree1.addRule("X=C0FF+[C1+F]+[C3-F]");
    std::cout<<tree1.getAxiom()<<endl;
    tree1.draw(4, colors);
    glFlush();
    
}

void processKeys(unsigned char key, int x, int y){
    
    switch(key){
        case 27:
            exit(0);
            break;
    }
    
    glutPostRedisplay();
}
