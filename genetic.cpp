/*
 * genetic.cpp
 *
 *  Created on: 28-Sep-2014
 *      Author: Kaushik, Pramod
 */


#include "genetic.h"
#include <algorithm>
#include <iostream>

extern const int nocities;
extern const float**  distances;

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
		candidates[i].randomise();                            // didn't understand this
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

	for(int i=0; i<=nocities; i++){       // i should be 1
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
/*/Performs simple natural selection by removing few Tours and duplicating some Tours
void Genetic::natseln(int triplicates, int duplicates)
{
	int costs[POP_SIZE];

}*/

void Generation::crossover()
{
	Tour children[3];
	for (int i = 1; i <= POP_SIZE; i=i+2)
	{
		ordercrossover(children,candidates[i],candidates[i+1]);
	//	bestoffour(children,candidates[i],candidates[i+1]);
	}




}
/*
Tour* Generation::simplecrossover(Tour parent1, Tour parent2)
{
	Tour children[3];

	for (int i = 1; i <= POP_SIZE; i++)
	{
		if(i <= (POP_SIZE/2) )
			children[1].order[i]=parent1.order[i];
		else
			children[1].order[i]=parent2.order[i];
		
	}

	for (int i = 1; i <= POP_SIZE; i++)
	{
		if(i <= (POP_SIZE/2) )
			children[2].order[i]=parent2.order[i];
		else
			children[2].order[i]=parent1.order[i];
		
	}

	return children;	

} */
/*
void Generation::bestoffour(Tour* children, Tour parent1 ,Tour parent2)
{
	tour arr[4];
	arr[0]=children[1];j
	arr[1]=children[2];
	arr[2]=parent1;
	arr[3]=parent2	;


}
*/

void Generation::ordercrossover(Tour* children,Tour parent1, Tour parent2)
{
	int part1[50];      //for 100 cities
	int part2[50];

	//Tour children[3];
	int j=0,i;
	for (i = 25; i <= 75 ; i++)
	{
	
			children[1].order[i]=parent1.order[i];
			part1[j] = parent1.order[i]; 
			part2[j] = parent2.order[i];
			j++;		
			children[2].order[i]=parent2.order[i];
			
	}
	i = 1;
	j = 1;
	int k = 1;
	while(i <= 100)
	{
		if(!search(parent2.order[i], part1))
		{
			children[1].order[j] = parent2.order[i];
			if(j==24)
				j = 76;
			else j++;
		}

		if(!search(parent1.order[i],part2))
		{
			children[2].order[k] = parent1.order[i];
			if(k==24)
				k = 76;
			else k++;
		}

		i++;
	}	


}

bool Generation::search(int a, int* arr)
{
	for (int i = 0; i < 50; i++)
	{
		if(a = arr[i])
			return true;
	}

	return false;
}










