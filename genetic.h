/*
 * genetic.h
 *
 *  Created on: 28-Sep-2014
 *      Authors: Kaushik, Pramod
 */

#ifndef GENETIC_H_
#define GENETIC_H_

#define POP_SIZE 100

class Tour {

				int cost;
			public:
				int *order;

			public:
				Tour();
				int getcost(){
					return cost;
				}
				void setcost();
				void randomise();
				void print();
	};


class Generation {

	
		Tour soln;
		Tour candidates[POP_SIZE+1];

	public:
		void print();
		void initialize ();
		void crossover();
		Tour* simplecrossover(Tour parent1, Tour parent2);
		void ordercrossover(Tour* children,Tour parent1, Tour parent2);
		bool search(int a, int* arr);
};

class Genetic {
	Generation gen;
	public:
		 //Genetic(int a, float** B);
		 int* getsoln();
};


#endif /* GENETIC_H_ */
