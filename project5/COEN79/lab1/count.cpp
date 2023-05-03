/* 
 * count.cpp
 * Lab 1
 * James Dameris
 */

#include <iostream>
#include <string>
#include "count.hpp"

using namespace std;

/* Counts the number of alphanumeric characters and 
 * non-alphanumeric characters from the user inputted string.
 * (spaces not included) */
void count () {
    string input;

    // asks for the input
    cout <<"Enter a word or phrase: "<< endl; 

    // stores inputted string
    getline (cin, input);

    int alNumCount = 0; // count for alphanumeric
    int nonAlNumCount = 0; // count for non-alphanumeric

    /* runs through the entire string counting non-alphanumerics
     * and alphanumerics, excluding spaces */
    for (int i = 0; i < input.length(); i++) {
        if (input[i] != ' ') {
            if (isalnum (input[i])) {
                alNumCount++;
            }
            else {
                nonAlNumCount++;
            }
        }
    }
    cout << input << " has " << alNumCount << " alphanumeric characters and " << nonAlNumCount << " non-alphanumeric characters." <<endl;
}
