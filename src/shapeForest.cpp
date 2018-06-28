#include "shapeForest.h"

//-------------------------------------------------------
shapeForest::shapeForest() {
}
//-------------------------------------------------------
void shapeForest::setup(float m, int num)
{
    mutationRate = m;
    shapes.clear();

    for (int x=0; x<num; x++){
        superShape tempShape;
        tempShape.setup(10); // Assign number of genes
        shapes.push_back(tempShape);
    }
}

//-------------------------------------------------------
void shapeForest::update(){
}

//-------------------------------------------------------
// Generate a mating pool
void shapeForest::selection() {

    // Clear the vector
    matingPool.clear();
    
    // Calculate total fitness of whole population
    float maxFitness = 0;
    for(int i = 0; i < shapes.size(); i++){
      maxFitness += shapes[i].fitness;
    }
    
    // Calculate fitness for each member of the population (scaled to value between 0 and 1)
    // Based on fitness, each member will get added to the mating pool a certain number of times
    // A higher fitness = more entries to mating pool = more likely to be picked as a parent
    // A lower fitness = fewer entries to mating pool = less likely to be picked as a parent
    
    for (int i = 0; i < shapes.size(); i++) {
        float fitnessNormal = ofMap(shapes[i].fitness, 0, maxFitness, 0, 1);
        int n = (int) (fitnessNormal * 100);  // Arbitrary multiplier
        for (int j = 0; j < n; j++) {
            matingPool.push_back(shapes[i]);
        }
    }

}
//------------------------------------------------------------
// Create a new generation
void shapeForest::draw(){
    
    ofTranslate(-spacing/4,-spacing/4);
    
    for(int i =0; i < shapes.size(); i++)
    {
        ofEnableLighting();
        
        // Draw the shape
        shapes[i].draw(0, 0); //just drawing the shapes
        ofDisableLighting();
        
        // Draw the fitness info
        ofSetColor(255);
        ofDrawBitmapString(ofToString(i) + ":" + ofToString(shapes[i].fitness), -10, 20);
        ofTranslate(spacing, 0);
        shapes[i].update();
        
        // Line break
        if ( i == 3){
            ofTranslate(-spacing*4, -(spacing/1.1));
        }
    }

}
//------------------------------------------------------------
// Create a new generation
void shapeForest::generate() {
        
    // Refill the shapes with children from the mating pool
    for (int i = 0; i < shapes.size(); i++) {
      int a = int(ofRandom(matingPool.size()));
      int b = int(ofRandom(matingPool.size()));
        
      superShape partnerA = matingPool[a];
      superShape partnerB = matingPool[b];
      shapeDNA childDNA = partnerA.shapedna.crossover(partnerB.shapedna);
      shapes[i].calcPhenotype();
      childDNA.mutate(mutationRate);
      superShape child;
      child.setup(childDNA);
      shapes[i] = child;
      shapes[i].calcPhenotype();
        
    }
}
//------------------------------------------------------------
void shapeForest::pick(int n){
     shapes[n].fitness++;
}
