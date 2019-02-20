#include "BST.h"
#include <math.h>
#include <algorithm>
#include <fstream>

using namespace std;

template <class T>
void BinSearchTree<T>:: add(T input) {
	if (root == NULL) {
		root = new Node<T>(input);
	}else{
		adder(root, input);
	}
}
template <class T>
int BinSearchTree<T>:: treeHeight() {
	return treeHeightChecker(root);
}
template <class T>
void BinSearchTree<T>:: printHelper(ofstream& writeFile, Node<T> *root, int space) {
	if (root == NULL) {
		return;
	}
	else {
		space += 10;
		//traverse tree to the right
		printHelper(writeFile, root->right, space);
		//print value
		for (int i = 10; i < space; i++) {
			writeFile << " ";
			cout << " ";
		}
		writeFile << root->value << endl;
		cout << root->value << endl;
		//traverse tree to the left
		printHelper(writeFile, root->left, space);
	}
}
template <class T>
void BinSearchTree<T>::adder(Node<T> *root, T input) {
	if (root == NULL) {
		root = new Node<T>(input);
	}
	else {
		if (input < root->value) {
			//check left tree
			if (root->left == NULL) {
				//end of left tree found, create new node
				root->left = new Node<T>(input);
			}
			else {
				//end of left tree not reached, recurse
				adder(root->left, input);
			}
		} //Value is more than right node
		else {
			//check right tree
			if (root->right == NULL) {
				//end of right tree found, create new node
				root->right = new Node<T>(input);
			}
			else {
				//end of right tree not reached, recurse
				adder(root->right, input);
			}
		}
	}
}

template <class T>
int BinSearchTree<T>::treeHeightChecker(Node<T> *root) {
	if (!root) return -1;
	//Count height of left tree, count height of right tree
	//Get the max of either the left or right tree, and add 1 for the root
	return 1 + max(treeHeightChecker(root->left), treeHeightChecker(root->right));
}
template <class T>
void BinSearchTree<T>::printToFile(ofstream& writeFile) {
	//ofstream fopen("test2.txt");
	writeFile << "Tree Height:" << treeHeight() << endl;
	cout<< "Tree Height:" << treeHeight() << endl;
	printHelper(writeFile, this->root, 0);
	//fopen.close();
}