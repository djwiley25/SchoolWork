#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void swap(int &a, int &b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}
int bubbleSort(vector<int> &m) {
	int bSwap = 0;
	int bComp = 0;
	// 1. Write a function that performs a bubble sort
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m.size() - 1 - i; ++j) {
			bComp++;
			if (m[j] > m[j + 1]) {
				bSwap++;
				swap(m[j], m[j + 1]);
			}
		}
	}
	return bSwap;
	return bComp;

}
void selectionSort(vector<int> &m) {
	// 2. Write a function that performs a selection sort.
	for (int pos = 0; pos < m.size() - 1; pos++) {
		int currentMinPos = pos;
		for (int i = pos; i < m.size(); ++i) {
			if (m[i] < m[currentMinPos]) {
				currentMinPos = i;
			}
		}
		if (currentMinPos != pos)	//swap check
		{
			int tmp = m[currentMinPos];
			m[currentMinPos] = m[pos];
			m[pos] = tmp;
		}
	}
}
	void printFunction(vector<int> &m) {
		for (int i = 0; i < m.size(); ++i) {
			cout << m[i] << endl;
		}
	}

int main() {
	vector<int> sizeTen(10);
	vector<int> sizeOneH(100);
	vector<int> sizeTwoH(200);
	vector<int> sizeThreeH(300);
	vector<int> sizeFourH(400);
	vector<int> sizeFiveH(500);
	vector<int> sizeSixH(600);
	vector<int> sizeSevenH(700);
	vector<int> sizeEightH(800);
	vector<int> sizeNineH(900);
	vector<int> sizeThou(1000);

	for (int i = 0; i < sizeTen.size(); ++i) {
		sizeTen[i] = rand() % 1000;
	}
	for (int i = 0; i < sizeOneH.size(); ++i) {
		sizeOneH[i] = rand() % 1000;
	}for (int i = 0; i < sizeTwoH.size(); ++i) {
		sizeTwoH[i] = rand() % 1000;
	}for (int i = 0; i < sizeThreeH.size(); ++i) {
		sizeThreeH[i] = rand() % 1000;
	}for (int i = 0; i < sizeFourH.size(); ++i) {
		sizeFourH[i] = rand() % 1000;
	}for (int i = 0; i < sizeFiveH.size(); ++i) {
		sizeFiveH[i] = rand() % 1000;
	}for (int i = 0; i < sizeSixH.size(); ++i) {
		sizeSixH[i] = rand() % 1000;
	}for (int i = 0; i < sizeSevenH.size(); ++i) {
		sizeSevenH[i] = rand() % 1000;
	}for (int i = 0; i < sizeEightH.size(); ++i) {
		sizeEightH[i] = rand() % 1000;
	}for (int i = 0; i < sizeNineH.size(); ++i) {
		sizeNineH[i] = rand() % 1000;
	}for (int i = 0; i < sizeThou.size(); ++i) {
		sizeThou[i] = rand() % 1000;
	}
	printFunction(sizeTen);
	cout << endl;

	// 3. Verify your sort functions are working using a vector of size 10
	cout << "Bubble Sort Verification" << endl << endl;
	bubbleSort(sizeTen);
	printFunction(sizeTen);
	cout << endl;
	
	cout << "Selection Sort Verification" << endl << endl;
	selectionSort(sizeTen);
	printFunction(sizeTen);

	bubbleSort(sizeOneH);
	bubbleSort(sizeTwoH);
	bubbleSort(sizeThreeH);
	bubbleSort(sizeFourH);
	bubbleSort(sizeFiveH);
	bubbleSort(sizeSixH);
	bubbleSort(sizeSevenH);
	bubbleSort(sizeEightH);
	bubbleSort(sizeNineH);
	bubbleSort(sizeThou);

	selectionSort(sizeOneH);
	selectionSort(sizeTwoH);
	selectionSort(sizeThreeH);
	selectionSort(sizeFourH);
	selectionSort(sizeFiveH);
	selectionSort(sizeSixH);
	selectionSort(sizeSevenH);
	selectionSort(sizeEightH);
	selectionSort(sizeNineH);
	selectionSort(sizeThou);

	return 0;
}