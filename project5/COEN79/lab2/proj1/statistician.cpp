// AUTHOR: James Dameris
// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
    // constructor
    statistician::statistician() {
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }

    // adds next number to the sequence and updates all stats
    void statistician::next(double r) { 
        total += r;
        if (size == 0) {
            min = r;
        }
        size++;
        if (r < min) {
            min = r;
        }
        if (r > max) {
            max = r;
        }
        avg = total/size;
    }

    // resets the sequence
    void statistician::reset() {
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }

    // the following's names are their function so there is no comment
    int statistician::length() const{
        return size;
    }

    double statistician::sum() const{
        return total;
    }

    double statistician::mean() const{
        return avg;
    }

    double statistician::minimum() const{
        return min;
    }

    double statistician::maximum() const{
        return max;
    }

    // allows sequence addition
    statistician operator +(const statistician& s1,const statistician& s2) {
        statistician s;
        s.total = s1.total + s2.total;
        s.size = s1.size + s2.size;
        if (s1.min < s2.min) {
            s.min = s1.min;
        }
        else {
            s.min = s2.min;
        }
        if (s1.max > s2.max) {
            s.max = s1.max;
        }
        else {
            s.max = s2.max;
        }
        s.avg = s.total/s.size;
        return s;
    }

    // allows sequence scaling
    statistician operator *(double scale, const statistician& s) {
        statistician s1;
        s1.total = scale * s.total;
        s1.size = s.size;
        if (scale < 0) {
            s1.max = scale * s.min;
            s1.min = scale * s.max;
        }
        else {
            s1.min = scale * s.min;
            s1.max = scale * s.max;
        }
        s1.avg = scale * s.avg;
        return s1;
    }

    // allows sequence equality
    bool operator ==(const statistician& s1,const statistician& s2) {
        if (s1.length() && s2.length() == 0) {
            return true;
        }
        else if (
            (s1.sum() == s2.sum()) &&
            (s1.length() == s2.length()) &&
            (s1.minimum() == s2.minimum()) &&
            (s1.maximum() == s2.maximum())) {
                return true;
            }
        else {
            return false;
        }
    } 


}


