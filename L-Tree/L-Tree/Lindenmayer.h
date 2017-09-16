#ifndef Lindenmayer_h
#define Lindenmayer_h

#include <string>
#include <map>
#include <stack>
#include <iostream>
#include "ShapeDrawer.h"

using namespace std;

struct coordinates {
    int x;
    int y;
    double angle;
};

class Lindenmayer {
    
private:
    
    int currentX, currentY;
    double rotationAngle;
    string axiom;
    map<string, string> rules;
    stack<coordinates> coordinateStack;
    ShapeDrawer sd;

public:
    
    // Constructor
    Lindenmayer(){
        currentX = 0;
        currentY = 0;
        rotationAngle = 0.0;
    }
    
    // Setters
    void setX(int x) {
        currentX = x;
    }

    double angleConvert(double ang){
        double x = ang*M_PI/180;
        return x;
    }
    
    void setY(int y){
        currentY = y;
    }
    
    void setAngle(double angle){
        rotationAngle = angle;
    }
    
    void setAxiom(string axiom){
        this->axiom = axiom;
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
    
    //Draw Function
    void draw(int iterations, double colors[][3] = NULL){
        
        int i,j;
        map<string, string>::iterator it;
        string generation = axiom;
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
        
        
        cout << generation << endl;
        
        size_t length = generation.length();
        double currentAngle = 0.0;
        
        for(i=0; i < length; i++){
            
            char next = generation.at(i);
            
            if(next == 'F'){
                sd.drawLineAtAngle(currentX, currentY, 90 - currentAngle, 10);
                currentX += 10*sin(angleConvert(currentAngle));
                currentY += 10*cos(angleConvert(currentAngle));
            }
            
            if(next == '-')
                currentAngle += rotationAngle;
            
            if(next == '+')
                currentAngle -= rotationAngle;
            
            if(next == 'C'){
                int colorNum = generation.at(i+1) - 48;
                sd.setColour(colors[colorNum][0], colors[colorNum][1], colors[colorNum][2]);
                i = i+1;
            }
            
            if(next == '[') {
                struct coordinates a;
                a.x = currentX;
                a.y = currentY;
                a.angle = currentAngle;
                coordinateStack.push(a);
            }
            
            if(next == ']') {
                struct coordinates a = coordinateStack.top();
                currentX = a.x;
                currentY = a.y;
                currentAngle = a.angle;
                coordinateStack.pop();
            }
            
            
        }
    }
};

#endif /* Lindenmayer_h */
