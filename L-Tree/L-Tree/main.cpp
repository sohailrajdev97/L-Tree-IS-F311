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

int screenWidth, screenHeight;

int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    init();
    glutMainLoop();
    return 0;
    
}

void init() {
    
    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("L-Systems");
    
    glutKeyboardFunc(processKeys);
    glutDisplayFunc(draw);
    
    glClearColor(0.878, 1.0, 1.0, 0);
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glutFullScreen();
    
}

void draw() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    ShapeDrawer sd;
    sd.setColour(0.545, 0.270, 0.074);
    
    int i;
    for(i=0; i < screenHeight/8; i++){
        sd.drawLine(0, i, screenWidth, i);
    }
    double colors[][3] = {{0.545, 0.270, 0.074}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    
    Lindenmayer tree1;
    tree1.setX(500);
    tree1.setY(screenHeight/16);
    tree1.setAngle(22.5);
    tree1.setBranchLength(0.111*screenHeight);
    tree1.setBranchScaleFactor(0.82);
    tree1.setAxiom("XF");
    tree1.addRule("F=C0F[C1+FX][F[C2+FX][FX][C2-FX]][C1-FX]");
    tree1.draw(6, colors);
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
