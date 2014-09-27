/*
 * genetic.cpp
 *
 *  Created on: 28-Sep-2014
 *      Author: Kaushik, Pramod
 */


#include "genetic.h"
#include <algorithm>
#include <iostream>

extern int nocities;
extern float**  distances;

/*Genetic::Genetic(int a,float** B)
{
	nocities = a ;
	distances = B ;
}*/

int* Genetic::getsoln(){

	gen.initialize();
	gen.print();

	return NULL;
}

void Generation::initialize ()
{
	for(int i = 1; i <= POP_SIZE; i++)
	{
		candidates[i].randomise();
		//std::cerr << cost(&generation[i][0]) << "\n";
	}
}

void Generation::print()
{
	int i;

	for(i = 1; i <= POP_SIZE; i++)
	{
		std::cout << candidates[i].getcost() << " ";
		//candidates[i].print();
		std::cout << "\n";
	}
}

Tour::Tour()
{
	order = new int[nocities+1];

	for(int i=0; i<=nocities; i++){
		order[i] = i;
	}
}

void Tour::setcost()
{
	int i;
	int sum = 0;
	for(i=1;i<nocities;i++)
	{
		sum += distances[order[i]][order[i+1]];
	}
	cost = sum;
}

void Tour::randomise()
{
	for(int i = 1; i <= POP_SIZE; i++)
	{
		std::random_shuffle (&order[1],&order[nocities]+1);
		setcost();
	}
}

void Tour::print()
{
	for(int i = 1; i <= nocities; i++){
		std::cout << order[i];
	}
}
/*/Performs simple natural selection by removing few tours and duplicating some tours
void Genetic::natseln(int triplicates, int duplicates)
{
	int costs[POP_SIZE];

}*/

