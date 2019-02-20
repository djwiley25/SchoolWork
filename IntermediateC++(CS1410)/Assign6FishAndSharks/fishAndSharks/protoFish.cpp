#include "dir.h"
#include "protofish.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;


//constructor
ProtoFish::ProtoFish(int startingAge) :
	age(startingAge) {
	dir = randDir();
	dead = false;
}

//Another day passes. 
void ProtoFish::timeUpdate() {
	if (age<100) {
		age++;
	}
	else {
		dead = true;
	}
}

//return a character to represent me
char ProtoFish::toChar() {
	if (dead)return 'X';
	if (dir == up)return '^';
	if (dir == rt)return '>';
	if (dir == dn)return 'v';
	if (dir == lt)return '<';
	exit(1);
}


//i will change direction in a random way
void ProtoFish::point() {
	//just pick a random direction
	dir = randDir();
}