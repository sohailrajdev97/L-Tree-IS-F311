#ifndef Lindenmayer_h
#define Lindenmayer_h

#include <string>
#include <map>
#include <stack>
#include "ShapeDrawer.h"

using namespace std;

//! A class to draw Lindenmayer Systems

class Lindenmayer {
    
private:
    
    struct turtleState {
        // A structure to store the turtle's state variables.
        int x, y;
        double branchLength, angle, red, green, blue, pointSize;
    };
    
    // The use of these has been explained in the corresponding setter methods.
    int currentX, currentY, iterations;
    double branchLength, pointSize, rotationAngle, branchScaleFactor, pointScaleFactor;
    string axiom, generation;
    
    // A map to store the rules of L-System. The map stores the value which has to be replaced and also the new value.
    map<string, string> rules;
    
    // A stack to store the states of turtle.
    stack<turtleState> stateStack;
    
    // A ShapeDrawer object to draw the L-Sytems after calculations have been done.
    ShapeDrawer sd;
    

public:
    
    Lindenmayer(string axiom, /**< The axiom for L-System */
                int iterations /**< Number of times the given rules have to be applied to the axiom */
                ){
        
        /// Constructor method to initialise values of Lindenmayer object.
        
        /** The constructor takes in axiom and number of iterations as a parameter and sets some default values for other fields */
        currentX = 0;
        currentY = 0;
        this->iterations = iterations;
        branchLength = 100;
        pointSize = 1.0;
        rotationAngle = 20.0;
        branchScaleFactor = 0.75;
        pointScaleFactor = 1.0;
        this->axiom = axiom;
        generation = "";
    }
    
    // Setters
    void setX(int x /**< The new X-Coordinate */) {
        /// Setter method for setting the current X-Coordinate of drawing turtle on screen.
        
        /** Initial X-Coordinate = 0 */
        
        currentX = x;
    }
    
    void setY(int y /**< The new T-Coordinate */){
        /// Setter method for setting the current Y-Coordinate of drawing turtle on screen.
        
        /** Initial Y-Coordinate = 0 */
        currentY = y;
    }
    
    void setAngle(double angle /**< The rotation angle for L-System in degrees*/){
        /// Setter method for setting the rotation angle of the turtle corresponding to + and - in the generation string.
        
        /** Initial rotation angle = 20 degrees */
        rotationAngle = angle;
    }
    
    void setBranchLength(double branchLength /**< The branch length for L-System */){
        /// Setter method for setting the number of pixels the turtle moves in one step.
        
        /** Initial branch length = 100px */
        
        this->branchLength = branchLength;
    }
    
    void setBranchScaleFactor(double branchScaleFactor /**< The branch scale factor for L-System */){
        /// Setter method for setting the factor with which the branch length is multiplied whenever branching off at a point.
        
        /** Initial branch scale factor = 0.75 */
        
        this->branchScaleFactor = branchScaleFactor;
    }
    
    void setPointScaleFactor(double pointScaleFactor /**< The point scale factor for L-System */){
        /// Setter method for setting the factor with which the point size is multiplied whenever branching off at a point.
        
        /** Initial point scale factor = 1.0 */
        
        this->pointScaleFactor = pointScaleFactor;
    }
    
    void setPointSize(double pointSize /**< The point size for L-System */){
        /// Setter method for setting the initial point size.
        
        /** Initial point size = 1.0 */
        
        this->pointSize = pointSize;
        sd.setPointSize(pointSize);
    }
    
    void addRule(string rule /**< The rule which has to be applied to the axiom. Rule should be of the form "X=ABCDEF" if X has to be replace with ABCDEF in subsequent iterations*/){
        /// A method to add rules to the L-System.
        size_t pos = rule.find('=');
        rules.insert(pair<string, string> (rule.substr(0, pos), rule.substr(pos+1)));
    }
    
    // Getters
    int getX(){
        /// A method to get the current X-Coordinate of turtle on screen.
        return currentX;
    }
    
    int getY(){
        /// A method to get the current Y-Coordinate of turtle on screen.
        return currentY;
    }
    
    double getAngle(){
        /// A method to get the current rotation angle of turtle on screen.
        return rotationAngle;
    }
    
