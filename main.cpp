/*
 * main.cpp
 *
 *  Created on: 28-Sep-2014
 *      Authors: Kaushik, Pramod
 */

#include<iostream>
#include"genetic.h"
#include<string>
using namespace std;
int nocities;
float **distances;

//main function takes input and calls genetic solver
int main()
{
	
	float coordinates;
	string str, str1;
	cin >> str;
	if(str=="non")
		cin >> str1;

	cin >> nocities;
	distances = new float*[nocities+1];
	for(int i = 0; i <= nocities; ++i) {
    	distances[i] = new float[nocities+1];
	}

	for(int i=1; i<= nocities*2; i++){
		cin >> coordinates;
	}

	for(int i=1; i<= nocities; i++){
		for(int j=1; j<= nocities; j++){
			cin >> distances[i][j];
		}
	}
	cerr << "Input read successfully" << endl;

	Genetic geneticsolver;
	geneticsolver.getsoln();

	return 0;
}


