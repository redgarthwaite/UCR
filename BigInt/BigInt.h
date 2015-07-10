#ifndef BIGINT_H
#define BIGINT_H

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
// implements an arbitrary precision integer class
// supports non-negative numbers only
//
// representation:
//
// <DESCRIBE INTERNAL REPRESENTATION HERE>
//
// constructors:
//
// BigInt()            -- default constructor, value of integer is 0
// BigInt(int n)       -- initialize to value of n (C++ int)
//       precondition: n >= 0
//
// BigInt(const string & s) -- initialize to value specified by s
//        e.g.    BigInt big("121212121212123123123123123");
//                (1 is most sig. digit of big; 3 is least sig. digit of big)
//        precondition: s has only digit chars and is not empty
//
// BigInt(const BigInt & b)  -- copy constructor
//
//
// *****  arithmetic operators:
// 
// const BigInt & operator += (const BigInt & b)
//          modifies object by adding a BigInt to it
//          returns a reference to the object that stores the result
//
// BigInt operator + (const BigInt & a, const BigInt & b)
//          adds two BigInts together, returns result
//
// const BigInt & operator *= (const BigInt & b)
//          modifies object by multiplying by BigInt
//          returns a reference to the object that stores the result
//
// BigInt operator * (const BigInt & a, const BigInt & b)
//          multiplies two BigInts together, returns result
//
//  ***** logical operators:
//
// int operator == (const BigInt & a, const BigInt & b)
//          returns 1 if a == b, 0 otherwise
//
// int operator != (const BigInt & a, const BitInt & b)
//          returns 1 if a != b, 0 otherwise
//
// int operator < (const BigInt & a, const BigInt & b)
//          returns 1 if a < b, 0 otherwise
//
// int operator <= (const BigInt & a, const BigInt & b)
//          returns 1 if a <= b, 0 otherwise
//
// int operator > (const BigInt & a, const BigInt & b)
//          returns 1 if a > b, 0 otherwise
//
// int operator >= (const BigInt & a, const BigInt & b)
//          returns 1 if a >= b, 0 otherwise
//
//
//  ***** I/O operators:
//
//  ostream & operator << (ostream & os, const BigInt & b)
//        stream operator to print value
//

class BigInt
{
  public:
    
    BigInt();                  // default constructor, value = 0
    BigInt(int);               // assign an integer value
    BigInt(const string &);    // assign a string 
    BigInt(const BigInt &);    // copy constructor 
    ~BigInt();                 // destructor 

/*     // operators: arithmetic, relational */

     const BigInt & operator += (const BigInt &); 
     const BigInt & operator *= (const BigInt &); 
     BigInt & operator = (const BigInt &); 

     friend ostream & operator <<(ostream &, const BigInt &); 
     friend int operator == (const BigInt &, const BigInt &); 
     friend int operator < (const BigInt &, const BigInt &); 

  private:
    vector<int> digits;
    // add the internal representation here

};

BigInt operator +(const BigInt &, const BigInt &); 
BigInt operator *(const BigInt &, const BigInt &);
int operator != (const BigInt &, const BigInt &);
int operator > (const BigInt &, const BigInt &);
int operator >= (const BigInt &, const BigInt &);
int operator <= (const BigInt &, const BigInt &);

#endif   // BIGINT_H not defined
