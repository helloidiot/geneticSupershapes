#pragma once
#include "ofMain.h"
#include "shapeDNA.h"

class superShape {
    
public:
    superShape();
    void setup(shapeDNA _shapedna);
    void setup(int _numOfGenes);
    void draw();
    void update();
    void keyPressed(int key);
    
    void calcPhenotype();
    void draw(int x, int y);
    void updateVertices();
    float getFitness ();
    superShape crossover(superShape partner);
    

    void mutate(float mutationRate);

    float n1value; //= ofRandomuf() * 0.8f + 20.0f;
    float n2value; //= ofRandomuf() * 0.8f + 2.0f;
    float n3value; //= ofRandomuf() * 0.8f + 2.0f;
    float n4value; //= ofRandomuf() * 0.8f + 2.0f;
    float a1value; //= ofRandomuf() * 0.8f + 4.0f;
    float a2value; //= ofRandomuf() * 0.8f + 8.0f;
    float stepvalue; //= ofRandomuf() * 0.02f + 0.1f;
    
    shapeDNA shapedna;
    int numOfGenes, geneSize;
    float fitness;
    
    ofMesh mesh;
    ofVec3f sf3d(float x, float y);
    
    vector<int> lastRow;

    float seed = 0;
    int count = 0;

    float r, g, b;

    ofColor shapeColor;
    ofColor c;
    
    float time;
    float phase;
    float offset = 0;
    
    
    vector<ofVec3f> offsets;
    
    
};

