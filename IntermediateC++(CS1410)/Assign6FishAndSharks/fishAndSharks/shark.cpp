#include "dir.h"
#include "protofish.h"
#include "fish.h"
#include "shark.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

//Constructor
Shark::Shark(int starvationCountdown, int starvationPeriod, int gestationCountdown, int gestationPeriod, int startingAge)
	:Fish(gestationCountdown, gestationPeriod, startingAge) {
	sCntDwn = starvationCountdown;
	sPd = starvationPeriod;
	gCntdwn = gestationCountdown;
	gPd = gestationPeriod;
	age = startingAge;
}
void Shark::eat() {
	sCntDwn = sPd;
}
char Shark::toChar() {
	if (dead)return 'X';
	if (dir == up)return 'u';
	if (dir == rt)return 'r';
	if (dir == dn)return 'd';
	if (dir == lt)return 'l';
}
void Shark::timeUpdate() {
	if (sCntDwn != 0) {
		sCntDwn--;
		if (sCntDwn == 0)dead = true;
	}
	Fish::timeUpdate();
}
void Shark::point(char sonarMap[5][5]) {
	if (sonarMap[0][0] != '.' || sonarMap[0][1] != '.' || sonarMap[0][2] != '.' || sonarMap[0][3] != '.' || sonarMap[0][4] != '.') dir = up;
	if (sonarMap[1][0] != '.' || sonarMap[2][0] != '.' || sonarMap[3][0] != '.' ) dir = lt;
	if (sonarMap[1][4] != '.' || sonarMap[2][4] != '.' || sonarMap[3][4] != '.' ) dir = rt;
	if (sonarMap[4][0] != '.' || sonarMap[4][1] != '.' || sonarMap[4][2] != '.' || sonarMap[4][3] != '.' || sonarMap[4][4] != '.') dir = dn;
	if (sonarMap[2][1] != '.')dir = lt;
	if (sonarMap[2][3] != '.')dir = rt;
	if (sonarMap[3][1] != '.' || sonarMap[3][2] != '.' || sonarMap[3][3] != '.')dir = dn;
	if (sonarMap[1][1] != '.' || sonarMap[1][2] != '.' || sonarMap[1][3] != '.')dir = up;
}