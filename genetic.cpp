/*
 * genetic.cpp
 *
 *  Created on: 28-Sep-2014
 *      Author: Kaushik, Pramod
 */


#include "genetic.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
using namespace std;

extern const int nocities;
extern const float**  distances;

#define GENERATIONS 50000

#define OPTITER 1

int* Genetic::getsoln(){

	gen.initialize();
	gen.soln.setcost();
	//gen.print(); cout << endl;
	for(int i=1; i<=GENERATIONS; i++){
		gen.natseln(15);
		//gen.print();
		gen.crossover();
		
		if(i<POP_SIZE)
			gen.generate_mutate(i);
		else
			gen.generate_mutate(POP_SIZE);
		gen.optimize();
		if(gen.solnflag==CHANGED){
			//cout << "printing solution\t";
			gen.soln.print();
			cout.flush();
			gen.solnflag = UNCHANGED;
		}
	
	}
	

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

		//std::cout << candidates[i].getcost() << " ";
		candidates[i].print();

	}
	
	std::cout << "\n";
}

Tour::Tour()
{
	order = new int[nocities+1];

	for(int i=1; i<=nocities; i++){      
		order[i] = i;
	}
	
}

void Tour::setcost()
{
	int i;
	float sum = 0.0;
	for(i=1;i<nocities;i++)
	{
		sum += distances[order[i]][order[i+1]];
	}
	cost = (float) sum + distances[order[nocities]][order[1]];
}

void Tour::randomise()
{
	for(int i = 1; i <= POP_SIZE; i++)
	{
		std::random_shuffle (&order[1],&order[nocities]+1);
		setcost();
	//	print();
		//cout<<i<<"  \n";
	}
}

void Tour::print()
{
//	cout << cost << "\t\t";
	for(int i = 1; i <= nocities; i++){
		std::cout << order[i] << " ";
	}
	cout << endl;
}

bool Tour::operator<(Tour b){
	if(this->getcost()<b.getcost())
		return true;
	else
		return false;
}

void Tour::optimize(){
	float newcost=0.0 ,oldcost;
	int temp;
//	int itercount = 1;
	bool modified = true;
	while(/*itercount<=OPTITER*/modified==true){
		modified = false;
		for(int i=1;i<nocities-1;i++){
			for(int j= i+2;j<=nocities;j++){
				oldcost = getcost();
						
						if(i==1 && j==nocities){				
						newcost = oldcost
						-( distances[order[1]] [order[2]] + distances [order[nocities]] [order[nocities-1]])
						+( distances[order[1]] [order[nocities-1]] + distances [order[2]] [order[nocities]]);
						}
						
						else if(i==1 && j!=nocities){
						newcost = oldcost
						-( distances[order[i]] [order[i+1]] + distances [order[nocities]] [order[i]]
						+ distances[order[j]] [order[j+1]] + distances [order[j-1]] [order[j]])
						+( distances[order[j]] [order[i+1]] + distances [order[nocities]] [order[j]]
						+ distances[order[i]] [order[j+1]] + distances [order[j-1]] [order[i]]);
						}
						
						else if(j==nocities && i!=1){
						newcost = oldcost
						-( distances[order[i]] [order[i+1]] + distances [order[i-1]] [order[i]]
						+ distances[order[j]] [order[1]] + distances [order[j-1]] [order[j]])
						+( distances[order[j]] [order[i+1]] + distances [order[i-1]] [order[j]]
						+ distances[order[i]] [order[1]] + distances [order[j-1]] [order[i]]);
						}
						
						else{
						newcost = oldcost
						-( distances[order[i]] [order[i+1]] + distances [order[i-1]] [order[i]]
						+ distances[order[j]] [order[j+1]] + distances [order[j-1]] [order[j]])
						+( distances[order[j]] [order[i+1]] + distances [order[i-1]] [order[j]]
						+ distances[order[i]] [order[j+1]] + distances [order[j-1]] [order[i]]);
						}					
						

				if (newcost < oldcost){
					temp = order[i];
					order[i] = order[j];
					order[j] = temp;
					setcost();
					modified = true;
				}
			}
		}
//		itercount++;
	}
}

//Performs simple natural selection by removing few tours and duplicating some tours
void Generation::natseln(int duplicates)
{
	Tour** max = new Tour*[duplicates];
	Tour** min = new Tour*[duplicates];

	setmaxtours(max,duplicates);
	setmintours(min,duplicates);

	for(int i=0; i<duplicates; i++){
		*(max[i])=*(min[i]);
	}

}

