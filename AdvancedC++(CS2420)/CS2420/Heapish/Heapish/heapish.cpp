#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <ctime>

using namespace std;

void maxHeap(vector<int> &A, int i, int n) {
	int largest;
	int left = 2 * i;
	int right = (2 * i) + 1;

	if ((left <= n) && (A[left - 1] > A[i - 1]))
		largest = left;
	else
		largest = i;

	if ((right < n) && (A[right - 1] > A[largest - 1]))
		largest = right;

	if (largest != i) {
		swap(A[i - 1], A[largest - 1]);
		maxHeap(A, largest, n);
	}
}
void buildHeap(vector<int>& A, int n) {
	for (int i = (n / 2); i >= 1; i--) {
		maxHeap(A, i, n);
	}
}
void heapSort(vector<int>& A, int n) {
	buildHeap(A, n);
	for (int i = n; i >= 1; i--) {
		swap(A[0], A[i]);
		maxHeap(A, 1, i);
	}
}
void deleteMin(vector<int>&v) {
	v.erase(v.begin());
	heapSort(v, int(v.size() - 1));
}
void print(vector<int>&v, ofstream& fout) {
	fout << "Sorted List: " << endl;
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << " ";
	}
	fout << endl;
}

int main() {

	vector<int> list;

	ofstream fout("heapSort.txt");

	clock_t begin = clock();

	list.reserve(1000000);

	for (int i = 0; i < 1000000; ++i) {

		list.push_back(rand() % 1000 + i);

	}
	heapSort(list, int(list.size() - 1));

	clock_t end = clock();

	double time1 = (end - begin) / (CLOCKS_PER_SEC / 1.0);

	fout << "time (sec): " << time1 << endl;
	/*
	// print sorted list
	list.push_back(2);
	heapSort(list, int(list.size() - 1));
	print(list, fopen);

	list.push_back(3);
	heapSort(list, int(list.size() - 1));
	print(list, fopen);

	list.push_back(7);
	heapSort(list, int(list.size() - 1));
	print(list, fopen);

	list.push_back(22);
	heapSort(list, int(list.size() - 1));
	print(list, fopen);

	list.push_back(5);
	heapSort(list, int(list.size() - 1));
	print(list, fopen);

	list.push_back(21);
	heapSort(list, int(list.size() - 1));
	print(list, fopen);

	list.push_back(1);
	heapSort(list, int(list.size() - 1));
	print(list, fopen);

	deleteMin(list);
	print(list, fopen);

	deleteMin(list);
	print(list, fopen);

	*/
	return 0;
}