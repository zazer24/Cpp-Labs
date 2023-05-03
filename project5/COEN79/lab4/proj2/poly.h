// FILE: poly.h
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// CLASS PROVIDED:
//   class polynomial (in the namespace coen79_lab4)
//     A polynomial has one variable x, real number coefficients, and
//     non-negative integer exponents. Such a polynomial can be viewed
//     as having the form:
//       A[n]*x^n + A[n-1]*x^(n-1) + ... A[2]*x^2 + A[1]*x + A[0]
//     where the A[n] are the real number coefficients and x^i represents
//     the variable x raised to the i power. The coefficient A[0] is
//     called the "constant" or "zeroth" term of the polynomial.
//
// HELPER MEMBER FUNCTIONS for the polynomial class
//   void update_current_degree()
//     POSTCONDITION: The current degree is set to the highest exponent
//      with a non-zero coeficient.
//
// MEMBER CONSTANTS
//   const static size_t MAXIMUM_DEGREE
//     The size of the maximum exponent permitted for a polynomial.
//
// CONSTRUCTOR for the polynomial class
//   polynomial(double c = 0.0, unsigned int exponent = 0)
//     PRECONDITION: exponent <= MAXIMUM_DEGREE
//     POSTCONDITION: This polynomial has been created with all zero
//     coefficients, except for coefficient c for the specified exponent.
//     When used as a default constructor (using default values for
//     both arguments), the result is a polynomial with all zero
//     coefficients.
//
// MODIFICATION MEMBER FUNCTIONS for the polynomial class
//   void assign_coef(double coefficient, unsigned int exponent)
//     PRECONDITION: exponent <= MAXIMUM_DEGREE.
//     POSTCONDITION: Sets the coefficient for the specified exponent.
//
//   void add_to_coef(double amount, unsigned int exponent)
//     PRECONDITION: exponent <= MAXIMUM_DEGREE.
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.
//
//   void clear( )
//     POSTCONDITION: All coefficients of this polynomial are set to zero.
//
// CONSTANT MEMBER FUNCTIONS for the polynomial class
//   polynomial antiderivative( ) const
//     PRECONDITION: degree( ) < MAXIMUM_DEGREE
//     POSTCONDITION: The return value is the antiderivative (indefinite integral)
//     of this polynomial.
//     NOTE: The return polynomial always has a constant term of zero.
//
//   double coefficient(unsigned int exponent) const
//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
//     NOTE: For exponents > MAXIMUM_DEGREE, the return value is always zero.
//
//   double definite_integral(double x0, double x1) const
//     POSTCONDITION: Returns the value of the definite integral computed from
//     x0 to x1.  The answer is computed analytically.
//
//   unsigned int degree( ) const
//     POSTCONDITION: The function returns the value of the largest exponent
//     with a non-zero coefficient.
//     If all coefficients are zero, then the function returns zero (even
//     though, technically, this polynomial does not have a degree).
//
//   polynomial derivative( ) const
//     POSTCONDITION: The return value is the first derivative of this
//     polynomial.
//
//   double eval(double x) const
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x.
//
//   bool is_zero( ) const
//     POSTCONDITION: The return value is true if and only if the polynomial
//     is the zero polynomial.
//
//   unsigned int next_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is LARGER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is zero.
//
//   unsigned int previous_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is SMALLER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is UINT_MAX
//     from <climits>.
//
// CONSTANT OPERATORS for the polynomial class
//   double operator( ) (double x) const
//     Same as the eval member function.
//
//
// NON-MEMBER BINARY OPERATORS for the polynomial Class
//   polynomial operator +(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the sum of the coefficients of p1 & p2 for any given
//     exponent.
//
//   polynomial operator -(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the difference of the coefficients of p1 & p2 for any given
//     exponent.
//
//   polynomial operator *(const polynomial& p1, const polynomial& p2)
//     PRECONDITION: p1.degree( ) + p2.degree( ) <= MAXIMUM_DEGREE.
//     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//     and the answer is the sum of all these term-by-term products.
//     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
//
//
// NON-MEMBER OUTPUT FUNCTIONS for the polynomial Class
//   ostream& operator << (ostream& out, const polynomial& p)
//     POSTCONDITION: The polynomial has been printed to ostream out, which,
//     in turn, has been returned to the calling function.
//     The format of the polynomial when printed should be as follows:
//              -2.5x^2 - 4x + 5.9
//     1) There should be exactly 1 space between the numbers and the operators.
//     2) The constant coeficient should be printed by itself: 5.3, not 5.3x^0
//     3) The first coeficient chould be followed by a plain x: 4x, not 4x^1
//     4) The highest degree's coeficient should have a sign: -2.5x^2, but the
//          following values should all be separated by appropriate operators
//          and then printed unsigned: -2.5x^2 - 4x...
//     5) If you manipulate any settings of the outstream inside of this,
//          such as the precision, they should be restored to what they were
//          at the start of the function before returning.
//
//
// The value semantics (copy constructor and assignment operator) are valid for
// the polynomial class.
//
//

#ifndef COEN79_POLY_H
#define COEN79_POLY_H

#include <cstdlib>  // Provides size_t
#include <iostream>  // Provides ostream

namespace coen79_lab4
{
    class polynomial
    {

    public:
    	// constructor
        polynomial(double c = 0.0, unsigned int exponent = 0);
        // CONSTANTS
        typedef std::size_t size_type; 
    	static const unsigned int MAXIMUM_DEGREE = 29;

        // member functions
        void update_current_degree(); // helper member function to update private variable degree
        void assign_coef(double coefficient, unsigned int exponent); // sets coefficient of the corresponding exponent
        void add_to_coef(double amount, unsigned int exponent); // adds to the coefficient of hte corresponding exponent
        void clear(); // clears the polynomial object

        // const member functions
        polynomial antiderivative() const; // takes the antiderivative of the polynomial and returns the new polynomial
        double coefficient(unsigned int exponent) const; // returns the coefficient of the corresponding exponent
        double definite_integral(double x0, double x1) const; // takes a definite integral 
        /* (finds the difference of two antiderivatives with corresponding values) */
        unsigned int degree() const; // returns the highest degree of the polynomial
        polynomial derivative() const; // returns a polynomial that is the derivative of the parameter polynomial
        double eval(double x) const; // evaluates the polynomial at at value x
        bool is_zero() const; // checks if it is the zero polynomial
        unsigned int next_term(unsigned int e) const; // finds the term after the exponent parameter
        unsigned int previous_term(unsigned int e) const; // finds the term before the exponent parameter

        // member operators
        double operator() (double x) const;
    private:
        double poly[MAXIMUM_DEGREE + 1];
        int current_degree;
    };

    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2);
    polynomial operator -(const polynomial& p1, const polynomial& p2);
    polynomial operator *(const polynomial& p1, const polynomial& p2);

    
    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p);
}
#endif
