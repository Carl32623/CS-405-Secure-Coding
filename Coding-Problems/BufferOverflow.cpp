/*
 * @file BufferOverflow.cpp
 *
 * Description
 * This program shows how buffer overflow can happen when user input
 * is beyond a fixed character size. It now securely handles user input 
 * limiting the number of characters that can be read into the buffer.
 *
 * @Author: Carl LaLonde
 *
 * @Date: 03/08/2026
 */

#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

int main() {
	cout << "Buffer Overflow Example" << endl;

	const string account_number = "CharlieBrown42";

	char user_input[20];

  
	cout << "Enter a value: ";

	// Reads user input, limiting input to 20 characters.
	cin.getline(user_input, 20);

	// if the user inputs too many characters, input fails.
	if (cin.fail()) {

		// clear the error so the program can continue running.
		cin.clear();

		// removes any leftover input from ruining any future attempts
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Error: You entered too many characters." << endl;

		// ends program
		return 1;
	}

	cout << "You entered: " << user_input << endl;

	cout << "Account Number = " << account_number << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


