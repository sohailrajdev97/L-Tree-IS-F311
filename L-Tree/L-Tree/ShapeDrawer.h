#ifndef ShapeDrawer_h
#define ShapeDrawer_h

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <cstdlib>

class ShapeDrawer {
    
private:
    
    GLfloat red, green, blue;
    
    void swap(int *a, int *b){
        int d = *a;
        *a = *b;
        *b = d;
    }
    
public:
    
    ShapeDrawer(){
        this->red = 1.0;
        this->green = 1.0;
        this->blue = 1.0;
    }
    
    void setColour(GLfloat red = 0.0, GLfloat green = 0.0, GLfloat blue = 0.0){
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
    
    void drawPixel(GLint x, GLint y) {
        glColor3f(red, green, blue);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
    }
    
    void drawLine(int x1, int y1, int x2, int y2){
        
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int xDirection = 0, yDirection = 0, swapStatus = 0;
        int i, x = x1, y = y1;
        
        if(x2 > x1)
            xDirection = 1;
        else if(x2 < x1)
            xDirection = -1;
        
        if(y2 > y1)
            yDirection = 1;
        else if (y2 < y1)
            yDirection = -1;
        
        if(dy > dx){
            swap(&dy, &dx);
            swapStatus = 1;
        }
        
        int dNE = 2*(dy - dx);
        int dE = 2*dy;
        int d = 2*dy - dx;
        
        for(i = 1; i <= dx; i++){
            drawPixel(x, y);
            
            if(d >= 0){
                if(swapStatus){
                    x = x + xDirection;
                    d = d + dNE;
                } else {
                    y = y + yDirection;
                    d = d + dNE;
                }
            } else {
                if(swapStatus){
                    d = d + dE;
                } else {
                    d = d + dE;
                }
            }
            
            if(swapStatus)
                y = y + yDirection;
            else
                x = x + xDirection;
        }
    }
};


#endif

/* ShapeDrawer_h */
