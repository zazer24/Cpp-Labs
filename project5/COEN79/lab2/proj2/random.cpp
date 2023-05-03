// AUTHOR: James Dameris
// FILE: random.cpp
// CLASS IMPLEMENTED: random (see random.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "random.h"

using namespace std;

namespace coen79_lab2
{
    // constructor
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus) {
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }

    // inserts new seed into the pseudo random generator
    void rand_gen::set_seed(int newSeed) {
        seed = newSeed;
    }

    // returns next pseudo random number and sets that to the new seed
    int rand_gen::next() {
        seed = (multiplier * seed + increment) % modulus;
        return seed;
    }

    // prints out the info
    void rand_gen::print_info() const{
        cout<<"Seed: "<<seed<<"\nMultiplier: "<<multiplier<<"\nIncrement: "<<increment<<"\nModulus: "<<modulus<<endl;
    }
}