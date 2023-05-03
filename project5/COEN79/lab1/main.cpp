/* 
 * main.cpp
 * Lab 1
 * James Dameris
 */

#include <iostream>
#include <fstream>
#include <string>
#include "count.hpp"
#include "pattern.hpp"
#include "uppercase.hpp"
// this file is to just run all of the programs 
// at once and take file as an argument.
int main(int argc, const char * argv[]) {
    if (argc != 2) {
        return 1;
    }

    count();
    pattern();
    uppercase(argv[1]);
    return 0;
}