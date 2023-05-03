/* 
 * pattern.cpp
 * Lab 1
 * James Dameris
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <bits/stdc++.h>
#include "pattern.hpp"

using namespace std;

// prints the pattern given in the assignment
void pattern () {
    string input;

    // asks for the input
    cout <<"Enter 10 digits, no spaces: "<< endl; 
    getline (cin, input);

    // set inverse string to input
    string inverse = input;

    // inbuilt function to reverse strings
    reverse(inverse.begin(), inverse.end());

    // prints inputted string
    cout<< input << endl;

    // pattern starts here. First is left, second is right
    cout<< setw (12) << input; 
    cout<< setw (25) << inverse << endl;

    cout<< setw (13) << input;
    cout<< setw (26) << inverse << endl;

    cout<< setw (14) << input;
    cout<< setw (27) << inverse << endl;

    cout<< setw (15) << input;
    cout<< setw (28) << inverse << endl;
}