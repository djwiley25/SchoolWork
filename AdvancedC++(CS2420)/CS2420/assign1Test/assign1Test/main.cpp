#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> wordLadder(string w1, string w2, vector<string> &dict);

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

	/*
	for (int i=0; i<dict.size(); i++){
	cout<<dict[i]<<endl;
	}
	*/
	string w1;
	string w2;
	cout << "Word Ladder program, please enter two words: " << endl;
	cin >> w1;
	cin >> w2;
	vector<string>winningLadder = wordLadder(w1, w2, dict);

	if (winningLadder.empty()) {
		cout << "No word ladder found using words " << w2 << "  and " << w1 << endl;
	}
	else {
		cout << "Ladder from " << w2 << " to " << w1 << ":" << endl;
		for (int i = 0; i < winningLadder.size(); i++) {
			cout << winningLadder[i] << endl;
		}

	}
	return 0;
}

vector<string> wordLadder(string w1, string w2, vector<string> &dict) {
	vector<string> ladder;
	vector<string> usedWords;
	vector<string> emptyLadder;
	int iteration = 0;
	//check paramaters
	if (w1.length() != w2.length()) {
		return emptyLadder;
	}

	ladder.push_back(w1);

	while (!ladder.empty()) {
		iteration += 1;

		string word = ladder.front();
		//if word is the destination word
		if (word == w2) {
			//shortest solution found
			return ladder;
		}
		else {
			//for every character in the word and for every letter in alphabet
			for (int i = 0; i < word.length(); i++) {
				for (int j = 0; j < 26; j++) {
					string tryNext = word;
					tryNext[i] = 'a' + j;
					//if the word is a valid word in the dictionary and hasn't been used before.
					if (tryNext == w2) {
						ladder.push_back(tryNext);
						return ladder;
					}
					bool dictContains = false;
					bool notUsed = false;
					for (int s = 0; s < dict.size(); s++) {
						if (tryNext == dict[s]) {
							dictContains = true;
						}
					}
					for (int t = 0; t < usedWords.size(); t++) {
						if (tryNext == usedWords[t]) {
							notUsed = true;
						}
					}
					if (dictContains && notUsed) {
						vector<string> nextLadder = ladder;
						nextLadder.push_back(tryNext);
						ladder = nextLadder;
						usedWords.push_back(tryNext);
					}
				}
			}
		}

	}
	return emptyLadder;
}
