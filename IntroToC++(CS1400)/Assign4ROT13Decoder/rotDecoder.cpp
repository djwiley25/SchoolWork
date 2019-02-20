#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

int main() {
	char c;
	ifstream secretMessage;
	ofstream decodedMessage;
	secretMessage.open("secretMessage.txt");
	decodedMessage.open("decodedMessage.txt");
	

	while (secretMessage.get(c)) {

		if (c >= 'A'&&c <= 'M') {
			c += 13;
		}
		else if (c >= 'N'&&c <= 'Z') {
			c -= 13;
		}
		else if (c >= 'a'&& c<= 'm') {
			c += 13;
		}
		else if (c >= 'n'&&c <= 'z') {
			c -= 13;
		}
		decodedMessage << c;
		cout << c;
	}

	
	secretMessage.close();
	decodedMessage.close();

	return 0;
}