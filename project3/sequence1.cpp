// FILE: sequence1.cpp
// CLASS IMPLEMENTED: sequence (see sequence1.h for documentation)
//Author: Zach Azer
//Description: 

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <cmath>
#include "sequence1.h"

using namespace std;
            
namespace coen79_lab3
{
    sequence::sequence(){
        used = 0;
        index = 0;
        int i;
        for(i=0;i<CAPACITY;i++){
            data[i] = 0;
        }
    }
    void sequence::start(){
        index = 0;
    }
    void sequence::end(){
        index = used - 1;
    }
    void sequence::last(){
        used--;
        if(index == used){
            index--;
        }
    }
    void sequence::advance(){
        assert(is_item() == true);
        if(index != CAPACITY){
            index++;
        }
    }
    void sequence::retreat(){
        if(used != 0){
            index--;
        }
    }
    void sequence::insert(const value_type& entry){
        assert(size() < CAPACITY);
        cout << used << endl;
        if(used == 0){
            data[0] = entry;
        }
        else{
            value_type temp = data[index];
            size_type i = used;
            data[index] = entry;
            for(i; i > index; i--){
                data[i] = data[i-1]; 
            }
            data[index + 1] = temp;
        }
        used++;
        cout << used << endl;
    }
    void sequence::attach(const value_type& entry){
        assert(size() < CAPACITY);
         if(used == 0){
            data[0] = entry;
        }
        else{
            value_type temp = data[index];
            size_type i = used;
            for(i; i>index + 1; i++){
                data[i] = data[i+1];
            }
            data[index - 1] = temp;
        }
        used++;
    }
    void sequence::remove_current(){
        assert(is_item() == true);
        size_type i = used - 1;
        for(i; i > index; i--){
            data[i-1] = data[i];
        }
        used--;
    }
    void sequence::insert_front(const value_type& entry){
        assert(used < CAPACITY);
        size_type i = used;
        for(i; i > index; i--){
            data[i] = data[i-1];
        }
        data[0] = entry;
    }
    void sequence::attach_back(const value_type& entry){
        assert(used < CAPACITY);
        data[used] = entry;
    }
    void sequence::remove_front(){
        assert(is_item() == true);
        size_type i = 0;
        used--;
        for(i; i< used; i++){
            data[i+1] = data[i];
        }
    }
    void sequence::operator +=(const sequence& rhs){
        assert(used + rhs.used < CAPACITY);
        size_type i;
        size_type temp = rhs.used;
        for(i=0; i<temp; i++){
            data[used] = rhs.data[i];
            used++;
        }
    }
    sequence::size_type sequence::size() const{
        return used;
    }
    bool sequence::is_item( ) const{
        if(index < used){
            return true;
        }
        return false;
    }
    sequence::value_type sequence::current() const{
        assert(is_item() == true);
        return data[index];
    }
    sequence::value_type sequence::operator[](int index) const{
        assert(index < used);
        index = data[index];
        return index;
    }
    double sequence::mean() const{
        double mean;
        size_type total = 0;
        size_type i;
        size_type avg;
        for(i = 0; i<used + 1;i++){
            total += data[i];
        }
        avg = total/used;
        return avg;
    }
    double sequence::standardDeviation() const{
        size_type total = 0;
        size_type i;
        size_type stdev;
        size_type mean;
        for(i=0;i<used + 1; i++){
            total += data[i];
        }
        mean = total/used;
        for(i=0; i<used + 1; i++){
            stdev += pow(data[i] - mean, 2);
        }
        return sqrt(stdev/used);
    }
    sequence operator +(const sequence& lhs, const sequence& rhs){
        sequence a;
        sequence::size_type i;
        a += lhs;
        a += rhs;
        return a;
     }
     sequence::value_type summation(const sequence &s){
        sequence::size_type i;
        sequence::size_type total;
        for(i=0;i<s.size();i++){
            total += s[i];
        return total;
        }
     }
}
