#ifndef ShapeDrawer_h
#define ShapeDrawer_h

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#define direction(x1, x2) ((x2 > x1) ? 1 : -1)

#include <cstdlib>
#include <ctime>
#include <cmath>

class ShapeDrawer {
    
private:
    
    GLfloat red, green, blue;
    
    void swap(int *a, int *b){
        int d = *a;
        *a = *b;
        *b = d;
    }
    
    void plotCircle(GLint xi,GLint yi,GLint xc,GLint yc){
        
		drawPixel(xi+xc,yi+yc);
		drawPixel(xi+xc,yc-yi);
		drawPixel(xc-xi,yc+yi);
		drawPixel(xc-xi,yc-yi);
		drawPixel(xc+yi,yc+xi);
		drawPixel(xc+yi,yc-xi);
		drawPixel(xc-yi,yc+xi);        
		drawPixel(xc-yi,yc-xi);
        
	}
    
public:
    
    ShapeDrawer(){
        this->red = 1.0;
        this->green = 1.0;
        this->blue = 1.0;
        srand((unsigned int)time(NULL));
    }
    
    void randomizeColour(){
        this->red = ((double)(rand()%100))/100;
        this->green = ((double)(rand()%100))/100;
        this->blue = ((double)(rand()%100))/100;
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
        
        xDirection = direction(x1, x2);
        yDirection = direction(y1, y2);
        
        if(dy > dx){
            swap(&dy, &dx);
            swapStatus = 1;
        }
        
        int dNE = 2*(dy - dx);
        int dE = 2*dy;
        int d = 2*dy - dx;
        
        for(i = 1; i <= dx; i++){
            drawPixel(x, y);
            
            if(d >= 0)
            {
                if(swapStatus)
                    x = x + xDirection;
                else
                    y = y + yDirection;
                
                d = d + dNE;
            }
            else
                d = d + dE;
            
            if(swapStatus)
                y = y + yDirection;
            else
                x = x + xDirection;
            
            
        }
    }
    
    void drawLineAtAngle(GLint x1, GLint y1, double angle, double length){
        
        int x2 = round(x1 + (length*cos(angle*M_PI/180)));
        int y2 = round(y1 + (length*sin(angle*M_PI/180)));
        
        drawLine(x1, y1, x2, y2);
    
    }

	void drawCircle(GLint x0,GLint y0,GLint r0){
		GLint x = 0;
		GLint y = r0;
		GLint pixel = 1-r0;
	
		while(x <= y){
			plotCircle(x,y,x0,y0);
	
		if(pixel<0){
			pixel = pixel+2*x+3;
		}
		else {
			pixel = pixel+2*(x-y)+5;
			y--;
		}
		x++;
		}
	}
};


#endif

/* ShapeDrawer_h */
