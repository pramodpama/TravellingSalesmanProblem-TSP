/*
 * genetic.h
 *
 *  Created on: 28-Sep-2014
 *      Authors: Kaushik, Pramod
 */

#ifndef GENETIC_H_
#define GENETIC_H_

#define POP_SIZE 100
#define CHANGED true
#define UNCHANGED false


class Tour {

				float cost;
			public:
				int *order;

			public:
				Tour();
				float getcost(){
					return cost;
				}
				void setcost();
				void randomise();
				void print();
				bool operator<(Tour);
				void optimize();
				void mutate();
	};


class Generation {

	
		Tour candidates[POP_SIZE+1];

	public:
		bool solnflag;
		Tour soln;
		
		void print();
		void initialize ();

		void crossover();
		
		void ordercrossover(Tour* parent1, Tour* parent2,int ,int);
		bool search(int a, int* arr);

		void natseln(int);
		void setmaxtours(Tour**,int);
		void setmintours(Tour**,int);
		void setmintours(Tour*,int,Tour* src);
		int getminindex(Tour**,int);
		int getmaxindex(Tour**,int);
		int getmaxindex(Tour*,int);
		void bestoffour(Tour* , Tour*, Tour parent1 ,Tour parent2);
		void optimize();
		void generate_mutate(int num);


};

class Genetic {
	Generation gen;
	public:
		 //Genetic(int a, float** B);
		 int* getsoln();
};


#endif /* GENETIC_H_ */
