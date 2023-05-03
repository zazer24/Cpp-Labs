// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)
//Author: Zach Azer
//Description: Provides statistics such as the sum, mean, minimum and maximum of a set of numbers

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;
            
namespace coen79_lab2
{
    statistician::statistician(){       //initializing values
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }
    void statistician::next(double r){
        if(size==0){
            min = r;                    //case for the first input to work
        }
        total += r;                     //incrementing the sum
        size++;
        if(r < min){
            min = r;                    //replacing the minimum if the new input is smaller
        }
        if(r > max){
            max = r;                    //replacing the maximum if the new input is larger
        }
        avg = total/size;
    }
    int statistician::length() const{
        return size;                    //function to receive the number of statistics
    }
    double statistician::sum() const{
        return total;                   //function to receive the total sum of the statistics
    }
    double statistician::mean() const{
        assert(length() > 0);   
        return avg;                     //function to receive the average of the statistics
    }
    double statistician::maximum() const{
        assert(length() > 0);   
        return max;                     //function to receive the maximum of the statistics
    }
    double statistician::minimum() const{
        assert(length() > 0);
        return min;                     //function to receive the minimum of the statistics
    }       
    void statistician::reset(){
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;                        //resetting all values back to zero
    }
    statistician operator +(const statistician& s1, const statistician& s2){
        statistician s;
        s.total = s1.total + s2.total;      //returns the total of the two inputs
        s.size = s1.size + s2.size;
        s.avg = (s1.avg + s2.avg)/2;
        if(s1.min < s2.min){                //cases to find the minimum between the two inputs
            s.min = s1.min;
        }
        else if(s2.min < s1.min){
            s.min = s2.min;
        }
        if(s1.max > s2.max){                //cases to find the maximum between the two inputs
            s.max = s1.max;
        }
        else if(s2.max > s1.max){
            s.max = s2.max;
        }
        return s;
    }
    statistician operator *(double scale, const statistician& s){
        statistician a;
        a.total = scale * s.total;
        a.size = s.size;
        if(scale < 0){
            a.max = scale * s.min;
            a.min = scale * s.max;
        }else{
        a.min = scale * s.min;              //multiplying the min by a determined scalar
        a.max = scale * s.max;
        }
        a.avg = scale * s.avg;
        return a;
    }
    bool operator ==(const statistician& s1, const statistician& s2){
        statistician s;
        if(s1.length() && s2.length() == 0){            //return true if their length is equal
            return true;
        }
        else if(s1.minimum() == s2.minimum() &&         //return true if they have the same minimum, maximum, length, and sum.
        s1.maximum() == s2.maximum() &&
        s1.length() == s2.length() &&
        s1.sum() == s2.sum()){
            return true;
        }
        else{
            return false;
        }
    }
}
