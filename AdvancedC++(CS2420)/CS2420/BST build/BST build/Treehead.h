#pragma once
#include <iostream>
using namespace std;

template <class T>
struct Node {
	T value;
	Node *left;
	Node *right;

	Node(T val) {
		this->value = val;
	}
	Node(T val, Node<T> left, Node <T> right) {
		this->value = val;
		this->left = left;
		this->right = right;
	}
};
template <class T>
Node<T> *root;

template <class T>
class binaryTree {

};

