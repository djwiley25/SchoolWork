#include <iostream>
#include "TUStack.h"

using namespace std;

int main() {
	//Negative initial value test
	cout << "Expected: OutOfBounds exception --> ";
	try {
		TUStack<int> s1(-1);

	}
	catch(TUStack<int>::OutOfBounds){
		cout << "Exception: value entered either negative or larger than size" << endl;
	}

	TUStack<int>s2(5);

	//Stack Full Test
	cout << "Expected: StackFullException --> ";
	try {
		s2.push(1);
		s2.push(2);
		s2.push(3);
		s2.push(4);
		s2.push(5);
		s2.push(6);
	}
	catch (TUStack<int>::EmptyException) {
		cout << "Exception: cannot pop, stack is empty" << endl;
	}
	catch (TUStack<int>::FullException) {
		cout << "Exception: cannot push, stack is full" << endl;
	}
	//Stack Empty Test
	cout << "Expected: StackEmptyException --> ";
	try {
		s2.pop();
		s2.pop();
		s2.pop();
		s2.pop();
		s2.pop();
		s2.pop();
	}
	catch (TUStack<int>::EmptyException) {
		cout << "Exception: cannot pop, stack is empty" << endl;
	}
	catch (TUStack<int>::FullException) {
		cout << "Exception: cannot push, stack is full" << endl;
	}
	//return copy of illegal index (out of scope)
	cout << "Expected: OutOfBounds exception --> ";
	try {
		s2[6];
	}
	catch (TUStack<int>::OutOfBounds) {
		cout<<"Exception: value entered is larger than size" << endl;
	}
	//return copy of illegal index (negative)
	cout << "Expected: OutOfBounds exception --> ";
	try {
		s2[-1];
	}
	catch (TUStack<int>::OutOfBounds) {
		cout << "Exception: value entered is negative" << endl;
	}

	//string testing
	cout << endl << "String testing" << endl;

	TUStack<string> s3(char(5));
	//Stack Full Test
	cout << "Expected: StackFullException --> ";
	try {
		s3.push("hey");
		s3.push(" you");
		s3.push(" guys");
		s3.push(" this");
		s3.push(" is");
		s3.push(" illegal");
	}
	catch (TUStack<string>::EmptyException) {
		cout << "Exception: cannot pop, stack is empty" << endl;
	}
	catch (TUStack<string>::FullException) {
		cout << "Exception: cannot push, stack is full" << endl;
	}
	//Stack Empty Test
	cout << "Expected: StackEmptyException --> ";
	try {
		s3.pop();
		s3.pop();
		s3.pop();
		s3.pop();
		s3.pop();
		s3.pop();
	}
	catch (TUStack<string>::EmptyException) {
		cout << "Exception: cannot pop, stack is empty" << endl;
	}
	catch (TUStack<string>::FullException) {
		cout << "Exception: cannot push, stack is full" << endl;
	}
	//return copy of illegal index (out of scope)
	cout << "Expected: OutOfBounds exception --> ";
	try {
		s3[6];
	}
	catch (TUStack<string>::OutOfBounds) {
		cout << "Exception: value entered is larger than size" << endl;
	}
	//return copy of illegal index (negative)
	cout << "Expected: OutOfBounds exception --> ";
	try {
		s3[-1];
	}
	catch (TUStack<string>::OutOfBounds) {
		cout << "Exception: value entered is negative" << endl;
	}
	

	return 0;
}