#ifndef FISH_H
#define FISH_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "protofish.h"
#include "dir.h"

class Fish:public ProtoFish {
public:
	//Constructor
	Fish(int gestationCountdown, int gestationPeriod, int startingAge);

	//Gestation Countdown accessor
	int getGCntdwn() { return gCntdwn; }

	//Gestation Period Countdown
	int getGPd() { return gPd; }

	//Baby accessor
	bool haveBaby();

	//Override timeUpdate in protofish
	void timeUpdate();

	//Sets direction fish is heading
	void point(char sonarMap[5][5]);

protected:
	int gCntdwn;
	int gPd;
	bool baby;

};


#endif
