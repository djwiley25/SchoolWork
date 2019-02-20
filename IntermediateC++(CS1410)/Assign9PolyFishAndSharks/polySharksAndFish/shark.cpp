#include "dir.h"
#include "shark.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>


Shark::Shark(int sc, int sp, int gc, int gp, int startingAge) :
	starvationCountdown(sc),
	starvationPeriod(sp),
	Fish(gc, gp, startingAge) {
}

void Shark::eat() {
	starvationCountdown = starvationPeriod;
}

void Shark::timeUpdate() {
	starvationCountdown--;
	if (starvationCountdown <= 0)dead = true;
	Fish::timeUpdate();
}

char Shark::toChar() {
	if (dead)return'X';
	if (dir == up)return 'u';
	if (dir == dn)return 'd';
	if (dir == rt)return 'r';
	if (dir == lt)return 'l';
	cout << "shark: couldn't find a good character. exiting.\n"; exit(1);
}


void Shark::point(char sonarMap[5][5]) {
	char x[5][5];
	Dir nd;
	for (int i = 0; i<5; ++i) {
		for (int j = 0; j<5; ++j) {
			x[i][j] = '.';
			if (sonarMap[i][j] == '^')x[i][j] = 'F';
			if (sonarMap[i][j] == '>')x[i][j] = 'F';
			if (sonarMap[i][j] == 'v')x[i][j] = 'F';
			if (sonarMap[i][j] == '<')x[i][j] = 'F';
		}
	}

	nd = randDir();

	if (x[0][0] == 'F')nd = lt;
	if (x[1][0] == 'F')nd = lt;
	if (x[2][0] == 'F')nd = lt;
	if (x[3][0] == 'F')nd = lt;
	if (x[4][0] == 'F')nd = lt;

	if (x[0][4] == 'F')nd = rt;
	if (x[1][4] == 'F')nd = rt;
	if (x[2][4] == 'F')nd = rt;
	if (x[3][4] == 'F')nd = rt;
	if (x[4][4] == 'F')nd = rt;

	if (x[0][1] == 'F')nd = up;
	if (x[0][2] == 'F')nd = up;
	if (x[0][3] == 'F')nd = up;

	if (x[4][1] == 'F')nd = dn;
	if (x[4][2] == 'F')nd = dn;
	if (x[4][3] == 'F')nd = dn;

	if (x[1][1] == 'F')nd = lt;
	if (x[2][1] == 'F')nd = lt;
	if (x[3][1] == 'F')nd = lt;

	if (x[1][3] == 'F')nd = rt;
	if (x[2][3] == 'F')nd = rt;
	if (x[3][3] == 'F')nd = rt;

	if (x[1][2] == 'F')nd = up;
	if (x[3][2] == 'F')nd = dn;

	dir = nd;
}
