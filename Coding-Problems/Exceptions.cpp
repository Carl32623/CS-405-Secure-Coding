/*
*  Name: Exceptions.cpp
*  
*  Description: This file shows how to throw and catch standard and custom
*  exceptions so the program can handle errors correctly instead of crashing.
* 
*  Author: Carl LaLonde
* 
*  Date: 03/28/2026
*/

#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

// Custom exception class using what() function. This allows the creation of specific application error.
class CustomApplicationException : public exception {

public: 

    //returns a message about the error.
    const char* what() const noexcept override {

        return "Custom application exception. A problem has occured.";
    }
};

bool do_even_more_custom_application_logic() {

    cout << "Running Even More Custom Application Logic." << endl;

    // Throws a standard exception
    throw runtime_error("Standard exception: Error occured in application logic");

    return true;
}

void do_custom_application_logic() {
    
    cout << "Running Custom Application Logic." << endl;

    // Added a try block to catch exception from the function below.
    try {

        if (do_even_more_custom_application_logic()) {

            cout << "Even More Custom Application Logic Succeeded." << endl;
        }
    }

    // Added a catch block to handle any standard exeptions
    catch (const exception& ex) {

        // Displays error message using ex.what() function
        cout << "Leaving Custom Application Logic." << endl << ex.what() << endl;
    }

    // Custom exception that will be caught in main()
    throw CustomApplicationException();
    
    cout << "Leaving Custom Application Logic." << endl;
}

float divide(float num, float den) {
    
    // Added a check to prevent division by zero
    if (den == 0.0f) {

        // Throws standard exception if denominator is zero
        throw runtime_error("Error: Cannot diviide by zero.");
    }

    return (num / den);
}

void do_division() { // removed noexcept
    
    // Added try block to catch exceptions from divide() function.
    try {

        float numerator = 10.0f;

        float denominator = 0;

        auto result = divide(numerator, denominator);

        cout << "divide(" << numerator << ", " << denominator << ") = " << result << endl;
    }

    // Added a catch block to handle any runtime_error from divide() function.
    catch (const runtime_error& ex) {

        // Displays the error message using ex.what() function.
        cout << "Caught division exception in do_division()" << ex.what() << endl;
    }
}

int main() {
    cout << "Exceptions Tests!" << endl;

    // Wrapped main logic in a try block so exceptions can be handled correctly instead of causing the program to crash.
    try {
        do_division();

        do_custom_application_logic();
    }
    
    // Catch block for custom exceptions.
    catch (const CustomApplicationException& ex) {
        
        cout << "Caught custom exception in main " << ex.what() << endl;
    }

    // Catch block for standard exceptions.
    catch (const exception& ex) {

        cout << "Caught exception in main " << ex.what() << endl;
    }

    // Catch block for unknown exceptions.
    catch (...) {

        cout << "Caught an unknown exception in main " << endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu