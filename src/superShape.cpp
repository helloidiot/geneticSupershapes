#include "superShape.h"
#include "ofxMeshUtils.h"
#define GENE_SIZE 1

//-------------------------------------------------------
superShape::superShape(){
    geneSize = GENE_SIZE;
    fitness = 0;
}


//-------------------------------------------------------
void superShape::setup(shapeDNA _shapedna){
    shapedna = _shapedna;
    geneSize = shapedna.geneSize;
    numOfGenes = shapedna.numOfGenes;
    
    calcPhenotype();
}
//-------------------------------------------------------
void superShape::setup(int _numOfGenes)
{
    numOfGenes = _numOfGenes;
    shapedna.setup(numOfGenes, geneSize);
    
    calcPhenotype();
}

//-------------------------------------------------------
void superShape::calcPhenotype(){
    
    //decode the genes into variables for drawing
    // Play with these to get more varied shapes...
    
    a1value = ofMap(shapedna.genes[0], 0, 1, 0.8, 1.8, true);
    a2value = ofMap(shapedna.genes[1], 0, 1, 0.8, 1.3, true);
    n1value = ofMap(shapedna.genes[2], 0, 1, 0.5, 4, true);
    n2value = ofMap(shapedna.genes[3], 0, 1, 0.8, 1.6, true);
    n3value = ofMap(shapedna.genes[4], 0, 1, 0.1, 1.5, true);
    n4value = ofMap(shapedna.genes[5], 0, 1, 0.1, 1.3, true);
    stepvalue = ofMap(shapedna.genes[6], 0, 1, 0.05, 0.2, true);

    r = ofMap(shapedna.genes[7], 0, 1, 0, 255);
    g = ofMap(shapedna.genes[8], 0, 1, 100, 255);
    b = ofMap(shapedna.genes[9], 0, 1, 235, 255);
    c = ofColor::fromHsb(r, g, b);
    shapeColor = ofColor(r, g, b);

    seed = ofRandom(1000,65000);
}

//--------------------------------------------------------------
ofVec3f superShape::sf3d(float x, float y) {
    
    float i = -PI + x * stepvalue;
    
    float j = -PI / 2.0 + y * stepvalue;
    
    float raux1 = pow(abs(1/a1value*abs(cos(n1value * i/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*i/4))),n4value);
    
    float r1=pow(abs(raux1),(-1/n2value));
    float raux2=pow(abs(1/a1value*abs(cos(n1value*j/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*j/4))),n4value);
    float r2=pow(abs(raux2),(-1/n2value));
    float xx=r1*cos(i)*r2*cos(j) * 100.0f;
    float yy=r1*sin(i)*r2*cos(j) * 100.0f;
    float zz=r2*sin(j) * 100.0f;
    
    return ofVec3f(xx,yy,zz);
    
}

//--------------------------------------------------------------
void superShape::update(){
    
    time++;
    
    mesh.clear();
    
    int N_X = ceil((2.0 * PI) / stepvalue);
    int N_Y = ceil(PI / stepvalue);
    
    for(int x=0; x<N_X; x++) {
        for(int y=0; y<N_Y; y++) {
            // Add a vertex with sf3d function
            mesh.addVertex(sf3d(x,y));
            mesh.addColor(c);

        }
    }
    
    mesh.addVertex(sf3d(PI/stepvalue,PI/stepvalue));
    
    lastRow.clear();
    
    for(int x=0;x<N_X;x++) {
        for(int y=0;y<N_Y-1;y++) {
            
            if(x == N_X-1) {
                
                int idx1 = x*N_Y+y;
                int idx2 = x*N_Y+y+1;
                
                int idx3 = y+1;
                int idx4 = y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
            } else {
                int idx1 = x*N_Y+y;
                int idx2 = x*N_Y+y+1;
                
                int idx3 = (x+1)*N_Y+y+1;
                int idx4 = (x+1)*N_Y+y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
                if(y == N_Y-2) {
                    lastRow.push_back(idx2);
                }
            }
        }
    }
    
    int lastVertex = (int) mesh.getNumVertices()-1;
    
    for(int i=0;i<lastRow.size()-1;i++) {
        mesh.addTriangle(lastRow[i], lastRow[i+1], lastVertex);
    }
    mesh.addTriangle(lastRow[0],lastRow[lastRow.size()-1], lastVertex);
    
    ofxMeshUtils::calcNormals(mesh);

}

//--------------------------------------------------------------
void superShape::draw(int x, int y){
    
    ofSeedRandom(seed);
    offset = ofRandom(-a1value, a1value);
    float nx = ofMap(ofNoise(a1value), 0, 1, 0, 3);
    float ny = ofMap(ofNoise(a2value), 0, 1, 0, 3);
    glShadeModel(GL_FLAT);
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
    ofPushMatrix();
    ofRotateX((time * 0.1) + nx);
    ofRotateZ((time * 0.2) + ny);
//    ofRotateY(time * offset);
    
    // Update vertices positons based on noise vals
     updateVertices();
//    turbulence();
    
    ofDisableAlphaBlending();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
    
    // Draw the mesh
    // Translate x, y ????
    mesh.draw();
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
}


//--------------------------------------------------------------
void superShape::updateVertices(){
    
    int numVerts = mesh.getNumVertices();

    
    for (int v = 0; v < numVerts; v++){
        offsets.push_back(ofVec3f(ofRandom(1000), ofRandom(1000), ofRandom(1000)));
        ofVec3f vert = mesh.getVertex(v);
        ofVec3f timeOffsets = offsets[v];
        float t = time * 0.1;
        float timescale = stepvalue;
        float displacementScale = n1value;
        vert.x += (ofSignedNoise(t * timescale + timeOffsets.x )) * displacementScale;
        vert.y += (ofSignedNoise(t * timescale + timeOffsets.y )) * displacementScale;
        vert.z += (ofSignedNoise(t * timescale + timeOffsets.z )) * displacementScale;
        mesh.setVertex(v, vert);
    }
}

