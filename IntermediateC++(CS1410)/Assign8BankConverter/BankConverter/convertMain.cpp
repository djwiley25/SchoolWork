#include <iostream>
#include <fstream>
#include <string>


using namespace std;
struct BNKHeader {
	char signature[4]; // {'B','A','N','K'};
	int numberOfAccounts;
	char reserved[24];
};
struct BNKAccount {
	int number;
	char name[20];
	double balance;
	char reserved[96];
};
struct BNKIndex {
	int accountNumber;
	long filePosition;
};

void displayMenu() {
	cout << "Please choose from the following options " << endl << endl;

	cout << "To display an account enter: "<<endl;
	cout << "# display (account number)" <<endl << endl;

	cout << "To deposit money into an account enter:" << endl;
	cout << "# deposit (account number) (amount to be deposited)" << endl<<endl;

	cout << "To withdraw money enter: " << endl;
	cout << "# withdraw (account number) (amount to be withdrawn)" <<endl<< endl;

	cout << "To create an account enter: " << endl;
	cout << "# create (account number),(First name Last name),(amount to be deposited)" <<endl<< endl;

	cout << "To delete an account enter: " << endl;
	cout << "# delete (account number)" << endl << endl;
	
}
int binarySearch(const BNKIndex*indexes, int size, int value)
{
	int first = 0,                     // First array element
		last = size - 1,               // Last array element
		middle,                        // Midpoint of search
		position = -1;                 // Position of search value
	bool found = false;                // Flag

	while (!found && first <= last)
	{
		middle = (first + last) / 2;    // Calculate midpoint
		if (indexes[middle].accountNumber == value)     // If value is found at mid
		{
			found = true;
			position = middle;
		}
		else if (indexes[middle].accountNumber > value) // If value is in lower half
			last = middle - 1;
		else
			first = middle + 1;          // If value is in upper half
	}
	return position;
}

int main() {
	ifstream fin;
	ofstream fout;

	//Count the Number of Lines in the File
	fin.open("csv.txt");
	int nLines = -1;
	while (!fin.eof()) {
		string line;
		getline(fin, line);
		nLines++;
	}
	fin.close();

	fout.open("binary.txt", ios::out | ios::binary);
	fin.open("csv.txt");

	//Put N into BNK header and write it into file
	BNKHeader head;
	head.numberOfAccounts = nLines;
	head.signature[0] = 'B';
	head.signature[1] = 'A';
	head.signature[2] = 'N';
	head.signature[3] = 'K';
	fout.write((char*)&head,sizeof(BNKHeader));

	//Allocate a dynamic array of N BNK Index records
	// Parse each line into a BNKAccount record, and write it to the BNK file
	BNKIndex*indices = new BNKIndex[nLines];
	BNKAccount account;
	string tempV;
	getline(fin, tempV);
	for (int i = 0; i < nLines; i++) {
		getline(fin, tempV, ',');
		indices[i].accountNumber = stoi(tempV);
		indices[i].filePosition = fout.tellp();
		account.number = indices[i].accountNumber;

		getline(fin, tempV, ',');
		int j;
		for (j = 0; j<tempV.length();j++)
		account.name[j] = tempV[j];
		account.name[j] = '\0';

		getline(fin, tempV);
		account.balance= stod(tempV);

		fout.write((char*)&account.name, sizeof(BNKAccount));
	}

	//Sort the array by account number
	int startScan, minIndex, minValue;
	for (startScan = 0; startScan < (nLines - 1); startScan++)
	{
		minIndex = startScan;
		minValue = indices[startScan].accountNumber;
		for (int index = startScan + 1; index < nLines; index++)
		{
			if (indices[index].accountNumber < minValue)
			{
				minValue = indices[index].accountNumber;
				minIndex = index;
			}
		}
		BNKIndex temp = indices[minIndex];
		indices[minIndex] = indices[startScan];
		indices[startScan] = temp;
	}
	//Write to the BNK file
	fout.write((char*)indices, sizeof(BNKIndex)*nLines);
	
	fout.close();
	fin.close();

	//Next part of assignment

	//Open BNK file and check if it contains BANK

	fin.open("binary.txt", ios::in|ios::binary);
	fin.seekg(0, ios::beg);
	fin.read((char*)&head, sizeof(BNKHeader));

	if (head.signature[0] == 'B'&&head.signature[1] == 'A'&&head.signature[2] == 'N'&&head.signature[3] == 'K') {
		cout << "File contains signature BANK " << endl;
	}
	else {
		cout << "File does NOT contain the signature BANK " << endl;
	}

	//Load the index into memory
	BNKIndex*indexes = new BNKIndex[nLines];
	fin.seekg(sizeof(BNKHeader) + nLines * sizeof(BNKAccount));
	for (int i = 0; i < nLines;i++){	
		fin.read((char*)&indexes[i], sizeof(BNKIndex));
		//cout << indexes[i].accountNumber<<" "<<indexes[i].filePosition << endl;
	}

	//Print a menu for the user
	string command;
	displayMenu();
	
	cin.ignore();
	cin.ignore();
	getline(cin, command, ' ');
	string accountNum;
	string deposit;
	string withdraw;
	string name;
	if (command == "display") {
		getline(cin, accountNum);
		int aNum = stoi(accountNum);
		int pos = binarySearch(indexes, nLines, aNum);

		if (pos == -1) {
			cout << "Value not found" << endl;
		}
		else {
			fin.seekg(indexes[pos].filePosition,ios::beg);
			fin.read((char*)&account, sizeof(BNKAccount));
			cout << account.number << endl;
			cout << account.name << endl;
			cout << account.balance << endl;
		}
	}
	else if (command == "deposit") {
			getline(cin, accountNum, ' ');
			int aNum = stoi(accountNum);
			getline(cin, deposit);
			double dep = stof(deposit);
			//use binary search
			int pos = binarySearch(indexes, nLines, aNum);
			if (pos = -1) {
				cout << "Value not found" << endl;
			}
			else {
				fout.seekp(indexes[pos].filePosition, ios::beg);
				fout.write((char*)&account.balance, sizeof(BNKAccount));
				account.balance += dep;
				cout << "Deposited $" << dep << " into Account: " << aNum << endl;
				cout << account.name << endl;
				cout << account.balance << endl;
			}
		}
		else if (command == "withdraw") {
			getline(fin, accountNum, ' ');
			int aNum = stoi(accountNum);
			getline(fin, withdraw);
			double with = stof(withdraw);
			//use binary search
			int pos = binarySearch(indexes, nLines, aNum);
			if (pos = -1) {
				cout << "Value not found" << endl;
			}
			fout.seekp(indexes[pos].filePosition,ios::beg);
			fout.write((char*)&account.balance, sizeof(BNKAccount));
			account.balance -= with;
			cout << "Withdraw $" << with << " from Account: " << aNum << endl;
			cout << account.name << endl;
			cout << account.balance << endl;
		}
		else if (command == "create") {
			getline(fin, accountNum, ',');
			int aNum = stoi(accountNum);
			getline(fin, name, ',');
			string nameCpy = name;
			getline(fin, deposit);
			double dep = stof(deposit);
			//add to array
			//Re sort the array

		}
		else if (command == "delete") {
			getline(fin, accountNum, ' ');
			int aNum = stoi(accountNum);
			int pos = binarySearch(indexes, nLines, aNum);
			if (pos = -1) {
				cout << "Value not found" << endl;
			}
			//remove from array
			//change array size
		}

		return 0;
}

