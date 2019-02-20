#include "dir.h"
#include "protofish.h"
#include "fish.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

//Constructor
Fish::Fish(int gestationCountdown, int gestationPeriod, int startingAge):ProtoFish(startingAge) {
	gCntdwn = gestationCountdown;
	gPd = gestationPeriod;
	age = startingAge;
}
bool Fish::haveBaby() {
	if (gCntdwn == 0) {
		gCntdwn = gPd;
		return true;
	}
	else {
		return false;
	}
}
void Fish::timeUpdate() {
	if (gCntdwn !=0) {
		gCntdwn--;
	}
	ProtoFish::timeUpdate();
}
void Fish::point(char sonarMap[5][5]) {
	if (sonarMap[0][0] != '.' || sonarMap[1][0] != '.' || sonarMap[1][1] != '.' || sonarMap[2][0] != '.' || sonarMap[2][1] != '.') dir = lt;
	if (sonarMap[0][2] != '.' || sonarMap[0][3] != '.' || sonarMap[0][4] != '.' || sonarMap[1][2] != '.' || sonarMap[1][3] != '.' || sonarMap[1][4] != '.' || sonarMap[0][1] != '.') dir = up;
	if (sonarMap[2][3] != '.' || sonarMap[2][4] != '.' || sonarMap[3][3] != '.' || sonarMap[3][4] != '.' || sonarMap[4][3] != '.' || sonarMap[4][4] != '.') dir = rt;
	if (sonarMap[3][0] != '.' || sonarMap[3][1] != '.' || sonarMap[3][2] != '.' || sonarMap[4][0] != '.' || sonarMap[4][1] != '.' || sonarMap[4][2] != '.') dir = dn;
}