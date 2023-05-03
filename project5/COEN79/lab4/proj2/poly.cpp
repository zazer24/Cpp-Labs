// AUTHOR: James Dameris
// FILE: poly.cpp
// CLASS IMPLEMENTED: polynomial (see poly.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <cmath>     // Provides pow(base, exponent)
#include <climits>   // Provides UINT_MAX
#include "poly.h"

using namespace std;

namespace coen79_lab4
{
    // constructor
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        size_type i;
        for (i = 0; i <= MAXIMUM_DEGREE; i++) {
            poly[i] = 0;
        }
        current_degree = 0;
    }
    // helper member function to update private variable degree
    void polynomial::update_current_degree() {
        size_type i;
        for (i = 0; i <= MAXIMUM_DEGREE; i++) {
            if (poly[i] != 0) {
                current_degree = i;
            }
        }
    }
    // sets coefficient of the corresponding exponent
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] = coefficient;
        polynomial::update_current_degree();
    }
    // adds to the coefficient of hte corresponding exponent
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] += amount;
        update_current_degree();
    }
    // clears the polynomial object
    void polynomial::clear( ) {
        size_type i;
        for (i = 0; i <= MAXIMUM_DEGREE; i++) {
            poly[i] = 0;
        }
        current_degree = 0;
    }
    // takes the antiderivative of the polynomial and returns the new polynomial
    polynomial polynomial::antiderivative( ) const {
        assert(degree() < MAXIMUM_DEGREE);
        polynomial antiDeriv;
        size_type i;
        antiDeriv.poly[0] = 0;
        for (i = 1; i <= MAXIMUM_DEGREE; i++) {
            antiDeriv.poly[i] = poly[i-1] * (1/i);
        }
        antiDeriv.update_current_degree();
        return antiDeriv;
    }
    // returns the coefficient of the corresponding exponent
    double polynomial::coefficient(unsigned int exponent) const {
        return poly[exponent];
    }
    // takes a definite integral 
    /* (finds the difference of two antiderivatives
     with corresponding values) */
    double polynomial::definite_integral(double x0, double x1) const {
        polynomial p1 = antiderivative();
        double defInt;
        defInt = p1.eval(x1) - p1.eval(x0);
        return defInt;
    }

    unsigned int polynomial::degree( ) const {
        return current_degree;
    }

    polynomial polynomial::derivative( ) const {
        polynomial deriv;
        size_type i;
        for (i = 0; i < current_degree; i++) {
            deriv.poly[i] = poly[i+1] * (i+1);
        }
        deriv.update_current_degree();
        return deriv;
    }

    double polynomial::eval(double x) const {
        size_type i;
        double eval;
        double exp;
        for (i = 0; i <= MAXIMUM_DEGREE; i++) {
            exp = pow(x,i);
            eval += poly[i] * exp;
        }
        return eval;
    }

    bool polynomial::is_zero( ) const {
        if (current_degree == 0 && poly[0] == 0) {
            return true;
        }
        return false;
    }

    unsigned int polynomial::next_term(unsigned int e) const {
        size_type i;
        for (i = e + 1; i <= MAXIMUM_DEGREE; i++) {
            if (poly[i] != 0) {
                return i;
            }
        }
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
        int i;
        for (i = e - 1; i >= 0; i--) {
            if (poly[i] != 0) {
                return i;
            }
        }
        return UINT_MAX;
    }

    double polynomial::operator() (double x) const {
        return eval(x);
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        polynomial p;
        polynomial::size_type i;
        polynomial::size_type end;
        if (p1.degree() > p2.degree()) {
            end = p1.degree();
        }
        else {
            end = p2.degree();
        }
        for (i = 0; i <= end; i++) {
            p.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        p.update_current_degree();
        return p;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial p;
        polynomial::size_type i;
        polynomial::size_type end;
        if (p1.degree() > p2.degree()) {
            end = p1.degree();
        }
        else {
            end = p2.degree();
        }
        for (i = 0; i <= end; i++) {
            p.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        p.update_current_degree();
        return p;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        assert(p1.degree() + p2.degree() <= p1.MAXIMUM_DEGREE);
        polynomial p;
        polynomial::size_type i,j;
        for (i = 0; i <= p1.degree(); i++) {
            for (j = 0; j <= p2.degree(); j++) {
                p.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
            }
        }
        p.update_current_degree();
        return p;
    }

    std::ostream& operator <<(std::ostream& out, const polynomial& p) {
        polynomial::size_type i;
        string sign = "+ ";
        double tmp = 0;
        i = p.degree();
        if (i == 0) {
            out<<p.coefficient(i)<<endl;
            return out;
        }
        else if (i == 1) {
            out<<p.coefficient(i)<<"x"<<" ";
        }
        else {
            out<<p.coefficient(i)<<"x^"<<i<<" ";
        }
        i = p.previous_term(i);
        for (i; i != UINT_MAX; i = p.previous_term(i)) {
            if (p.coefficient(i) < 0) {
                tmp = p.coefficient(i) * -1;
                sign = "- ";
            }
            else {
                tmp = p.coefficient(i);
            }
            if (i !=1) {
                out<<sign<<tmp<<"x^"<<i<<" ";
            }
            else if (i = 1) {
                out<<sign<<tmp<<"x"<<" ";
            }
            else {
                out<<sign<<tmp;
            }
        }
        return out;
    }
}
