#ifndef Lindenmayer_h
#define Lindenmayer_h

#include <string>
#include <map>
#include <stack>
#include <iostream>
#include "ShapeDrawer.h"

using namespace std;

struct turtleState {
    int x, y;
    double branchLength, angle, red, green, blue, pointSize;
};

class Lindenmayer {
    
private:
    
    int currentX, currentY, iterations;
    double branchLength, pointSize, rotationAngle, branchScaleFactor, pointScaleFactor;
    string axiom, generation;
    map<string, string> rules;
    stack<turtleState> stateStack;
    ShapeDrawer sd;

public:
    
    // Constructor
    Lindenmayer(string axiom, int iterations){
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
    void setX(int x) {
        currentX = x;
    }
    
    void setY(int y){
        currentY = y;
    }
    
    void setAngle(double angle){
        rotationAngle = angle;
    }
    
    void setBranchLength(double branchLength){
        this->branchLength = branchLength;
    }
    
    void setBranchScaleFactor(double branchScaleFactor){
        this->branchScaleFactor = branchScaleFactor;
    }
    
    void setPointScaleFactor(double pointScaleFactor){
        this->pointScaleFactor = pointScaleFactor;
    }
    
    void setPointSize(double pointSize){
        this->pointSize = pointSize;
        sd.setPointSize(pointSize);
    }
    
    void addRule(string rule){
        size_t pos = rule.find('=');
        rules.insert(pair<string, string> (rule.substr(0, pos), rule.substr(pos+1)));
    }
    
    // Getters
    int getX(){
        return currentX;
    }
    
    int getY(){
        return currentY;
    }
    
    double getAngle(){
        return rotationAngle;
    }
    
    string getAxiom(){
        return axiom;
    }
    
    double getBranchLength(){
        return branchLength;
    }
    
    double getBranchScaleFactor(){
        return branchScaleFactor;
    }
    
    double getPointSize(){
        return pointSize;
    }
    
    double getPointScaleFactor() {
        return pointScaleFactor;
    }
    
    //Draw Function
    void draw(double colors[][3] = NULL){
        
        int i,j;
        
        if(generation.length() == 0)
        {
            map<string, string>::iterator it;
            generation = axiom;
            string tGeneration = "";
            
            for(i=0; i < iterations; i++){
                
                size_t length = generation.length();
                
                for(j=0; j < length; j++){
                    
                    it = rules.find(generation.substr(j, 1));
                    
                    if(it != rules.end()){
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
        
        double currentAngle = 0.0;
        double currentBranchLength = branchLength;
        double currentPointSize = pointSize;
        double red = 1, green = 1, blue = 1;
        
        for(i=0; i < length; i++){
            
            char next = generation.at(i);
            
            if(next == 'F'){
                sd.drawLineAtAngle(currentX, currentY, 90 - currentAngle, currentBranchLength);
                currentX += currentBranchLength*sin(toRadians(currentAngle));
                currentY += currentBranchLength*cos(toRadians(currentAngle));
            }
            
            if(next == '-')
                currentAngle += rotationAngle;
            
            if(next == '+')
                currentAngle -= rotationAngle;
            
            if(next == 'C'){
                int colorNum = generation.at(i+1) - 48;
                red = colors[colorNum][0];
                green = colors[colorNum][1];
                blue = colors[colorNum][2];
                sd.setColour(red, green, blue);
                i = i+1;
            }
            
            if(next == '[') {
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
                
                currentBranchLength *= branchScaleFactor;
                currentPointSize *= pointScaleFactor;
                
                sd.setPointSize(currentPointSize);
            }
            
            if(next == ']') {
                struct turtleState newState = stateStack.top();
                
                currentX = newState.x;
                currentY = newState.y;
                
                currentAngle = newState.angle;
                currentBranchLength = newState.branchLength;
                currentPointSize = newState.pointSize;
                
                red = newState.red;
                green = newState.green;
                blue = newState.blue;
                
                sd.setColour(red, green, blue);
                sd.setPointSize(pointSize);
                stateStack.pop();
            }
            
            
        }

    }
    
};

#endif /* Lindenmayer_h */
