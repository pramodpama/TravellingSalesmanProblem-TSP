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
	gen.natseln(20);
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

bool Tour::operator<(Tour b){
	if(this->getcost()<b.getcost())
		return true;
	else
		return false;
}

//Performs simple natural selection by removing few tours and duplicating some tours
void Generation::natseln(int duplicates)
{
	Tour** max = new Tour*[duplicates];
	Tour** min = new Tour*[duplicates];

	setmaxtours(max,duplicates);
	setmintours(min,duplicates);

	/*std::cerr << "Max tours are ";
	for(int i=0; i<duplicates; i++){
		std::cerr << " " << max[i]->getcost();
	}
	std::cerr << std::endl;

	std::cerr << "Min tours are ";
	for(int i=0; i<duplicates; i++){
		std::cerr << " " << min[i]->getcost();
	}
	std::cerr << std::endl;*/


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