void Generation::setmaxtours(Tour** temp,int size){
	int minindex;
	for(int i=0; i<size; i++){
		temp[i] = &candidates[i+1];
	}
	minindex = getminindex(temp,size);

	for(int i=1+size; i<=POP_SIZE; i++){
		if(*temp[minindex]<candidates[i]){
			temp[minindex]=&candidates[i];
			minindex = getminindex(temp,size);
		}
	}
}

int Generation::getminindex(Tour** job,int size){
	int minindex =0;
	for(int i=1; i<size; i++){
		if(*job[i]<*job[minindex])
			minindex = i;
	}
	return minindex;
}

void Generation::crossover()
{



	Tour children[3];
	std::random_shuffle (&candidates[1],&candidates[POP_SIZE]+1);
//	children[1].print();

	for (int i = 1; i < POP_SIZE; i=i+2)
	{
		ordercrossover(&candidates[i],&candidates[i+1],i,i+1);
	
	}


	for (int i = 1; i <= POP_SIZE; i++)
		candidates[i].setcost();


}


void Generation::ordercrossover(Tour* parent1, Tour* parent2,int z,int x)
{

	int genes = nocities/3;
	int* part1 = new int[genes];       
	int* part2 = new int[genes];

	Tour children[3];


	int j=0,i;
	for (i = genes+1; i <= 2*genes ; i++)
	{
	
			children[1].order[i]=parent1->order[i];
			part1[j] = parent1->order[i]; 
			part2[j] = parent2->order[i];
			j++;		
			children[2].order[i]=parent2->order[i];
			
	}

	i = 1;
	j = 1;
	int k = 1;
	
	while(i <= nocities)
	{
		if(!search(parent2->order[i], part1))
		{
			children[1].order[j] = parent2->order[i];
			if(j==genes)
				j = 2*genes+1;
			else j++;
		
		}

		if(!search(parent1->order[i],part2))
		{
			children[2].order[k] = parent1->order[i];
			if(k==genes)
				k = 2*genes+1 ;
			else k++;
		}

		i++;
	}	
	
	
	bestoffour(&children[1],&children[2],*parent1,*parent2);


	candidates[z] = children[1];
	candidates[x] = children[2];
}

bool Generation::search(int a, int* arr)
{
	int genes = nocities/3;	

	for (int i = 0; i < genes; i++)
	{
		if(a == arr[i])
			return true;
	}

	return false;
}

void Generation::setmintours(Tour** temp,int size){
	int maxindex;
	for(int i=0; i<size; i++){
		temp[i] = &candidates[i+1];
	}
	maxindex = getmaxindex(temp,size);

	for(int i=1+size; i<=POP_SIZE; i++){
		if(candidates[i]<*temp[maxindex]){
			temp[maxindex]=&candidates[i];
			maxindex = getmaxindex(temp,size);
		}
	}
}

int Generation::getmaxindex(Tour** job,int size){
	int maxindex =0;
	for(int i=0; i<size; i++){
		if(*job[maxindex]<*job[i])
			maxindex = i;
	}
	return maxindex;
}

void Generation::bestoffour(Tour* child1, Tour* child2,Tour parent1 ,Tour parent2)
{
	Tour temp[2];
	temp[0] = parent1;
	temp[1] = parent2;

	int max;

	if(temp[0] < temp[1])
		max = 1;
	else
		max = 0;

	if (*child1<temp[max]){
		temp[max] = *child1;
		if(temp[0] < temp[1])
			max = 1;
		else
			max = 0;
	}

	if (*child2<temp[max]){
		temp[max] = *child2;
		if(temp[0] < temp[1])
			max = 1;
		else
			max = 0;
	}

	*child1 = temp[0];
	*child2 = temp[1];	
}

void Generation::optimize(){
	for(int i=1;i<=POP_SIZE;i++){
		candidates[i].optimize();
		if(candidates[i]<soln){
			soln = candidates[i];
			solnflag = CHANGED;
		}
	}
}


void Tour::mutate ()
{

	time_t t;
	//srand((unsigned) time(&t));
	int temp;
	int i = 0;
	int j = 0;

	while (j == i)
	{
		i = rand()%nocities+1;
		j = rand()%nocities+1;
	}

	temp = order[i];
	order[i] = order[j];
	order[j] = temp;



	setcost();
}


void Generation::generate_mutate(int num)
{
	int a;
	for (int i = 1; i <= num; ++i)
	{
		//a = rand()%POP_SIZE+1;
		candidates[POP_SIZE-i].mutate();
		
	}
}
