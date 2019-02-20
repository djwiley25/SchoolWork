//#include "binTree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> trimDict(string w1, vector<string> &dict) {
	vector <string> trimmedDict;
	for (int i = 0; i<dict.size(); i++) {
		if (w1.size() == dict[i].size()) {
			trimmedDict.push_back(dict[i]);
		}
	}
	return trimmedDict;
}

int main() {
	string line;
	vector <string> dict;
	ifstream file("dictionary.txt");
	if (!file) {
		cout << "Error opening output file" << endl;
		return -1;
	}
	while (getline(file, line)) {
		dict.push_back(line);
	}
	file.close();

	string w1;
	cout << "Word Ladder program, please enter one word: " << endl;
	cin >> w1;
	vector <string> newDict = trimDict(w1, dict);
	for (int i = 0; i<10; i++) {
		cout << newDict[i] << endl;
	}

	return 0;
}