// AUTHOR: James Dameris
// FILE: sequence1.cpp
// CLASS IMPLEMENTED: sequence1 (see sequence1.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "sequence1.h"

using namespace std;

namespace coen79_lab3
{
    // constructor
    sequence::sequence() {
        used = 0;
        index = 0;
        size_type i;
        for (i = 0; i < CAPACITY; i++) {
            arr[i] = 0;
        }
    }
    // returns to the start of the sequence
    void sequence::start() {
        index = 0;
    }
    // moves to the end of the sequence
    void sequence::end() {
        index = used - 1;
    }
    // reduces the sequence by one
    void sequence::last() {
        used--;
        if (index == (used)) {
            index--;
        }
    }
    // iterates forwards by one
    void sequence::advance() {
        assert(is_item() == true);
        index++;
    }
    // iterates backwards by one
    void sequence::retreat() {
        // asserting that index doesn't go below 0
        assert(index != 0); 
        index--;
    }
    // before current index
    void sequence::insert(const value_type& entry) { 
        assert(used < CAPACITY);
        if (used == 0) {
            arr[0] = entry;
        }
        else {
            value_type tmp = arr[index];
            size_type i = used;
            arr[index] = entry;
            for (i; i > index+1; i--) {
                arr[i] = arr[i-1];
            }
            arr[index+1] = tmp;
        }
        used++;
    }
    // after current index
    void sequence::attach(const value_type& entry) { 
        assert(used < CAPACITY);
        if (used == 0) {
            arr[index] = entry;
        }
        else {
            value_type tmp = arr[index+1];
            size_type i = used;
            arr[index+1] = entry;
            index++;
            for (i; i > index+1; i--) {
                arr[i] = arr[i-1];
            }
        }
        used++;
    }
    
    void sequence::remove_current() {
        assert(is_item() == true);
        size_type i = used-1;
        for (i; i > index; i--) {
            arr[i-1] = arr[i]; 
        }
        used--;
    }
    // applies insert function but uses zero index instead of current
    void sequence::insert_front(const value_type& entry) { 
        assert(used < CAPACITY);
        size_type i = used;
        for (i; i > index; i--) {
            arr[i] = arr[i-1]; 
        }
        arr[0] = entry;
    }
    // applies attach function but uses used - 1 index instead of current
    void sequence::attach_back(const value_type& entry) {
        assert(used < CAPACITY);
        arr[used] = entry;
    }

    void sequence::remove_front(const value_type& entry) {
        assert(is_item() == true);
        size_type i = 0;
        used--;
        for (i; i < used; i++) {
            arr[i] = arr[i+1];
        }
    }
    // overloads += operator to enable sequence addition with itself
    void sequence::operator +=(const sequence& rhs) {
        assert(used + rhs.used < CAPACITY);
        size_type i = 0;
        size_type tmp = rhs.used;
        for (i; i < tmp; i++) {
            arr[used] = rhs.arr[i];
            used++;
        }
    }

    sequence::size_type sequence::size() const {
        return used;
    }
    // asserts thats the array index in question is valid
    bool sequence::is_item() const {
        /* checks if the sequence index has 
         been advanced out of the range */
        if (index < used) { 
            return true;
        }
        return false;

    }

    sequence::value_type sequence::current() const {
        return arr[index];
    }
    // overloads [] operator to allow sequence indexing
    sequence::value_type sequence::operator[](int index) const {
        return arr[index];
    }

    double sequence::mean() const {
        sequence::size_type i = 0;
        sequence::value_type mean;
        for (i; i < used; i++) {
            mean += arr[i];
        }
        return mean / used;
        
    }
    double sequence::standardDeviation() const {
        sequence::value_type stdev;
        stdev = sequence::mean();
        sequence::size_type i = 0;
        for (i; i < used; i++) {
            stdev = (arr[i] - stdev) ^ 2;
        }
        stdev = stdev/used;
        return sqrt(stdev);
    }

    sequence operator +(const sequence& lhs, const sequence& rhs) {
        sequence s;
        s += lhs;
        s += rhs;
        return s;
    }

    sequence::value_type summation(const sequence& s) {
        return s.mean() * s.size();
    }


}