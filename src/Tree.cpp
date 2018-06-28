#include "Tree.h"
#define GENE_SIZE 1
//#define GENE_SIZE 5

// Initial branch width
// Leaf Size
// Leaf colour R
// Leaf colour G
// Leaf colour B
// Leaf shape


//-------------------------------------------------------
Tree::Tree(){
    geneSize = GENE_SIZE;
    fitness = 0;
}
//-------------------------------------------------------
void Tree::setup(DNA _dna){
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    calcPhenotype();
}
//-------------------------------------------------------
void Tree::setup(int _numOfGenes)
{
    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    calcPhenotype();
}
//-------------------------------------------------------
// This function turns the floats into a tree
void Tree::calcPhenotype(){
    //decode the genes into variables for drawing
    branchOffset = ofMap(dna.genes[0],0,1,0,1);
    startTheta = ofMap(dna.genes[1],0,1, 0, 30);
    startLength = ofMap(dna.genes[2],0,1, 20, 100);
    minLength = ofMap(dna.genes[3],0,1, 3, 10);
    branchReduce = ofMap(dna.genes[4],0,1, 0.45, 0.7);
    thetaVariance = ofMap(dna.genes[5],0,1, 0, 30);
    reduceVariance = ofMap(dna.genes[6],0,1, 0, 0.1);
    startAngle = ofMap(dna.genes[7],0,1, 0, 30);
    
    initialTrunkWidth = ofMap(dna.genes[8], 0, 1, 1, 5);
    leafSize = ofMap(dna.genes[9], 0, 1, 1, 10);
    r = ofMap(dna.genes[10], 0, 1, 0, 255);
    g = ofMap(dna.genes[11], 0, 1, 0, 255);
    b = ofMap(dna.genes[12], 0, 1, 0, 255);
    leafColor = ofColor(r, g, b, 255);
    
    
        seed = ofRandom(1000,65000);
}
void Tree::branch(float b_length, float theta)
{
    if(count > 500)
    {
        cout << "max branches reached" << endl;
    }
    
    if(b_length > minLength )
    {
        ofPushStyle();
        ofSetColor(0);
        ofSetLineWidth(initialTrunkWidth);
        ofDrawLine(0,0,0,-b_length);
        ofPopStyle();
        
        ofPushMatrix();
        ofTranslate(0,-b_length);
        ofRotate(theta + ofRandom(-thetaVariance, thetaVariance));
        branch(b_length * (branchReduce + ofRandom(-reduceVariance, reduceVariance)), theta);
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(0,-b_length * branchOffset);
        ofRotate(-theta + ofRandom(-thetaVariance, thetaVariance));
        branch(b_length * (branchReduce + ofRandom(-reduceVariance, reduceVariance)), theta);
        ofPopMatrix();
    }
    else{
        
        for(int i = 0; i < 20; i++)
        {
            ofSetColor(leafColor);
            ofDrawEllipse(ofRandom(-4,4),ofRandom(-4,4),1,1);
        }
    }
    
}

//--------------------------------------------------------
// Draws the tree
void Tree::draw(int x, int y){
    ofSeedRandom(seed);
    count = 0;
    ofPushMatrix();
    ofRotate(ofRandom(-startAngle, startAngle));
    branch(startLength, startTheta);
    ofPopMatrix();
}
////--------------------------------------------------------
//// Draws the tree
//void Tree::print(){
//    cout << branchOffset << endl;
//    cout <<     startTheta << endl;
//    cout <<     startLength << endl;
//        cout << minLength << endl;
//        cout << branchReduce << endl;
//        cout << thetaVariance << endl;
//       cout <<  reduceVariance << endl;
//        cout << startAngle << endl;
//        cout << seed << endl;
//}
