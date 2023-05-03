// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag (see keyed_bag.h for documentation)
//Author: Zach Azer
//Description: Maintains a polynomial using an array
#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <cmath>
#include <cstring>
#include <climits>
#include "poly.h"

using namespace std;

namespace coen79_lab4{
    polynomial::polynomial(double c, unsigned int exponent){ //constructor for polynomial
        assert(exponent <= MAXIMUM_DEGREE);
        int i;
        for(i=0;i<MAXIMUM_DEGREE;i++){
            poly[i] = c;                            //initiliazes given coefficient
        }
    }
    void polynomial::update_current_degree(){
        size_t i;
        for(i=0;i<MAXIMUM_DEGREE;i++){
            if(poly[i] != 0){
                current_degree = i;                 //updates the current degree variable
            }
        }
    }
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] = coefficient;               //assigns the inputted coefficient to its respective exponent
        update_current_degree();                    //updates current degree of the exponent
    }
    void polynomial::add_to_coef(double amount, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] += amount;                   //adds an inputted amount to the coefficient
        update_current_degree();
    }
    void polynomial::clear(){
        int i;
        for(i=0;i<MAXIMUM_DEGREE;i++){
            poly[i] = 0;                            //resets all values to zero
        }
    }
    polynomial polynomial::antiderivative() const{
        assert(degree() < MAXIMUM_DEGREE);          //makes sure I have not gone past the maximum degree
        int i;
        polynomial p;
        for(i=1;i<current_degree;i++){              
            p.poly[i] = poly[i-1]/i;                //logic for getting the coefficient of the previous term and dividing it as you would do in an integral
        }
        p.update_current_degree();
        return p;
    }
    double polynomial::coefficient(unsigned int exponent) const{
        if(poly[exponent] > MAXIMUM_DEGREE){        
            return 0;
        }
        return poly[exponent];                      //returns the coefficient of the polynomial at passed in value
    }
    double polynomial::definite_integral(double x0, double x1) const{
        polynomial p1 = antiderivative();           //calls antiderivative for the integral part 
        double definite;
        definite = p1.eval(x1) - p1.eval(x0);       //calls eval to evaluate at the two inputs
        return definite;
    }
    unsigned int polynomial::degree() const{
        return current_degree;
    }
    polynomial polynomial::derivative() const {
        int i;
        polynomial p;
        for(i=0;i<current_degree;i++){
            p.poly[i] = poly[i+1] * (i+1);          //logic for a derivative of the array
        }
        p.update_current_degree();
        return p;
    }
    double polynomial::eval(double x) const{
        size_t i;
        double ans;
        double exponent;
        for (i = 0; i <= MAXIMUM_DEGREE; i++) {
            exponent = pow(x,i);                         //uses pow function to return the power of the exponent
            ans += poly[i] * exponent;                   //calculates the answer
        }
        return ans;
    }
    bool polynomial::is_zero() const{
        if(degree() == 0 && poly[0] == 0){
            return true;                                //returns true since the degree and array value are zero
        }
        return false;
    }
    unsigned int polynomial::next_term(unsigned int e) const{
        int i;
        for(i=e + 1;i<=MAXIMUM_DEGREE;i++){
            if(poly[i] != 0){                           //returns the location of the next term after e
                return i;
            }
        }
        return 0;
    }
    unsigned int polynomial::previous_term(unsigned int e) const{
        int i;
        for(i=e-1;i<MAXIMUM_DEGREE;i--){
            if(poly[i] != 0){                           //returns the location of the previous term of e
                return i;
            }
        }
        return UINT_MAX;
    }
    double polynomial::operator() (double x) const{
        return eval(x);
    }
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        polynomial p;
        int high, i;
        if(p1.degree() > p2.degree()){                  //condition for finding the highest degree
            high = p1.degree();
        }
        else{
            high = p2.degree();
        }
        for(i=0;i<=high;i++){
            p.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);    //assigns the new polynomial to the sum of the two inputted ones
        }
        p.update_current_degree();
        return p;
    }
    polynomial operator -(const polynomial& p1, const polynomial& p2){
        polynomial p;
        int high;
        int i;
        if(p1.degree() > p2.degree()){
            high = p1.degree();
        }
        else{
            high = p2.degree();
        }
        for(i=0;i<=high;i++){
            p.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);    //assigns to the difference of the two inputs
        }
        p.update_current_degree();
        return p;
    }
    polynomial operator *(const polynomial& p1, const polynomial& p2){
        assert(p1.degree() + p2.degree() <= p1.MAXIMUM_DEGREE);
        polynomial p;
        int i, j;
        for(i=0;i<=p1.degree();i++){                    //traverses through the first polynomial
            for(j=0;j<=p2.degree();j++){                //traverses through the second polynomial
                p.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);    //multiplies their coefficients
            }
        }
        p.update_current_degree();
        return p;
    }
    std::ostream& operator <<(std::ostream& out, const polynomial& p) {
        size_t i;
        string posNeg = "+ ";
        double temp= 0;
        i = p.degree();
        if (i==0){                                              //case for a constant
            out<<p.coefficient(i)<<endl;
            return out;
        }
        else if(i==1){
            out<<p.coefficient(i)<<"x"<<" ";                    //does not include the power since it's just x
        }
        else {
            out<<p.coefficient(i)<<"x^"<<i<<" ";                //prints the power of the coefficient
        }
        i = p.previous_term(i);
        for (i;i!=UINT_MAX;i = p.previous_term(i)){
            if (p.coefficient(i) < 0) {
                temp = p.coefficient(i) * -1;                   
                posNeg = "- ";                                  //change to negative number
            }
            if (i!=1){
                out<<posNeg<<p.coefficient(i)<<"x^"<<i<<" ";    //prints out the rest of the information
            }
            else if(i=1){
                out<<posNeg<<p.coefficient(i)<<"x"<<" ";
            }
            else{
                out<<posNeg<<p.coefficient(i);
            }
        }
        return out;
    }
}