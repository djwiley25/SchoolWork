#include "BST.cpp"
#include <iostream>
#include<fstream>
#include<string>


using namespace std;

int main() {
	BinSearchTree<int> *bst = new BinSearchTree<int>();

	cout << "created new BST instance successfully" << endl;
	/*
	bst->add(11);
	bst->add(1);
	bst->add(6);
	bst->add(-1);
	bst->add(100);
	bst->add(10);
	bst->printToFile();
	*/
	ifstream file("nums.txt");
	if (!file) {
		cout << "Error opening output file" << endl;
		return -1;
	}
	int a;
	ofstream fopen("test.txt");
	while (file>>a) {
		bst->add(a);
		bst->printToFile(fopen);
	}
	fopen.close();
	return 0;
}