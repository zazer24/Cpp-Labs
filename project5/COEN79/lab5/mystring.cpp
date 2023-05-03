// AUTHORS: Zach Azer, James Dameris
// FILE: mystring.cpp
// CLASS IMPLEMENTED: mystring (see mystring.h for documentation)
#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <cstring>
#include "mystring.h"

using namespace std;

namespace coen79_lab5
{
/*Function: constructor
  Description: initializes the string class for an inputted char array and inputs the sequence of chars in str
*/
    string::string(const char str[]){
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, str, current_length);
    }
/*Function: constructors
  Description: initializes the string class for an inputted character
*/
    string::string(char c){
        current_length = 1;
        allocated = current_length + 1;
        characters = new char[allocated];
        characters[0] = c;
    }
/*Function: constructor
  Description: initializes the string class for an inputted string and copies the string
*/
    string::string(const string& source){
        current_length = source.current_length;
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, source.characters, current_length);
    }
/*Function: ~string
  Description: deletes the string
*/
    string::~string(){
        delete [] characters;
    }
/*Function: +=
  Description: catenates an inputted string (addend) to the end of the string
*/
    void string::operator +=(const string& addend) {
        current_length = current_length + addend.current_length;
        reserve(current_length + 1);
        strncat(characters, addend.characters, addend.current_length);
    }
/*Function: +=
  Description: catenates an inputted string (addend) to the end of the string
*/
    void string::operator +=(const char addend[ ]) {
        current_length = current_length + strlen(addend);
        reserve(current_length + 1);
        strncat(characters, addend, current_length);
        characters[current_length] = '\0';
    }
/*Function: +=
  Description: catenates a character to the end of the string
*/
    void string::operator +=(char addend) {
        reserve(current_length + 2);
        characters[current_length] = addend;
        characters[current_length+1] = '\0';
        current_length++;
    }
/*Function: reserve
  Big O Runtime: O(n)
  Description: creates space for an amount n of characters in the string
*/
    void string::reserve(size_t n) {
        if (n == allocated) {
            return;
        }
        if (allocated > n) {
            n = allocated;
        }
        char *tmp = new char[n];
        copy(characters, characters + current_length, tmp);
        delete [] characters;
        characters = tmp;
        allocated = n+1;
    }
/*Function: =
  Description: overloads the assignment operator
*/
    string& string::operator =(const string& source) {
        if (this == &source) {
            return *this;
        }
        current_length = source.current_length;
        reserve(current_length + 1);
        copy(source.characters,source.characters + source.current_length, characters);
        return *this;
    }
/*Function: Insert
  Big O Runtime: O(n)
  Description: Inserts a source string to the string before a certain index
*/
    void string::insert(const string& source, unsigned int position) {
        assert(position <= current_length);
        reserve(current_length + source.current_length + 10);
        string s1,s2;
        size_t end = position - 1;
        strncpy(s1.characters, characters, position);
        strncpy(s2.characters, characters + position, current_length - position);
        *this += s1;
        *this += source;
        *this += s2;
    }
/*Function: dlt
  Big O Runtime: O(n)
  Description: Deletes a number of characters from a certain position
*/
    void string::dlt(unsigned int position, unsigned int num) {
        assert(position + num <= current_length);
        size_t i,j;
        j = num + position;
        for (i = position; i <= position + num; i++, j++) {
            if (j > current_length) {
                break;
            }
            characters[i] = characters[j];
        }
        current_length = current_length - num;
    }
/*Function: Replace
  Description: Replaces a single character at a given location
*/
    void string::replace(char c, unsigned int position) {
        assert(position <= current_length);
        characters[position] = c;
    }
/*Function: Replace
  Description: Replaces part of the string with the inputted source string
*/
    void string::replace(const string& source, unsigned int position) {
        assert(position + source.current_length <= current_length);
        copy(source.characters, source.characters + source.current_length, characters + position);
    }
/*Function: []
  Description: Overloads the [] operator 
*/
    char string::operator [](size_t position) const {
        return characters[position];
    }
/*Function: Search
  Big O Runtime:O(n)
  Description: returns the location of a character if it is found, returns -1 if not found through entire traversal
*/
    int string::search(char c) const {
        size_t i;
        for (i=0;i<allocated;i++){
            if(characters[i] == c){
                return i;
            }
        }
        return -1;
    }
/*Function: Search
  Big O Runtime: O(n^2)
  Description: Traverses through the string and returns the index of the first instance of the inputted substring, or -1 if it is not found
*/
    int string::search(const string& substring) const {
        size_t i = 0, j = 0;
        for (i = 0; i < current_length - substring.current_length; i++) {
            for  (j = 0; j < substring.current_length; j++) {
                if (characters[i+j] != substring.characters[j]) {
                    break;
                }
            }
            if (j == current_length) {
                    return i;
            }
        }
        return -1;
    }
/*Function: Count
  Big O Runtime: O(n)
  Description: Counts the number of occurences of a character in the string
*/
    unsigned int string::count(char c) const {
        size_t i = 0, count = 0;
        while (i < current_length) {
            if (characters[i] == c) {
                count++;
            }
            i++;
        }
        return count;
    }
/*Function: ostream <<
  Description:  writes the sequence of characters in source to outs and returns outs.
*/
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        size_t i = 0;
        while (i < source.current_length) {
            outs << source.characters[i];
            i++;
        }
        return outs;
    }
/*Functions: Operators
  Description: Implements the six comparison operators for the string class
*/
    bool operator ==(const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) == 0) {
            return true;
        }
        return false;
    }

    bool operator !=(const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) != 0) {
            return true;
        }
        return false;
    }

    bool operator > (const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) > 0) {
            return true;
        }
        return false;
    }

    bool operator < (const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) < 0) {
            return true;
        }
        return false;
    }

    bool operator >=(const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) >= 0) {
            return true;
        }
        return false;
    }

    bool operator <=(const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) <= 0) {
            return true;
        }
        return false;
    }
/*Function: +
  Description: returns the catenation of two strings
*/
    string operator +(const string& s1, const string& s2) {
        string s;
        size_t total = s1.length() + s2.length() + 1;
        s.reserve(total);
        s += s1;
        s += s2;
        return s;
    }
/*Function: +
  Description: returns the catenation of a string and the addend
*/
    string operator +(const string& s1, const char addend[ ]) {
        string s;
        size_t total = s1.length() + strlen(addend) + 1;
        s.reserve(total);
        s += s1;
        s += addend;
        return s;
    }
/*Function: istream >>
  Description: reads the string inputted and returns ins. Skips any white space in the process.
*/
    std::istream& operator >> (std::istream& ins, string& target) { // this function needs to be written still
        while (ins && isspace(ins.peek())) {
            ins.ignore();
        }
        char tmp;
        while (!ins.eof() && !isspace(ins.peek())) {
            ins >> tmp;
            target += tmp;
        }
        cout << target << endl;
        return ins;
    }


}
