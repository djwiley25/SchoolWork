#pragma once
#include <iostream>

using namespace std;

template <class T>
class Node {
public:
	T value;
	Node<T> *left;
	Node<T> *right;

	Node(T value) {
		this->value = value;
		left = NULL;
		right = NULL;
	}
	Node(Node<T> *newNode) {
		this->value = newNode->value;
		this->left = newNode->left;
		this->right = newNode->right;
	}

	Node(T value, Node<T> left, Node<T> right) {
		this->value = value;
		this->left = left;
		this->right = right;
	}
};


template <class T>
class BinSearchTree {
public:
	BinSearchTree() {
		root = NULL;
	}
	void add(T);
	int treeHeight();
	void printHelper(ofstream& writeFile, Node<T> *, int space);
	void printToFile(ofstream& writeFile);
private:
	Node<T> *root;
	void adder(Node<T>*, T);
	int treeHeightChecker(Node<T>*);


};
