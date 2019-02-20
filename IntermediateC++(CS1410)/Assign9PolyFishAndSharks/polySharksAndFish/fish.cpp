#include "dir.h"
#include "fish.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

//constructor
Fish::Fish(int gc, int gp, int startingAge) :
	gestationCountdown(gc), //countdown timer to grow a baby fish
	gestationPeriod(gp),    //reset value for gestationCountdown
	ProtoFish(startingAge)
{
	babyReady = false;
}

//returns true if I have a baby, then resets gestationCountdown
bool Fish::haveBaby() {
	if (!babyReady)return false;
	babyReady = false;
	gestationCountdown = gestationPeriod;
	return true;
}

//Another day passes. Do we have a baby ready?  Did we starve?
void Fish::timeUpdate() {
	ProtoFish::timeUpdate();
	if (gestationPeriod >= 0 && !babyReady) {
		gestationCountdown--;
		if (gestationCountdown <= 0) {
			babyReady = true;
		}
	}
}


//given a sonar map of my surroundings, I will change direction
//toward a blank space.  I prefer spaces next to other fish
void Fish::point(char sonarMap[5][5]) {
	//pick a random direction to start looking
	Dir nd = randDir();
	int nr, nc;
	for (int i = 0; i<4; ++i) {
		//look in each of four directions
		nr = 2; nc = 2;
		if (nd == up)nr--;
		if (nd == rt)nc++;
		if (nd == dn)nr++;
		if (nd == lt)nc--;
		//if I find a blank space, set my direction towards it
		if (sonarMap[nr][nc] == '.') {
			if (nextToFish(nr, nc, sonarMap)) {
				dir = nd;
				return;
			}
		}
		nd = nextDir(nd);
	}
	for (int i = 0; i<4; ++i) {
		//look in each of four directions
		nr = 2; nc = 2;
		if (nd == up)nr--;
		if (nd == rt)nc++;
		if (nd == dn)nr++;
		if (nd == lt)nc--;
		//if I find a blank space, set my direction towards it
		if (sonarMap[nr][nc] == '.') {
			dir = nd;
			return;
		}
		nd = nextDir(nd);
	}
	//else just pick a random direction
	dir = randDir();
}


bool Fish::nextToFish(int r, int c, char sonarMap[5][5]) {
	int tr, tc;
	tr = r - 1;
	for (int i = 0; i<3; ++i) {
		tc = c - 1;
		for (int j = 0; j<3; ++j) {
			if (tr<0 || tr >= 3 || tc<0 || tc >= 3 || (tr == 2 && tc && 2))continue;
			if (sonarMap[tr][tc] == '^')return true;
			if (sonarMap[tr][tc] == '>')return true;
			if (sonarMap[tr][tc] == 'v')return true;
			if (sonarMap[tr][tc] == '<')return true;
			tc++;
		}
		tr++;
	}
	return false;
}
