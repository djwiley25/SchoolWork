#include"BigInteger.h"

using namespace std;

int main() {

	//Task 3: Compute the 1000th Fibonacci number
	
	BigInteger nm1(1);
	BigInteger nm2(0);
	BigInteger fibb(1);
	for(int i=0;i<1000;i++){
	fibb=nm1+nm2;
	nm2=nm1;
	nm1=fibb;
	}
	cout << fibb << endl;

	//Task 5: Compute 2^1000, 2^1001, 2^2001 and verify comparison operator tests
	//Comp1 is 2^1000
	BigInteger comp1(2);
	for (int i = 2; i < 1001; i++) {
		comp1 = comp1 * 2;
	}
	//Comp2 is 2^1001
	BigInteger  comp2(2);
	for (int i = 2; i < 1002; i++) {
		comp2 = comp2 * 2;
	}
	//Comp3 is 2^2001
	BigInteger comp3(2);
	for (int i = 2; i < 2002; i++) {
		comp3 = comp3 * 2;
	}
	if (comp1 < comp2) {
		cout << "2^1000 is less than 2^1001" << endl;
	}
	if (comp1*comp2 == comp3) {
		cout << "2^1000 times 2^1001 is equivalent to 2^2001" << endl;
	}
	

	return 0;
}