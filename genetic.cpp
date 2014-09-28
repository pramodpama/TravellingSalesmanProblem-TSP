/*
 * genetic.cpp
 *
 *  Created on: 28-Sep-2014
 *      Author: Kaushik, Pramod
 */


#include "genetic.h"
#include <algorithm>
#include <iostream>
 using namespace std;

extern const int nocities;
extern const float**  distances;
#define GENERATIONS 10

/*Genetic::Genetic(int a,float** B)
{
	nocities = a ;
	distances = B ;
}*/

int* Genetic::getsoln(){

	gen.initialize();
//	for(int i=1; i<=GENERATIONS; i++){
		gen.natseln(15);
		gen.crossover();
//	}

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
		std::cout << order[i] << " ";
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

void Generation::crossover()
{



	Tour children[3];
//	children[1].print();
	for (int i = 1; i < POP_SIZE; i=i+2)
	{
		ordercrossover(/*children,*/&candidates[i],&candidates[i+1],i,i+1);
	//	bestoffour(children,candidates[i],candidates[i+1]);
		//candidates[i] = children[1];
	//	cout << "\nin crossover \n";
	  //  candidates[i].print();	
		//candidates[i+1] = children[2];
	}
	for (int i = 1; i <= POP_SIZE; i++)
		candidates[i].setcost();


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


void Generation::ordercrossover(/*Tour* children,*/Tour* parent1, Tour* parent2,int z,int x)
{
	int part1[50];      //for 100 cities
	int part2[50];

	Tour children[3];
	/*cout << "\nParents are \n";
	parent1->setcost(); cout << parent1->getcost() << "\t";// parent1->print();
	cout << endl;
	parent2->setcost(); cout << parent2->getcost() << "\t";// parent2->print();*/

	int j=0,i;
	for (i = 25; i <= 75 ; i++)
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
	while(i <= 100)
	{
		if(!search(parent2->order[i], part1))
		{
			children[1].order[j] = parent2->order[i];
			if(j==24)
				j = 76;
			else j++;
		}

		if(!search(parent1->order[i],part2))
		{
			children[2].order[k] = parent1->order[i];
			if(k==24)
				k = 76;
			else k++;
		}

		i++;
	}	
	
	/*cout << "\nchildren before bestoffour\n";
	children[1].setcost(); cout << children[1].getcost();//children[1].print();
	cout << endl;
	children[2].setcost(); cout << children[2].getcost();//children[2].print();*/
	
	bestoffour(&children[1],&children[2],*parent1,*parent2);
	//parent1 = &children[1];
	//parent2 = &children[2];

	/*cout << "\nchildren after bestoffour\n";
	children[1].setcost(); cout << children[1].getcost();//children[1].print();
	cout << endl;
	children[2].setcost(); cout << children[2].getcost();//children[2].print();
	cout << endl;*/

	candidates[z] = children[1];
	candidates[x] = children[2];
}

bool Generation::search(int a, int* arr)
{
	for (int i = 0; i < 50; i++)
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
