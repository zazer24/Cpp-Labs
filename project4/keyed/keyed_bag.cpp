// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag (see keyed_bag.h for documentation)
//Author: Zach Azer
//Description: Implents a keyed bag which can store a collection of items
#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <cmath>
#include <string>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4
{
    keyed_bag::keyed_bag(){
        used = 0;
        int i;
        for(i=0;i<CAPACITY;i++){
            data[i] = 0;
        }
        for(i=0;i<CAPACITY;i++){
            key[i] = '\0';                  //sets the data array to zero, and the key string array to null
        }
    }
    void keyed_bag::erase(){
        size_type i;
        for(i=0;i<CAPACITY;i++){
            key[i] = '\0';                  //erases all the values of the arrays and resets them
            data[i] = 0;
        }
        used = 0;
    }
    bool keyed_bag::erase(const key_type& key){
        size_type i;
        for(i=0;i<used;i++){
            if(key == this->key[i]){
                used--;                             //erases a single value
                this->key[i] = this->key[used];     //moves the value at index i out of the spot and replaces it with the last value
                this->data[i] = this->data[used];
                return true;
            }
        }
        return false;
    }
    void keyed_bag::insert(const value_type& entry, const key_type& key){
        assert(has_key(key) == false && used < CAPACITY);
        data[used] = entry;             //inserts the entry and key to the current point in each array
        this->key[used] = key;
        used++;
    }
    void keyed_bag::operator +=(const keyed_bag& addend){
        assert(used + addend.used <= CAPACITY);
        assert(hasDuplicateKey(addend) == false);       //checks whether there is a duplicate
        size_type i, j=used;
        for(i=0, j;i<addend.used;i++, j++){
            key[j] = addend.key[i];                     //adds the input to the end of the original array
            data[j] = addend.data[i];
        }
        used = used + addend.used;                      //calculates new amount of terms
    
    }
    bool keyed_bag::has_key(const key_type& key) const{
        size_type i;
        for(i=0;i<used;i++){
            if(key == this->key[i])                     //checks to see if the input and a value in the array are the same
                return true;
        }
        return false;
    }
    keyed_bag::value_type keyed_bag::get(const key_type& key) const{
        assert(has_key(key) == true);
        size_type i;
        for(i=0;i<used;i++){
            if(key == this->key[i]){                    //returns a given key from the array
                return data[i];
            }
        }
    }
    keyed_bag::size_type keyed_bag::size( ) const{
        return used;                                    //returns the number of items in the bag
    }
    keyed_bag::size_type keyed_bag::count(const value_type& target) const{
        size_type count = 0;
        size_type i;
        for(i=0;i<used;i++){
            if(target == data[i]){                      //increments the counter if the target is in the array
                count++;
            }
        }
        return count;
    }
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
        size_type i;
        for(i=0;i<otherBag.used;i++){
            if(has_key(otherBag.key[i]))                //checks the other bag if the key is there and returns true if so
                return true;
        }
        return false;
    }
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
        keyed_bag b;
        assert(b1.size( ) + b2.size( ) <= keyed_bag::CAPACITY);
        assert(b1.hasDuplicateKey(b2) == false);
        b += b1;                                    //adds the components of bag 1 and bag 2 to a new keyed bag
        b += b2;
        return b;
    }
}
