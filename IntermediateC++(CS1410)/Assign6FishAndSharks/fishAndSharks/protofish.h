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
	Dir getDir() { return dir; }

	//age accessor
	int getAge() { return age; }

	//deadness accessor
	bool isDead() { return dead; }

	//Another day passes. 
	void timeUpdate();

	//return a character to represent me
	char toChar();

	//change direction in a random way
	void point();

protected:
	Dir dir;		//where i am heading
	int age;		//how long i have lived
	bool dead;		//sadness
};

#endif