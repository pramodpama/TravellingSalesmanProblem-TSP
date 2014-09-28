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
				int *order;

			public:
				Tour();
				int getcost(){
					return cost;
				}
				void setcost();
				void randomise();
				void print();
				bool operator<(Tour);
	};


class Generation {

	
		Tour soln;
		Tour candidates[POP_SIZE+1];

	public:
		void print();
		void initialize ();
		void natseln(int);
		void setmaxtours(Tour**,int);
		void setmintours(Tour**,int);
		int getminindex(Tour**,int);
		int getmaxindex(Tour**,int);
	//	void

};

class Genetic {
	Generation gen;
	public:
		 //Genetic(int a, float** B);
		 int* getsoln();
};


#endif /* GENETIC_H_ */
