#ifndef BIG_INTEGER
#define BIG_INTEGER
#include"BigInteger.h"

BigInteger::BigInteger() {
	digits = NULL;      // Default constructor: storing nothing!
	size = 0;
	nDigits = 0;
}

BigInteger::~BigInteger() {
	if (digits != NULL) delete[] digits;
	digits = NULL;
	size = 0;
	nDigits = 0;
}

void BigInteger::init(int size) {
	// Task 1. Allocate memory for digits and fill them as zeros

	digits = new char[size];		//allocate a new digits array with the same size in num
	for (int i = 0;i < size;i++) {
		digits[i] = 0;
	}
}

void BigInteger::copy(const BigInteger &num) {
	size = num.size;            // copy digits array size 
	nDigits = num.nDigits;      // copy number of digits
	digits = new char[size];                 // allocate a new digits array with the same size in num
	memcpy(digits, num.digits, size); // copy digits array
}

BigInteger::BigInteger(const BigInteger &num) { // Copy constructor
	copy(num);
}

BigInteger& BigInteger::operator=(const BigInteger &num) {
	if (this != &num) {             // not assign to the same object
		if (digits != NULL) delete[] digits;  // release current digits array
		copy(num);
	}
	return *this;
}


BigInteger::BigInteger(int val) {
	// Task 2a. Construct a BigInteger from an int value
	int count = 0;
	int temp = val;
	while (temp > 0) {
		count++;
		temp /= 10;
	}
	init(count);
	nDigits = count;
	for (int i = 0; i < nDigits; i++) {
		char n = val % 10;
		val /= 10;
		digits[i] = n;
	}	
	

}


BigInteger::BigInteger(string str) {
	// Task 2b. Construct a BigInteger from a string.

	for (int i = 0, j = sizeof(str) - 1; i < sizeof(str); i++, j--){
		digits[i] = str[j];
	}

}

char BigInteger::getDigit(int pos) const {
	if (pos >= nDigits)
		return 0;
	else
		return digits[pos];
}

void BigInteger::setDigit(int pos, char digit) {
	if (pos >= size) {       // not enough space 
		int newSize = 1;
		while (newSize <= pos) newSize *= 2; // compute newSize as a power of 2 that is bigger than pos

		char* temp = digits;    // store link to current digits

		digits = new char[newSize]; // allocate a new array
		memset(digits, 0, newSize); // and fill zeros         

		if (temp != NULL)           // if there are some current digits
			memcpy(digits, temp, nDigits);        // copy them
		size = newSize;
	}

	digits[pos] = digit;    // put the given digit at position pos

	if (pos >= nDigits)      // update the number of digits!
		nDigits = pos + 1;
}

BigInteger multiply(BigInteger &x, int y, int pos) {
	int nx = x.numberOfDigits();
	BigInteger z;
	int carry = 0;
	for (int i = 0; i < nx; i++) {
		carry += (x.getDigit(i)) * y;
		z.setDigit(pos++, (carry % 10));
		carry /= 10;
	}
	while (carry > 0) {
		z.setDigit(pos++, (carry % 10));
		carry /= 10;
	}
	return z;
}

void BigInteger::print(bool debug) {
	if (digits == NULL)
		cout << '0';
	else
		for (int i = nDigits; --i >= 0;)
			cout << (int)digits[i];
	if (debug)
		printf(" [digits = %x, size = %d, nDigits = %d] ", digits, size, nDigits);
}

ostream& operator<<(ostream& out, BigInteger num) {
	//Task 3. Overload operator << to write a BigInteger object to screen
	for (int i = num.numberOfDigits() - 1; i >= 0; i--) {
		out << (int) num.getDigit(i);
	}

	return out;
}
BigInteger BigInteger::operator+(const BigInteger& rhs) {
	//Task 1: Overload operator + to add two BigInteger objects to screen
	BigInteger temp;
	int carry = 0;
	int sum = 0;
	for (int i = 0;i < rhs.numberOfDigits();i++) {

		sum = getDigit(i) + rhs.getDigit(i)+ carry;
		if (sum >= 10) {
			sum = sum - 10;
			carry = 1;
		}
		else {
			carry = 0;
		}
		temp.setDigit(i, sum);
	}
	return temp;


}
BigInteger BigInteger::operator*(const BigInteger &x) {
	//Task 2: Overload operator * for multiplying two BigInteger objects
	int carry = 0;
	int pos=0;
	BigInteger result(0);
	for (int i = 0; i < x.numberOfDigits(); i++) {
		BigInteger temp = multiply(*this, x.getDigit(i));
		for (int j = 0; j < i; j++) {
			temp = multiply(temp, 10);
		}
		result = result + temp;
	}
	return result;
}

bool BigInteger::operator==(BigInteger &operand) const {
	// Task 4a: Overload operator ==
	if (operand.numberOfDigits() != numberOfDigits()) {
		return false;
	}
	else {

		for (int i = 0; i < operand.numberOfDigits(); i++) {
			
			if (operand.getDigit(i) != getDigit(i))
				return false;
		}
	}
	return true;
}
bool BigInteger::operator!=(BigInteger &operand) {
	//Task 4b: Overload operator !=
	
	return !(*this==operand);

}
bool BigInteger::operator<(BigInteger &operand) {
	//Task 4c: Overload operator <
	for (int i = 0; i < operand.numberOfDigits(); i++) {
		if (operand.getDigit(i) > getDigit(i))
			return false;
	}
}

bool BigInteger::operator>(BigInteger &operand) {
	//Task 4d: Overload operator >
	for (int i = 0; i < operand.numberOfDigits(); i++) {
		if (operand.getDigit(i) < getDigit(i))
			return false;
	}
}


	

#endif