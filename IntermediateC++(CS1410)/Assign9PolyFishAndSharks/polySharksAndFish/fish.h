#ifndef FISH_H
#define FISH_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "dir.h"
#include "protofish.h"

using namespace std;

//a basic fish that moves, has baby fish, and could starve
class Fish : public ProtoFish {
public:
	//constructor
	Fish(int gc, int gp, int startingAge);

	//returns true if I have a baby, then resets gestationCountdown
	bool haveBaby();

	//what am I?
	char whatAmI() { return 'F'; }

	//Another day passes. Do we have a baby ready? 
	void timeUpdate();

	//given a sonar map of my surroundings, I will change direction
	//toward a blank space. I prefer blank spaces that are next to 
	//other fish
	void point(char sonarMap[5][5]);

protected:
	bool nextToFish(int r, int c, char sonarMap[5][5]);
	int gestationCountdown; //when timer reaches 0, a baby is ready
	int gestationPeriod;    //when i have a baby, reset counter to this
	bool babyReady;		//it's a guppy!
};

#endif