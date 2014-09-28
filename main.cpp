#include <iostream>
#include "genetic.h"

using namespace std;

int main()
{
	int nocities;
	float **distances;
	float coordinates;

	cin >> nocities;
	distances = new float*[nocities+1];
	for(int i = 1; i <= nocities; ++i) {
    	distances[i] = new float[nocities+1];
	}
	
	for(int i=1; i<= nocities*2; i++){
		cin >> coordinates;
	}

	for(int i=1; i<= nocities; i++){
		for(int j=1; j<= nocities; j++){
			cin >> distances[i][j];
		}
	}
	cerr << "Input read successfully" << endl;

	Genetic geneticsolver(nocities,distances);

	geneticsolver.getsoln();

	return 0;
}
