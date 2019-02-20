#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "dir.h"
#include "fish.h"
#include "sea.h"

using namespace std;

int main() {
	Sea sea(30, 60);
	char line[1024];

	while (!cin.eof() && line[0] != 'q') {
		sea.print();
		sea.timeUpdate();
		cin.getline(line, 1024);
	}

	return 0;
}