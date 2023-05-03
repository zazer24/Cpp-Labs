// FILE: mystrin_tester.cpp
// This is a small demonstration program showing how the string class is used.
//
//  COEN 79
//  --- James Dameris, COEN, SCU ---
//
//

#include <iostream>     // Provides cout and cin
#include <cstdlib>      // Provides EXIT_SUCCESS
#include "mystring.h"   // Or use the Standard Library <string>

using std::cin;
using std::cout;
using std::endl;
using namespace coen79_lab5;

void compare(const string& s1, const string& s2);

int main() {
    string lessThan("Apple");
    string greaterThan("Yellow");
    string userInput;
    cin >> userInput;
    cout << userInput << endl;
    userInput.insert(lessThan,(userInput.length() / 2));
    cout << userInput << endl;
    compare(lessThan,greaterThan);
    return EXIT_SUCCESS;
}

void compare(const string& s1, const string& s2) {
    if (s1 < s2) {
        cout << s1 << " comes before " << s2 << endl;
    }
    else {
        cout << s2 << "comes before " << s1 << endl;
    }
}