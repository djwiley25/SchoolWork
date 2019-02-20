#pragma once
#include <iostream>
#include <string>
using namespace std;

class Node {
private:
	string word;		//word stored in node
	int numChild;		//Number of children node has
	int subTreeN;		//Number of nodes in subtree
	Node *leftChild;	//left child
	Node *rightSib;		//right siblings
	Node *parent;
public:
	Node();			// default constructor
	void setData(string word, int numChild);	//assign word to Node and number of children to node
	string getWord();		//returns word
	int getNumChild();		//returns number of children
	void setLeftChild(Node *left);		//sets left child pointer
	Node *getLeftChild();				//returns left child pointer
	void setRightSib(Node *right);		//sets right sibling pointer
	Node* getRightSib();				//returns right sibling pointer
	void setParent(Node *p);
	Node* getParent();
	void setSubTree(int sub);
	int getSubTree();
};