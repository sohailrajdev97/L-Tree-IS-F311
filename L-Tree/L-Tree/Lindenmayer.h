#ifndef Lindenmayer_h
#define Lindenmayer_h

#include <string>
#include <map>
#include <iostream>
#include "ShapeDrawer.h"

using namespace std;

class Lindenmayer {
    
private:
    
    int currentX, currentY;
    double rotationAngle;
    string axiom;
    map<string, string> rules;
    ShapeDrawer sd;

public:
    
    // Constructor
    Lindenmayer(){
        currentX = 0.0;
        currentY = 0.0;
        rotationAngle = 0.0;
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
    void draw(int iterations){
        
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
        cout << generation;
    }
};

#endif /* Lindenmayer_h */
