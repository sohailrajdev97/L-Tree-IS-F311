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
    double gradient = 1.0;
    for(i=0; i < screenHeight/8; i++){
        sd.setColour(gradient/2,gradient,0.0);
        gradient -= 4.0/screenHeight;
        sd.drawLine(0, i, screenWidth, i);
    }

    double leftTreeColors[][3] = {{0.111, 0.111, 0.439}, {0.576, 0.458, 0.858}, {0.545, 0.0, 0.545}};
    
    Lindenmayer tree;
    tree.setX(0.347*screenWidth);
    tree.setY(screenHeight/8);
    tree.setAngle(22.5);
    tree.setBranchLength(0.111*screenHeight);
    tree.setBranchScaleFactor(0.82);
    tree.setAxiom("F");
    tree.addRule("F=C0F[C1+F][F[C2+F][F][C2-F]][C1-F]");
    tree.draw(6, leftTreeColors);
    
    double rightTreeColors[][3] = {{0.501, 0.0, 0.0}, {0.980, 0.501, 0.4470}, {0.862, 0.078, 0.235}};
    tree.setX(0.6944*screenWidth);
    tree.setY(screenHeight/8);
    tree.setBranchLength(0.065*screenHeight);
    tree.draw(6, rightTreeColors);
    
    Lindenmayer grass;
    grass.setAxiom("C0F");
    grass.addRule("F=[+F[+F]][-F[-F]]");
    grass.setAngle(25);
    grass.setBranchLength(8);
    grass.setBranchScaleFactor(0.75);
    grass.setY(screenHeight/8);
    double grassColors[][3] = {{0.25, 0.5, 0.0}};
    for(i=0; i < screenWidth; i = i + 15){
        grass.setX(i);
        grass.draw(1, grassColors);
    }
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
