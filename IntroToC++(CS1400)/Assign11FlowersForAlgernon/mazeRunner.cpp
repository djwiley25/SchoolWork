#include "algernon.h"
#include "mazeRunner.h"
#include <iostream>

using namespace std;

void printThing(Thing t) {
	switch (t) {
	case wall:    cout << "X"; break;
	case space:   cout << " "; break;
	case flower:  cout << "*"; break;
	case start:   cout << "S"; break;
	case cheese:  cout << "C"; break;
	case U:       cout << "^"; break;
	case D:       cout << "v"; break;
	case L:       cout << "<"; break;
	case R:       cout << ">"; break;
	}
}

void printMaze(Thing m[ROWS][COLS]) {
	char line[1024];
	cout << endl;
	for (int i = 0; i<ROWS; ++i) {
		for (int j = 0; j<COLS; ++j) {
			printThing(m[i][j]);
		}
		cout << endl;
	}
	cout << endl;
	cin.getline(line, 1023);
	return;
}

Thing setThing(char c) {
	switch (c) {
	case 'X': return wall;
	case ' ': return space;
	case '*': return flower;
	case 'S': return start;
	case 'C': return cheese;
	case '^': return U;
	case 'v': return D;
	case '<': return L;
	case '>': return R;
	}
	return wall;
}

void setupMaze(Thing a[ROWS][COLS], const char b[ROWS][COLS]) {
	for (int i = 0; i<ROWS; ++i) {
		for (int j = 0; j<COLS; ++j) {
			a[i][j] = setThing(b[i][j]);
		}
	}
	return;
}

int main() {
	Thing maze[ROWS][COLS];
	cout << "=================\n";
	setupMaze(maze, MAZE01);
	printMaze(maze);
	algernon(maze);
	printMaze(maze);
	cout << "=================\n";
	setupMaze(maze, MAZE02);
	printMaze(maze);
	algernon(maze);
	printMaze(maze);
	cout << "=================\n";
	setupMaze(maze, MAZE03);
	printMaze(maze);
	algernon(maze);
	printMaze(maze);
	cout << "=================\n";
	setupMaze(maze, MAZE04);
	printMaze(maze);
	algernon(maze);
	printMaze(maze);
	cout << "=================\n";

	return 0;
}