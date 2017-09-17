#ifndef ShapeDrawer_h
#define ShapeDrawer_h

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <cstdlib>
#include <ctime>
#include <cmath>

#define direction(x1, x2) ((x2 > x1) ? 1 : -1) /**< A macros to check if x is increasing or decresing */
#define toRadians(degrees) ((double)degrees * M_PI)/180 /**< A macros to convert degrees to radians */

//! A class to draw various shapes (lines, circles and even pixels !)
class ShapeDrawer {
    
private:
    
    GLfloat red, green, blue, pointSize;
    
    void swap(int *a, int *b){
        // A method to swap two numbers.
        int d = *a;
        *a = *b;
        *b = d;
    }
    
    void plotCircle(GLint xi,GLint yi,GLint xc,GLint yc){
        
        /// A method to plot symmetrical point when drawing a circle using 8-way symmetry.
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
        /// Constructor method for ShapeDrawer class to set default color and seed the randomizer.
        this->red = 1.0; // Set the default color to red in case setColour method is not called
        this->green = 0.0;
        this->blue = 0.0;
        this->pointSize = 1.0;
        srand((unsigned int)time(NULL)); // Seed the randomizer with timestamp.
    }
    
    void randomizeColour(){
        /// A method to randomize the drawing color of ShapeDrawer object.
        
        // Update the values of red, green, blue with some random doubles.
        this->red = ((double)(rand()%100))/100;
        this->green = ((double)(rand()%100))/100;
        this->blue = ((double)(rand()%100))/100;
    }
    
    void setColour(GLfloat red = 1.0, /**< Red value of color ranging 0-1 */
                   GLfloat green = 0.0, /**< Green value of color ranging 0-1 */
                   GLfloat blue = 0.0 /**< Blue value of color ranging 0-1 */
                   ){
        /// A method to set the drawing color of the ShapeDrawer object to the given values.
        /** By default, red color is chosen if this method is not called after object creation. */
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
    
    void setPointSize(GLfloat pointSize /**< Point size in pixels */
                      ) {
        /// A method to set the pixel draw size of ShapeDrawer object.
        this->pointSize = pointSize;
    }
    
    void drawPixel(GLint x, /**< X coordinate of the pixel to be illuminated */
                   GLint y /**< Y coordinate of the pixel to be illuminated */
                   ) {
        /// A method to illuminate a pixel with given coordinates on screen.
        /** The given pixel is illuminated with the drawing color of the ShapeDrawer object. */
        glColor3f(red, green, blue);
        glPointSize(pointSize);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
    }
    
    void drawLine(int x1, /**< X coordinate of the starting point */
                  int y1, /**< Y coordinate of the starting point */
                  int x2, /**< X coordinate of the ending point */
                  int y2 /**< Y coordinate of the ending point */
                  ){
        
        /// A method to draw a line segment between two given points using Bresenham's Algorithm
        /** The line is drawn using the current color of ShapeDrawer object */
                      
        int dx = abs(x2 - x1); // Find the magnitude of change in X-Direction
        int dy = abs(y2 - y1); // Find the magnitude of change in Y-Direction
        int xDirection = 0, yDirection = 0, swapStatus = 0;
        int i, x = x1, y = y1;
        
        xDirection = direction(x1, x2); //Find whether X is increasing or decreasing
        yDirection = direction(y1, y2); //Find whether Y is increasing or decreasin
        
        if(dy > dx){
            swap(&dy, &dx); // If magnitude of slope is greater than 1, swap dx and dy
            swapStatus = 1; // Toggle the swap flag.
        }
        
        int d = 2*dy - dx; // Initial value for decision variable
        int dNE = 2*(dy - dx); // Change in value of decision variable of North East pixel is illuminated
        int dE = 2*dy; // Change in value of decision variable of East pixel is illuminated
                      
        for(i = 1; i <= dx; i++){ // Start iterating in X direction. (This will iterate in Y direction if dy and dx are swapped)
            drawPixel(x, y); // Illuminate the first pixel.
            
            if(d >= 0) // Select North East pixel if d >= 0
            {
                if(swapStatus)
                    x = x + xDirection; // Increment x if we are moving along Y direction
                else
                    y = y + yDirection; // Increment y if we are moving along X direction.
                
                d = d + dNE; // Change the value of decision variable accordingly.
            }
            else
                d = d + dE;
            
            if(swapStatus)
                y = y + yDirection; // Move along Y axis if the slope of line is greater than 1 i.e. dy and dx were swapped.
            else
                x = x + xDirection; // Move along X in the other case.
            
            
        }
    }
    
    void drawLineAtAngle(GLint x1, /**< X coordinate of the starting point */
                         GLint y1, /**< Y coordinate of the starting point */
                         double angle, /**< Angle made by the line with the positive X direction */
                         double length /**< Length of the line segment */
                         ){
        
        /// A method to draw a line segment given it's starting point, length and the angle made with positive X direction
        /** The line is drawn using the current color of ShapeDrawer object. This method uses Bresenham's Algorithm */
        
                             
        // Select the ending point based on the length and angle with positive X direction.
        int x2 = round(x1 + (length*cos(toRadians(angle))));
        int y2 = round(y1 + (length*sin(toRadians(angle))));
        
        // Call the drawLine method with starting and ending point as arguments.
        drawLine(x1, y1, x2, y2);
    
    }

    void drawCircle(int x0, /**< X coordinate of the centre */
                    int y0, /**< Y coordinate of the centre */
                    int r0 /**< Radius of the circle */
                    ){
        /// A method to draw a circle using midpoint algorithm with constant increments given it's centre and radius.
        /** The circle is drawn using the current color of ShapeDrawer object */

        // We draw only 1/8 of a circle and plot remaining points using symmetry.
                        
        int x = 0; // X coordinate of first point.
        int y = r0; // Y coordinate of first point.
        int d = 1-r0; // Initial value of decision variable
                        
        // Method of second order difference
        int deltaE = 3;
        int deltaSE = -2*r0+5;
        
        while(x <= y){
            plotCircle(x,y,x0,y0); // Plot symmetrical points
            
            // Choose appropriate pixel based on decision variable.
            if(d<0){
                d = d+deltaE; // Increment the value of decision variable.
                deltaE = deltaE+2;
                deltaSE = deltaSE+2; // Method of second order difference
            }
            else {
                d = d+deltaSE;
                deltaE = deltaE+2;
                deltaSE = deltaSE+4;
                y--;
            }
            x++;
        }
    }
};


#endif

/* ShapeDrawer_h */
