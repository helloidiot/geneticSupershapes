#pragma once
#include "ofMain.h"
#include "shapeForest.h"
#include "superShape.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
        void displayInfo();

        int popmax;
        float mutationRate;
        bool activate;
    
        shapeForest shapeforest;
        superShape shapeshape;

        ofCamera cam;
        ofLight lightR;
        ofColor r;
        ofLight lightL;
        ofColor l;
        float time;

};
