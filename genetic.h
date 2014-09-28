/*
 * Genetic Algorithm
 */

#ifndef GENETIC_H
#define GENETIC_H

#define POP_SIZE 100 

class Genetic {

	
	int nocities;
	float**  distances;
	int **generation;

	public:
		 Genetic(int a, float** B);
		 
		 void Initializer ();

		 int cost(int* tour);

		 void printgen();

		 int* getsoln();


};




#endif 

