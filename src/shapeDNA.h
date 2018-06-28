#pragma once
#include "ofMain.h"

class shapeDNA{

	public:
		shapeDNA();
		void setup(int _numOfGenes, int _geneSize);
		void draw();
        shapeDNA crossover(shapeDNA partner);
        void mutate(float mutationRate);

		vector<float> genes;
		int numOfGenes;
		int geneSize;
        float fitness;
        float mutationAmount;
};
