#ifndef SEA_H
#define SEA_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "protofish.h"

using namespace std;

//make a sea to hold all the fishies
class Sea {
public:
	//constructor
	Sea(int rows, int cols);

	//free up allocated memory
	~Sea();

	//print the sea to the console
	void print();

	//move and update all the fish in the sea
	void timeUpdate();


private:
	//process one fish for one day
	void updateFish(int i, int j);

	//make a sonar map for a specific row and column
	void setSonarMap(int rPos, int cPos);

	//reset the moved array to all false
	void resetMoved();


	char sonarMap[5][5]; // a generic sonar map to give to a creature
	ProtoFish ***pFish; //where all the creatures are stored
	bool **pMoved; //to keep track of which creatures have moved this day
	int rows; //number of rows in the sea
	int cols; //number of columns in the sea
};


#endif
