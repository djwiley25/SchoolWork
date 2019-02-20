#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<fstream>

using namespace std;

void printHeader() {
	//top of the menu
	cout <<"		***"<< endl;
	cout << "		You			Devil";
	cout << endl;
	cout << endl;
	return;
}
void PL01() {		//left side space
	cout <<"        ";
	return;
}
void PL02(int myScore, int i) {		//myscore indicator
	if (myScore < i || myScore >= i + 5) {
		cout << "    ";
	}
	else {cout<<myScore<<" > "<<left;
	}
	return;
}

void PL03() {			//left dashes
	cout << "--";
	return;
}
void PL04(int i) {		//score increments user
	cout <<setw(5)<<right << i;
	return;
}
void PL05(int i) {		//score increments devil
	if(i>=0 && i<=70||i>90)cout << setw(25)<< i;
	else cout << setw(11)<<i;
	return;
}
void PL06(int i) {		//right dashes
	cout << " --";
	return;
}
void PL07(bool devilsTurn, int i, int die) {
	if (i == 90) {
		if (devilsTurn) cout <<setw(14)<< " (   )";
		else cout <<setw(14)<<" die ";
	}
	else if (i == 85) {
		cout <<setw(14)<< " --- ";
	}
	else if (i == 80) {
		cout << setw(11) << "|"<<die<<"|";
	}
	else if (i == 75) {
		cout << setw(14) << " --- ";
	}
	return;
}
void PL08(int devilScore, int i) {		//devilScore indicator
	if (devilScore < i || devilScore >= i + 5) {
		cout << "     ";
	}
	else {
		cout << " <";
		cout << devilScore;
		
	}
	return;
}
void printLine(int myScore, int i, int devilScore, bool devilsTurn,int die) {
	
	PL01();
	PL02(myScore, i);
	PL03();
	PL04(i);
	PL07(devilsTurn, i, die);
	PL05(i);
	PL06(i);
	PL08(devilScore, i);
	cout << endl;
}


void printMenu(int myScore, int devilScore, bool devilsTurn,int die) {
	int line;
	line = 100;
	printHeader();
	while (line >= 0) {
		printLine(myScore, line, devilScore, devilsTurn, die);
		line -= 5;
	}
	cout << endl << endl<< "Pass[p], Roll[r], or Forfeit[f]\n";

}
char getResponse();

int main() {
	char response;
	bool endOperation = false;
	bool devilsTurn = false;
	int die=0;
	int myScore = 0;
	int devilScore = 0;
	int turnScore = 0;
	int wins, losses;
	ifstream fin;
	ofstream fout;

	srand(time(NULL));

	wins = 0;
	losses = 0;
	fin.open("devilDiceRecord.txt");
	if (fin) {
		fin >> wins;
		fin >> losses;
		fin.close();
	}

	cout << endl;
	while (!endOperation) {
		printMenu(myScore, devilScore, devilsTurn, die);

		while (devilsTurn) {
			//Devils Turn
			if (myScore >= devilScore&&turnScore<17 || devilScore>myScore&&turnScore < 12 || devilScore>84) {
				//Devil Rolls
				response = 'r';
				if (response == 'r') {
					die = (rand() % 6 + 1);		//Number generator for die
				}if (die > 1) {
					turnScore += die;
				}
				else {
					turnScore = 0;
					devilsTurn = false;
				}
			}
			else {
				//Devil Passes
				cout << "The Devil chooses to pass. ";
				devilScore += turnScore;
				response = 'p';
				turnScore = 0;
				devilsTurn = false;
				if (devilScore >= 100) {
					cout << "You lose your soul!!";
					endOperation = true;
					losses++;
				}
			}
		}
		devilsTurn = false;
		if (!devilsTurn) {
			//User's Turn
			response = getResponse();
			switch (response) {
			case'p':			//User passes
				myScore += turnScore;
				turnScore = 0;
				devilsTurn = true;
				if (myScore >= 100) {
					cout << "You Win!!";
					endOperation = true;
					wins++;
				}
				break;
			case 'r':			//User rolls
				die = (rand() % 6) + 1;		//Number generator for die
				if (die > 1) {
					turnScore += die;
				}
				else {
					turnScore = 0;
					devilsTurn = true;
				}
				break;
			case 'f':			//user forfeit's
				//quit
				losses++;
				endOperation = true;
				break;
			}
		}
	}

	fout.open("devilDiceRecord.txt");
	fout << wins << "\n";
	fout << losses;
	fout.close();

	return 0;
}
char getResponse() {
	char c;
	bool valid = false;

	while (!valid) {
		cout << "Your selection: ";
		cin >> c;
		if (c == 'p' || c == 'r' || c == 'f')valid = true;
		else cout << "Please select an option from the choices listed\n";
	}
	return c;
}