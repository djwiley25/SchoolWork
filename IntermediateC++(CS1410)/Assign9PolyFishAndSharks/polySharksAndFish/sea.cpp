#include "dir.h"
#include "shark.h"
#include "fish.h"
#include"sea.h"
#include "protofish.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

Sea::Sea(int rows, int cols) {
	//make a sea matrix
	this->rows = rows;
	this->cols = cols;
	pFish = new ProtoFish**[rows];
	pMoved = new bool*[rows];
	for (int a = 0; a < rows; a++) {
		pFish[a] = new ProtoFish*[cols];
		pMoved[a] = new bool[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (rand() % 100 == 0) {
				pFish[i][j] = new Fish(5, 5, 0);
			}
			else if (rand() % 200 == 0) {
				pFish[i][j] = new Shark(10, 10, 10, 10, 0);
			}
			else {
				pFish[i][j] = new ProtoFish(0);
			}
		}
	}

}
Sea::~Sea() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{
			delete pFish[i][j];
		}
		delete[] pFish[i];
		delete[] pMoved[i];
		}
	delete [] pFish;
	delete[] pMoved;
}
void Sea::print() {
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (pFish[i][j] != NULL) {
				cout << pFish[i][j]->toChar();
			}
			else {
				cout << ".";
			}
		}
		cout << endl;
	}
}
void Sea::timeUpdate() {
	resetMoved();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (pFish[i][j] != NULL) {
				pFish[i][j]->timeUpdate();
				setSonarMap(i,j);
				pFish[i][j]->point(sonarMap);
				updateFish(i, j);
			}
		
		}
	}
}
void Sea::updateFish(int i, int j) {
	if (pFish[i][j] != NULL) {
		if (pFish[i][j]->getDir() == '>'||pFish[i][j]->getDir()=='r') {	
			//Check to the right
			if (pFish[i][j + 1] == NULL) {
				pFish[i][j + 1] = pFish[i][j];
				pMoved[i][j + 1] = true;
				if (pFish[i][j]->haveBaby() == false) {
					pFish[i][j] == NULL;
				}
				else {
					pFish[i][j] = new Fish(5,5,0);
				}
			}
			else if (pFish[i][j]->whatAmI() == 'S') {				//If shark then eat
				dynamic_cast<Shark*>(pFish[i][j])->eat();
				pFish[i][j + 1] = pFish[i][j];
				pMoved[i][j + 1] = true;
				if (pFish[i][j]->haveBaby() == false) {
					pFish[i][j] == NULL;
				}
				else {
					pFish[i][j] = new Shark(10,10,10,10,0);
				}
			}
		}
		if (pFish[i][j]->getDir() == 'v'||pFish[i][j]->getDir()=='d') {		//Check down
			if (pFish[i + 1][j] == NULL) {
				pFish[i + 1][j] = pFish[i][j];
				pMoved[i + 1][j] = true;
				if (pFish[i][j]->haveBaby() == false) {
					pFish[i][j] == NULL;
				}
				else {
					pFish[i][j] = new Fish(5,5,0);
				}
			}
			else if (pFish[i][j]->whatAmI() == 'S') {			//If Shark, then eat
				dynamic_cast<Shark*>(pFish[i][j])->eat();
				pFish[i + 1][j] = pFish[i][j];
				pMoved[i + 1][j] = true;
				if (pFish[i][j]->haveBaby() == false) {
					pFish[i][j] == NULL;
				}
				else {
					pFish[i][j] = new Shark(10,10,10,10,0);
				}
			}
		}
		if (pFish[i][j]->getDir() == '<' || pFish[i][j]->getDir() == 'l') {		//Check left
			if (pFish[i][j - 1] == NULL) {
				pFish[i][j - 1] = pFish[i][j];
				pMoved[i][j - 1] = true;
				if (pFish[i][j]->haveBaby() == false) {
					pFish[i][j] == NULL;
				}
				else {
					pFish[i][j] = new Fish(5,5,0);
				}
			}
			else if (pFish[i][j]->whatAmI() == 'S') {			//If shark, then eat
				dynamic_cast<Shark*>(pFish[i][j])->eat();
				pFish[i][j - 1] = pFish[i][j];
				pMoved[i][j - 1] = true;
				if (pFish[i][j]->haveBaby() == false) {
					pFish[i][j] == NULL;
				}
				else {
					pFish[i][j] = new Shark(10,10,10,10,0);
				}
			}
		}
		if (pFish[i][j]->getDir() == '^' || pFish[i][j]->getDir() == 'u') {		//Check up
			if (pFish[i - 1][j] == NULL) {
				pFish[i - 1][j] = pFish[i][j];
				pMoved[i - 1][j] = true;
				if (pFish[i][j]->haveBaby() == false) {
					pFish[i][j] == NULL;
				}
				else {
					pFish[i][j] = new Fish(5,5,0);
				}
			}
			else if (pFish[i][j]->whatAmI() == 'S') {			//If shark then eat
				dynamic_cast<Shark*>(pFish[i][j])->eat();
				pFish[i - 1][j] = pFish[i][j];
				pMoved[i - 1][j] = true;
				if (pFish[i][j]->haveBaby() == false) {
					pFish[i][j] == NULL;
				}
				else {
					pFish[i][j] = new Shark(10,10,10,10,0);
				}
			}
		}
	}
}
void Sea::setSonarMap(int rPos, int cPos) {
	for (int i = rPos - 2, a=0; i <= rPos + 2; i++,a++) {
		for (int j = cPos - 2, b=0; j <= cPos + 2; j++,b++) {
			if (i >= 0 && j >= 0 && i < rows&&j < cols) {
				if (pFish[i][j] != NULL) {
					if (pFish[i][j]->whatAmI() == 'S') {
						sonarMap[a][b] = pFish[a][b]->toChar();
					}
					else if (pFish[i][j]->whatAmI() == 'F') {
						sonarMap[a][b] = pFish[a][b]->toChar();
					}
				}
				else { continue; }
			}
		}
	}
}
void Sea::resetMoved() {
	//reset pMoved
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			pMoved[i][j]=false;
		}
	}

}