    string getAxiom(){
        /// A method to get the axiom of current L-System.
        return axiom;
    }
    
    double getBranchLength(){
        /// A method to get the current branch length of L-System.
        return branchLength;
    }
    
    double getBranchScaleFactor(){
        /// A method to get the current value of branchScaleFactor.
        return branchScaleFactor;
    }
    
    double getPointSize(){
        /// A method to get the current value of point size.
        return pointSize;
    }
    
    double getPointScaleFactor() {
        /// A method to get the current value of pointScaleFactor.
        return pointScaleFactor;
    }
    

    void draw(double colors[][3] = NULL /**< A 2-D array of colors which has to be passed to the function. A sample array of 2 colors is {{r1, g1, b1}, {r2, g2, b2}}  where r, g, b are the red, green, blue values for a color respectively*/){
        
        /// A method to draw the L-System given the axiom and set of rules.
        
        int i,j;
        
        if(generation.length() == 0) // Do not generate the generation string if it has already been generated
        {
            map<string, string>::iterator it;
            generation = axiom;
            string tGeneration = ""; // A temporary string to store the current generation of L-system until the final generation is derived
            
            // Generating the final generation string.
            for(i=0; i < iterations; i++){
                
                size_t length = generation.length();
                
                for(j=0; j < length; j++){
                    
                    // Find if there is a rule corresponding to the current character being read,
                    it = rules.find(generation.substr(j, 1));
                    
                    if(it != rules.end()){
                        // Replace the character if there is a corresponding rule
                        tGeneration = tGeneration + rules.at(generation.substr(j, 1));
                    } else {
                        tGeneration = tGeneration + generation.substr(j, 1);
                    }
                }
                generation = tGeneration;
                tGeneration = "";
            }
        }
        
        size_t length = generation.length();

        
        // Setup the drawing variables.
        double currentAngle = 0.0;
        double currentBranchLength = branchLength;
        double currentPointSize = pointSize;
        double red = 1, green = 0, blue = 0;
        
        for(i=0; i < length; i++){
            
            // Start reading the final generation string.
            
            char next = generation.at(i);
            
            if(next == 'F'){
                // Draw a line at the current angle using the ShapeDrawer object when 'F' is encountered.
                sd.drawLineAtAngle(currentX, currentY, 90 - currentAngle, currentBranchLength);
                
                //Update the turtle's position to the end of newly drawn line.
                currentX += round(currentBranchLength*sin(toRadians(currentAngle)));
                currentY += round(currentBranchLength*cos(toRadians(currentAngle)));
            }
            
            if(next == '-') // Right rotation
                currentAngle += rotationAngle;
            
            if(next == '+') // Left rotation
                currentAngle -= rotationAngle;
            
            if(next == 'C'){
                // Color changing
                int colorNum = generation.at(i+1) - 48;
                red = colors[colorNum][0];
                green = colors[colorNum][1];
                blue = colors[colorNum][2];
                sd.setColour(red, green, blue);
                i = i+1;
            }
            
            if(next == '[') {
                
                // Save the state of turtle when '[' is encountered.
                
                struct turtleState currentState;
                currentState.x = currentX;
                currentState.y = currentY;
                
                currentState.branchLength = currentBranchLength;
                currentState.pointSize = currentPointSize;
                currentState.angle = currentAngle;

                currentState.red = red;
                currentState.green = green;
                currentState.blue = blue;
                stateStack.push(currentState);
                
                // Scale the point size and branch size according to the corresponding scale factors.
                currentBranchLength *= branchScaleFactor;
                currentPointSize *= pointScaleFactor;
                
                sd.setPointSize(currentPointSize);
            }
            
            if(next == ']') {
                
                // Reapply the last saved state of the turtle when ']' is encountered.
                
                struct turtleState newState = stateStack.top();
                
                currentX = newState.x;
                currentY = newState.y;
                
                currentAngle = newState.angle;
                currentBranchLength = newState.branchLength;
                currentPointSize = newState.pointSize;
                
                red = newState.red;
                green = newState.green;
                blue = newState.blue;
                
                // Set the new color and point size.
                sd.setColour(red, green, blue);
                sd.setPointSize(pointSize);
                
                stateStack.pop();
            }
            
            
        }

    }
    
};

#endif /* Lindenmayer_h */
