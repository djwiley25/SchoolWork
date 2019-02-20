#include "hashTable.h"
#include <string>

using namespace std;
const int TBL_SIZE = 8;

int hashing::hashFunc(int key) {
	return key % TBL_SIZE;
}
void hashing::insert(int key, string data) {
	int hashValue = hashFunc(key);
	bool collide=false;
	
}
void hashing::find(int key) {
	int hashValue = hashFunc(key);

}