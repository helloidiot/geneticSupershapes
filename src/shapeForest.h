#pragma once
#include "ofMain.h"
#include "Tree.h"
#include "superShape.h"

class shapeForest{

  public:
    shapeForest();
    void setup(float m, int num);
    void selection();
    void generate();
    void draw();
    void update();
    void pick(int n);

    float mutationRate;                 // Mutation rate
    vector<superShape> shapes;          // Vector to hold the current population
    vector<superShape> matingPool;     // Vector which we will use for our "mating pool"
    int spacing = 500;
    int locX, locY;
};
