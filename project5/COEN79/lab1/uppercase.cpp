/* 
 * uppercase.cpp
 * Lab 1
 * James Dameris
 */
#include <iostream>
#include <fstream>
#include <string>
#include "uppercase.hpp"

using namespace std;

/* removes all non-alphanumerics and then prints 
 * words that are 10 char or longer in Uppercase
 */
void uppercase (const char *filename) {
    // file variable
    ifstream iFile;
    iFile.open(filename);
    
    // exits file if null
    if (!iFile) {
        cout << "Failed to open the file." << endl;
        return;
    }
    
    string buffer;

    // iterates through the file while not end of file
    while (!iFile.eof()) {
        // place string into the buffer
        iFile >> buffer;

        int count; 

        // string to store words over 10 characters long
        string word;

        // loop to form uppercase words without non-alphanumerics
        for (int i = 0; i < buffer.length(); i++) {
            if (isalnum (buffer[i])) {
                word.push_back(toupper(buffer[i]));
                count++;
            }
        }
        // prints word if length is greater or equal to 10
        if (count >= 10) {
            cout << word << endl;
        }

        // reset word and count for next while iteration
        word = "";
        count = 0;
    }
    iFile.close();
}

