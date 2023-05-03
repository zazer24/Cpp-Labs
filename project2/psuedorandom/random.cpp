/* File: random.cpp 
 * Author: Zach Azer
 * Description: generates psuedorandom numbers based on main function input
*/
#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "random.h"

using namespace std;
            
namespace coen79_lab2
{
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus){
        this->seed = seed;                      //setting the paramater and checking for duplicates
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }
    void rand_gen::set_seed(int newSeed){
        seed = newSeed;                         //setting the seed of the class to the input
    }
    int rand_gen::next(){
        int current = (multiplier * seed + increment) % modulus;    //generating the pseudorandom number
        seed = current;                                             
        return current;
    }
    void rand_gen::print_info(){
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;                 //printing values
        cout << "Modulus: " << modulus << endl;
    }
}
