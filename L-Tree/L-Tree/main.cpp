#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Lindenmayer.h"

void init();
void draw();
void processKeys(unsigned char, int, int);

int screenWidth, screenHeight;

int main(int argc, char **argv)
{
    
    /// Initialise the glut main window and main loop
    glutInit(&argc, argv);
    init();
    glutMainLoop();
    return 0;
    
}

void init() {
    
    screenWidth = glutGet(GLUT_SCREEN_WIDTH); // Get screen width
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // Get screen height

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0); // Set initial window position
    glutInitWindowSize(screenWidth, screenHeight); // Set window size
    glutCreateWindow("L-Systems"); // Create and set a window title
    
    glutKeyboardFunc(processKeys); // Set keyboard event listener
    glutDisplayFunc(draw); // Hook a display function to window
   
    glutFullScreen(); // Enable full screen mode
    
}

void draw() {
    
    // Setup background gradient
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glBegin(GL_QUADS);
    
    //Top Gradient
    glColor3f(1.0,0.807,1.0);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    
    //Bottom Gradient
    glColor3f(0.678,0.847,0.9);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();
    
    /**************************/
    
    // Setup ortho 2-D projection matrix.
    
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    
    ShapeDrawer sd;
    sd.setColour(0.545, 0.270, 0.074);
    
    /**************************/
    
    // Draw the land
    int i;
    double gradient = 1.0;
    for(i=0; i < screenHeight/8; i++){
        sd.setColour(gradient/2,gradient,0.0);
        gradient -= 4.0/screenHeight;
        sd.drawLine(0, i, screenWidth, i);
    }
    
    /**************************/
    
    // Draw trees

    double leftTreeColors[][3] = {{0.111, 0.111, 0.439}, {0.576, 0.458, 0.858}, {0.545, 0.0, 0.545}};
    
    Lindenmayer tree("F", 6);
    tree.setX(0.27*screenWidth);
    tree.setY(screenHeight/8);
    tree.setAngle(22.5);
    tree.setBranchLength(0.111*screenHeight);
    tree.setBranchScaleFactor(0.82);
    tree.setPointSize(3);
    tree.setPointScaleFactor(0.8);
    tree.addRule("F=C0F[C1+F][F[C2+F][F][C2-F]][C1-F]");
    tree.draw(leftTreeColors);
    
    double rightTreeColors[][3] = {{0.501, 0.0, 0.0}, {0.980, 0.501, 0.4470}, {0.862, 0.078, 0.235}};
    tree.setX(0.62*screenWidth);
    tree.setY(screenHeight/8);
    tree.setBranchLength(0.065*screenHeight);
    tree.draw(rightTreeColors);
    
    /**************************/
    
    // Draw sun
    
    Lindenmayer sun("[X]++[X]++[X]++[X]++[X]", 5);
    double sunColors[][3] = {{1.0,0.54,0}, {1.0,0.40,0}};
    sun.addRule("W=YF++ZF----XF[-YF----WF]++");
    sun.addRule("X=C0+YF--ZF[C1---WF--XF]+");
    sun.addRule("Y=-WF++XF[+++YF++ZF]-");
    sun.addRule("Z=--YF++++WF[+ZF++++XF]--XF");
    sun.addRule("F=");
    sun.setY(0.77*screenHeight);
    sun.setX(0.83*screenWidth);
    sun.setPointSize(2);
    sun.setBranchLength(0.01*screenHeight);
    sun.setBranchScaleFactor(1);
    sun.setAngle(36);
    sun.draw(sunColors);
    
    /**************************/
    
    // Draw grass
    
    Lindenmayer grass("C0F", 1);
    grass.addRule("F=[+F[+F]][-F[-F]]");
    grass.setAngle(25);
    grass.setBranchLength(6);
    grass.setBranchScaleFactor(0.75);
    grass.setY(screenHeight/8);
    double grassColors[][3] = {{0.25, 0.5, 0.0}};
    for(i=0; i < screenWidth; i = i + 15){
        grass.setX(i);
        grass.draw(grassColors);
    }
    
    /**************************/
    glFlush();
    
}

void processKeys(unsigned char key, int x, int y){
    // A function to handle key presses.
    switch(key){
        case 27:
            exit(0); // Exit on Esc press
            break;
    }
    
    glutPostRedisplay();
}
