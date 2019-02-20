#include<iostream>

using namespace std;

class PiggyBank {
public:
	void defaultConstructor();
	void regularConstructor();
	void destructor();
	void countSavings();
	void depositMoney();
	void smash();

private:
	bool broken;
	double savings;


};