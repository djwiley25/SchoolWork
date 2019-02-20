#ifndef SHARK_H
#define SHARK_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "protofish.h"
#include "dir.h"

class Shark :public Fish {
public:
	//Constructor
	Shark(int starvationCountdown, int starvationPeriod, int gestationCountdown, int gestationPeriod, int startingAge);

	//Accessor function for Starvation Countdown
	int getSCntDwn() { return sCntDwn; }

	//Accessor function for Starvation Period
	int getSPd() { return sPd; }

	// resets starvation countdown
	void eat();

	// overrides to return u,d,l,r as its character console
	char toChar();

	//overrides timeUpdate and decides if shark has died
	void timeUpdate();

	//overrides point to update direction
	void point(char sonarMap[5][5]);
		

protected:
	int sCntDwn;
	int sPd;
};

#endif