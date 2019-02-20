#include "Node.h"
#include <string>

Node::Node() {
	this->leftChild = NULL;
	this->rightSib = NULL;
	this->parent = NULL;
}
void Node::setData(string word, int numChild) {
	this->word = word;
	this->numChild = numChild;
}
string Node::getWord() {
	return this->word;
}
int Node::getNumChild() {
	return this->numChild;
}
void Node::setLeftChild(Node *left) {
	this->leftChild = left;
}
Node* Node::getLeftChild() {
	return this->leftChild;
}
void Node::setRightSib(Node *right) {
	this->rightSib = right;
}
Node* Node::getRightSib() {
	return this->rightSib;
}
void Node::setParent(Node *p) {
	this->parent = p;
}
Node* Node::getParent() {
	return this->parent;
}
void Node::setSubTree(int sub) {
	this->subTreeN = sub;
}
int Node::getSubTree() {
	return this->subTreeN;
}