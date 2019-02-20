#pragma once
#include <string>
using namespace std;

class hNode {
public:
	int key;
	string data;
	hNode(int key, string value) {
		this->key = key;
		this->data = value;
	}
};

class hashing {
public:
	hashing();
	int hashFunc(int key);
	void insert(int key, string data);
	void find(int key);
	void deleteNode(int key);
	int rehash();
	void print();

private:
	hNode **hashTable;
};