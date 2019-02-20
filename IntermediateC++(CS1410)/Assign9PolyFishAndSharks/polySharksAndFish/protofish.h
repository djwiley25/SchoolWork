#ifndef PROTOFISH_H
#define PROTOFISH_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "dir.h"

using namespace std;

//a basic fish that changes direction and dies at age 100
class ProtoFish {
public:
	//constructor
	ProtoFish(int startingAge);

	//direction accessor
	virtual Dir getDir() { return dir; }

	//age accessor
	virtual Dir getAge() { return dir; }

	//deadness accessor
	virtual bool isDead() { return dead; }

	//protofish don't have babies
	virtual bool haveBaby() { return false; }

	//protofish don't eat
	virtual void eat() {}

	//return a char to say what I am
	virtual char whatAmI() { return 'P'; };

	//Another day passes. 
	virtual void timeUpdate();

	//return a character to represent me
	virtual char toChar();

	//change direction in a random way
	virtual void point(char sonarmap[5][5]);

protected:
	Dir dir;		//where i am heading
	int age;		//how long i have lived
	bool dead;		//sadness
};

#endif
