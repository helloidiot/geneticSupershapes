#include "shapeDNA.h"

shapeDNA::shapeDNA(){
    mutationAmount = 1;
}

//-------------------------------------------------------
void shapeDNA::setup(int _numOfGenes, int _geneSize)
{
    numOfGenes = _numOfGenes;
    geneSize = _geneSize;

    for (int i = 0; i < numOfGenes; i++) {
        for (int j = 0; j < geneSize; j++) {
           genes.push_back(ofRandom(1));
        }
    }
}
//------------------------------------------------------------------
// Crossover
shapeDNA shapeDNA::crossover(shapeDNA partner) {
    // A new child
    shapeDNA child;
    child.setup(numOfGenes, geneSize);
    int midpoint = int(ofRandom(genes.size())); // Pick a midpoint (NO RESPECT FOR GENE INTEGRITY)

    // Half from one, half from the other
    for (int i = 0; i < genes.size(); i++) {
        if (i > midpoint) child.genes[i] = genes[i];
        else              child.genes[i] = partner.genes[i];
    }
    return child;

}
//------------------------------------------------------------------
void shapeDNA::mutate(float mutationRate) {
    for (int i = 0; i < genes.size(); i++) {
      if (ofRandom(1) < mutationRate) {
        genes[i] = ofRandom(mutationAmount);
      }
   }
}
