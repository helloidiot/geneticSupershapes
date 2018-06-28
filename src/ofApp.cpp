#include "ofApp.h"
#define FRAME_WIDTH 80
#define FRAME_HEIGHT 60
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(35);
    popmax = 8;
    mutationRate = ofRandom(0.6);
    shapeforest.setup(mutationRate, popmax);
    
    ofSetVerticalSync(true);
    ofEnableDepthTest();

    l = ofColor::fromHsb(180, 180, 150);
    r = ofColor::fromHsb(255, 180, 150);
    
    cam.setFov(20);
    cam.setPosition(0, 0, 3500);
    lightL.setDirectional();
    lightL.setDiffuseColor(l);
    lightL.setSpecularColor(l);
    lightL.setOrientation(ofVec3f(0,-60,45));
    lightR.setDirectional();
    lightR.setDiffuseColor(r);
    lightR.setSpecularColor(r);
    lightR.setOrientation(ofVec3f(0,60,45));
}
//--------------------------------------------------------------
void ofApp::update(){
    time++;
    shapeforest.update();

}
//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    ofTranslate(-ofGetWidth()/2, ofGetHeight() / 2);
    
    ofEnableLighting();lightL.enable();lightR.enable();
    shapeforest.draw();
    lightL.disable();lightR.disable();ofDisableLighting();
    cam.end();

}
//--------------------------------------------------------------
void ofApp::displayInfo(){

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'g' || key == 'G') {
        shapeforest.selection();
        shapeforest.generate();
    }
     else if (key>=48 && key <=57 ) {
        shapeforest.pick(ofToInt(ofToString(char(key))));
    }
    

    
}


