// David Wiley
// A01099945
// Section 001

#include<iostream>

using namespace std;

int main() {
	char response;

	cout << "What would a dog do? \n";
	cout << "Is it an object? [Y/N] \n";
	cin >> response;
	if (response == 'y') {
		//not an object
		cout << "Can you eat it? [Y/N] \n";
		cin>> response;
		if (response == 'y') {
			//you can eat it
			cout << "EAT IT!!!! \n";
			cout << "Was it good? [Y/N] \n";
			cin >> response;
			if (response == 'y') {
				cout << "Wag your tail!! \n";
			}
			else {
				cout << "Puke it out right now!!!! \n";
				cout << "Now it looks and smells even better, lets try eating this again. \n";
			}
		}
		else {
			cout << "Is it a tennis ball? [Y/N] \n";
			cin >> response;
			if (response == 'y') {
				cout << "Pick it up!! \n";
				cout << "Return to owner so they can throw it again!! \n";
			}
			else {
				cout << "Bark at it!!! \n";
			}
		}
		
	}
	else {
		//not an object
		cout << "Is it a sound? [Y/N] \n";
		cin >> response;
		if (response == 'y') {
			cout << "Bark at it!!! \n";
		}
		else {
			//not a sound
			cout << "Go back to sleep. \n";
		}
	}
	cout << "You're such a good boy!! \n";

	


	return 0;
}