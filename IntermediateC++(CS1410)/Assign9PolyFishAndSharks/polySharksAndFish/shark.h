#ifndef SHARK_H
#define SHARK_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "dir.h"
#include "fish.h"

using namespace std;

//a basic fish that moves, has baby fish, and could starve
class Shark : public Fish {
public:
	//constructor
	Shark(int sc, int sp, int gc, int gp, int startingAge);

	//sharks gotta eat or die
	void eat();

	//override the print character
	char toChar();

	//what am I?
	char whatAmI() { return 'S'; }

	//Another day passes. Do we have a baby ready? 
	void timeUpdate();

	//given a sonar map of my surroundings, I will change direction
	//toward the nearest fish
	void point(char sonarMap[5][5]);

protected:
	int starvationCountdown; //when timer reaches 0, a baby is ready
	int starvationPeriod;    //when i have a baby, reset counter to this
};

#endif
