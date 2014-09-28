/*
 * Genetic Algorithm
 */
#include "genetic.h"
#include <malloc.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>


Genetic :: Genetic(int a,float** B)
{
	nocities = a ;
	distances = B ;

	int i,j;

	//(*generation)[nocities] = malloc(sizeof(*generation) * POP_SIZE); // generation[POP_SIZE][nocities]

	generation = new int*[POP_SIZE+1];
	
	for(i = 1; i <= POP_SIZE; i++)
	{
		generation[i] = new int[nocities+1];
		for(j = 1; j <= nocities; j++)
		{
			generation[i][j] = j;
		}	
	}

}			

int* Genetic::getsoln(){
	
	Initializer();
	printgen();

	return NULL;
}

void Genetic :: Initializer ()
{
	int i,j;

	for(i = 1; i <= POP_SIZE; i++)
	{
		std::random_shuffle (&generation[i][1],&generation[i][nocities]+1);
		//std::cerr << cost(&generation[i][0]) << "\n";
	}
}

void Genetic::printgen()
{
	int i,j;
	
	for(i = 1; i <= POP_SIZE; i++)
	{
		for(j = 1; j <= nocities; j++)
		{
			std::cout <<  generation[i][j] << " ";
		}
		std::cout << "\n";	
	}
}

int Genetic::cost(int* tour)
{
	int i;
	int sum = 0;
	for(i=1;i<nocities;i++)
	{
		sum += distances[tour[i]][tour[i+1]];
	}
	return sum;
}
