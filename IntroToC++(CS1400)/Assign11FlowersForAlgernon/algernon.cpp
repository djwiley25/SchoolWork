#include "algernon.h"
#include <iostream>

using namespace std;

void algernon(Thing maze[ROWS][COLS]) {
	//TODO:  Write this function.  Add other functions as needed.
	for (int i = 1; i < ROWS - 1; ++i) {
		for (int j = 1; j < COLS - 1; ++j) {
				if (maze[i][j] == cheese) {
					if (maze[i][j - 1] == space)maze[i][j - 1] = L;
					if (maze[i][j + 1] == space)maze[i][j + 1] = R;
					if (maze[i - 1][j] == space)maze[i - 1][j] = U;
					if (maze[i + 1][j] == space)maze[i + 1][j] = D;
				}
				if (maze[i][j] == L) {
					if (maze[i][j - 1] == space)maze[i][j - 1] = L;
					if (maze[i][j + 1] == space)maze[i][j + 1] = R;
					if (maze[i - 1][j] == space)maze[i - 1][j] = U;
					if (maze[i + 1][j] == space)maze[i + 1][j] = D;
				}
				if (maze[i][j] == R) {
					if (maze[i][j - 1] == space)maze[i][j - 1] = L;
					if (maze[i][j + 1] == space)maze[i][j + 1] = R;
					if (maze[i - 1][j] == space)maze[i - 1][j] = U;
					if (maze[i + 1][j] == space)maze[i + 1][j] = D;
				}
				if (maze[i][j] == U) {
					if (maze[i][j - 1] == space)maze[i][j - 1] = L;
					if (maze[i][j + 1] == space)maze[i][j + 1] = R;
					if (maze[i - 1][j] == space)maze[i - 1][j] = U;
					if (maze[i + 1][j] == space)maze[i + 1][j] = D;
				}
				if (maze[i][j] == D) {
					if (maze[i][j - 1] == space)maze[i][j - 1] = L;
					if (maze[i][j + 1] == space)maze[i][j + 1] = R;
					if (maze[i - 1][j] == space)maze[i - 1][j] = U;
					if (maze[i + 1][j] == space)maze[i + 1][j] = D;
				}
			}
			
	}
	return;
}
bool checkPath(Thing maze [ROWS][COLS]) {

	//turn up
	if (maze[ROWS][COLS - 1] != space && maze[ROWS + 1][COLS] != space && maze[ROWS][COLS + 1] != space && maze[ROWS - 1][COLS] == space) {
		return true;
	}

	//turn down
	if (maze[ROWS][COLS - 1] != space && maze[ROWS + 1][COLS] == space) {
		return true;
	}

	//turn left
	if (maze[ROWS][COLS - 1] == space) {
		return true;
	}

	//turn right
	if (maze[ROWS][COLS - 1] != space && maze[ROWS + 1][COLS] != space && maze[ROWS][COLS + 1] == space) {
		return true;
	}


}
int findpath(Thing maze[ROWS][COLS]) {

	//turn up
	if (maze[ROWS][COLS - 1] != space && maze[ROWS + 1][COLS] != space && maze[ROWS][COLS + 1] != space && maze[ROWS - 1][COLS] == space) {
		return 1;
	}

	//turn down
	if (maze[ROWS][COLS - 1] != space && maze[ROWS + 1][COLS] == space) {
		return 2;
	}

	//turn left
	if (maze[ROWS][COLS - 1] == space) {
		return 3;
	}

	//turn right
	if (maze[ROWS][COLS - 1] != space && maze[ROWS + 1][COLS] != space && maze[ROWS][COLS + 1] == space) {
		return 4;
	}
	
}