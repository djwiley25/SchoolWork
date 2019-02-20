#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "dir.h"

using namespace std;

//return a random direction
Dir randDir() {
	int i;
	i = rand() % 4;
	switch (i) {
	case 0:return up;
	case 1:return rt;
	case 2:return dn;
	case 3:return lt;
	default: cout << "dir: picked a bad direction.  exiting.\n"; exit(1);
	}
}

//given a direction, return the next direction in a clockwise fashion
Dir nextDir(Dir currentDir) {
	switch (currentDir) {
	case up:return rt;
	case rt:return dn;
	case dn:return lt;
	case lt:return up;
	}
}