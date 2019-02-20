#include "TreeStarter.h"
#include "Node.h"
#include <iostream>
#include <fstream>

using namespace std;

//void Tree::makeEmpty(Node *&r) {
//	if (r != NULL) {
//		makeEmpty(r->getLeftChild());
//		makeEmpty(r->getRightSib());
//		delete r;
//		r = NULL;
//	}
//}

string Tree::printTree(string indent, Node *n) {
	//stringstream??
}
string Tree::printTree(string indent = "") {
	return printTree(indent, root);
}
string Tree::toPreorder(Node *n) {
	//stringstream
}
string Tree::toPreorder() {

}
void Tree::buildFromPrefix(ifstream &inf) {
	root = new Node();
	string w;
	int kidct;
	inf >> w >> kidct;	//read string set to w read int set kidct
	root->setData(w, kidct);
	root->setSubTree = 1;
	root->setSubTree+=1;
	Node* temp;
	for (int i = 0; i < kidct - 1; i++) {
		if (root->getLeftChild == NULL) {
			root->setLeftChild(buildNodeFromPrefix(inf, root));
			temp = root->getLeftChild();
		}
		else {
			temp->setRightSib(buildNodeFromPrefix(inf, root));
			temp = temp->getRightSib();
		}

	}
	inf.close;
}
Node* Tree::buildNodeFromPrefix(ifstream & inf, Node *parent) {
	Node *n = new Node();
	string w;
	int kidct;
	inf >> w >> kidct;		//assign data(word, kidct)
	n->setData(w, kidct);
	n->setParent(parent);
	Node* temp;
	for (int i = 0; i < kidct-1; i++) {
		if (n->getLeftChild == NULL) {
			n->setLeftChild(buildNodeFromPrefix(inf, n));
			temp = n->getLeftChild();
		}
		else {
			temp->setRightSib(buildNodeFromPrefix(inf, n));
			temp = temp->getRightSib();
		}
	}
	return n;
}
Node* Tree::findWord(string word, Node *r) {
	if (r == NULL) {
		return;
	}
	if (r->getWord() == word) {
		return r;
	}
	if (r->getLeftChild() != NULL) {
		findWord(word, r->getLeftChild());
	}
	else if(r->getRightSib()!=NULL) {
		findWord(word, r->getRightSib());
	}
	else if (r->getRightSib == NULL&&r->getLeftChild == NULL) {
		Node *p = r->getParent();
		if (p->getRightSib != NULL) {
			findWord(word, p->getRightSib());
		}
		else return;
	}
}
Node* Tree::findWord(string word) {
	return findWord(word, root);
}

//void Tree::upCase(Node *n) {
//	if (n == NULL) {
//		return;
//	}
//	string str = n->getWord();
//	str = toupper;
//	if (n->getLeftChild() != NULL) {
//		n->setData(str);
//	}
//	else if (n->getRightSib() != NULL) {
//		(str, n->getRightSib());
//	}
//	else if (n->getRightSib == NULL&&n->getLeftChild == NULL) {
//		Node *p = n->getParent();
//		if (p->getRightSib != NULL) {
//			(str,n->getRightSib());
//		}
//		else return;
//	}
//}

void Tree::upCase() {
	upCase(root);
}
Tree Tree::clone() {
	Node *n;
	clone(n, root);
}

Node* clone(Node *n, Node *p) {
	while (p != NULL) {
		n = new Node();
		n->getWord = p->getWord;
		n->getNumChild = p->getNumChild;
		clone(n->getLeftChild(),p->getLeftChild());
		clone(n->getRightSib(), p->getRightSib());
	}
}
int Tree::fringe() {
	return fringe(root);
}
int Tree::fringe(Node *n) {

}
int Tree::nodesInLevel(int level) {
	return nodesInLevel(level, root);
}
int Tree::nodesInLevel(int level, Node *r) {

}
bool Tree::isIsomorphic(Tree &t2) {
	return isIsomorphic(root, t2.root);
}
bool Tree::isIsomorphic(Node *r1, Node *r2) {

}
string Tree::commonAncestor(string s1, string s2) {

}
Node * Tree::commonAncestor(Node* n1, Node *n2) {

}
