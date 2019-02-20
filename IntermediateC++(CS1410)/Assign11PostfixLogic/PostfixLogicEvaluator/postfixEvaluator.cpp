#include<iostream>
#include<stack>
#include<string>

	using namespace std;

// Function to evaluate Postfix expression and return output
bool EvaluatePostfix(string input)
{
	// Declaring a Stack 
	stack<bool> S;

	for (int i = 0; i < input.length(); i++) {
		//If character is T, push T
		if ((input[i]) == 'T') {
			S.push(true);
		}
		//If character is F, push F
		else if (input[i] == 'F') {
			S.push(false);
		}

		// If character is + operator, pop two elements from stack, perform operation and push the result back. 
		else if ((input[i]) == '+') {
			// Pop two operands. 
			bool operand2 = S.top(); S.pop();
			bool operand1 = S.top(); S.pop();

			bool result = (operand1 || operand2);
			//Push back result of operation on stack. 
			S.push(result);
		}
		// If character is * operator, pop two elements from stack, perform operation and push the result back.
		else if ((input[i]) == '*') {
			// Pop two operands. 
			bool operand2 = S.top(); S.pop();
			bool operand1 = S.top(); S.pop();

			bool result = (operand1&&operand2);
			//Push back result of operation on stack. 
			S.push(result);
		}
		// If character is ! operator, pop the top element, negate it, and push the result back.
		else if ((input[i]) == '!') {
			//Pop the top element
			bool operand = S.top(); S.pop();
			//negate it
			bool result = !operand;
			//push result back
			S.push(result);
		}
	}
	return S.top();
}

int main()
{
	string input;
	cout << "Enter Postfix Expression \n";
	getline(cin, input);
	bool result = EvaluatePostfix(input);
	
	cout << "Output = ";
	if (result == 1) {
		cout << "T" << endl;
	}
	else {
		cout << "F" << endl;
	}

	return 0;
}