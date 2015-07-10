// BigInt.cc
// no negatives allowed

using namespace std;
#include <assert.h>
#include "BigInt.h"

#define MIN(A,B) ( ((A)<(B))? (A) : (B) )
#define MAX(A,B) ( ((A)>(B))? (A) : (B) )

BigInt::BigInt()
{
  digits.push_back(0);
}

BigInt::BigInt(int a)
{
  if(a >= 0)
    {
      digits.push_back(a);
    }
  else
    {
      digits.push_back(0);
    }
}

BigInt::BigInt(const string & a)
{
  if(!a.empty())
    {
      int temp;
      char convert[a.size()+1];
      strcpy(convert,a.c_str());
      for(unsigned int i = 0; i < a.size(); ++i)
	{
	  temp = convert[i];
	  temp = temp - 48;
	  if(temp >= 0 && temp <= 9)
	    {
	      digits.push_back(temp);
	    }
	  
	}
    }
  else
    {
      digits.push_back(0);
    }
}

 BigInt::BigInt(const BigInt & a)
 {
   if(!a.digits.empty())
     {
       for(unsigned int i = 0; i < a.digits.size();++i)
	 {
	   digits.push_back(a.digits[i]);
	 }
     }
   else
     {
       digits.push_back(0);
     }
 }

BigInt::~BigInt()
 {
   while(!digits.empty())
     {
       digits.pop_back();
     }

 }

const BigInt & BigInt::operator +=(const BigInt & a)
{
  int i = this->digits.size() -1;
  int j = a.digits.size()-1;
  int k = MAX(this->digits.size(),a.digits.size()) - 1;
  for(;k >= 0;k--)
    {
      if(j >= 0 && i >= 0)
	{
	  this->digits[k] = this->digits[k] + a.digits[k];
	  if(this->digits[k] >= 10)
	    {
	      this->digits[k] -= 10;
	      if(k <= 0)
		{
		  this->digits.push_back(0);
		  for(unsigned int z =  this->digits.size()-1; z > 0; --z )
		    {
		      if(z != 0)
			{
			  this->digits[z] = this->digits[z-1];
			}
		    }
		  this->digits[0] = 1;
		}
	      else
		{
		  this->digits[i-1] += 1;
		}
      	    }
       	}
      else if(j < 0)
	{
	  return *this;
	}
      else
	{
	  this->digits.push_back(0);
	  for(unsigned int z =  this->digits.size()-1; z > 0; --z )
	    {
	      if(z!=0)
		{
		  this->digits[z] = this->digits[z-1];
		}
	    }
	  this->digits[0] = a.digits[j];
	}
      i--;
      j--;
    }
  return *this;
}

BigInt operator +(const BigInt & a, const BigInt & b) 
 {
   BigInt sum = a;      // implemented in terms of +=
   sum += b;            // can't call until += is implement
   return sum;
}

BigInt& BigInt::operator = (const BigInt& a)
{
  this->digits = a.digits;
  return *this; // need to be changed
}

 ostream & operator <<(ostream &os, const BigInt & b)
 {
   // need to print most significant digit to least significant 
   for(unsigned int i = 0; i < b.digits.size(); ++i)
     {
       os << b.digits[i];
     }
   return os;
 }

const BigInt & BigInt::operator *=(const BigInt & b)
// NOTES on *=: 
//      1. you must *= reimplement for final version
//      2. to call this version *=, need to have implemented other member
//         functions: +=, !=, int->big constr., copy constr, =
{
    BigInt copy(*this);      
    return *this;
}

// BigInt operator *(const BigInt & a, const BigInt & b)
// {
//   BigInt prod = a;      // implemented in terms of *=
//   prod *= b;            // can't call until *= is implemented
//   return prod;
// }

int operator == (const BigInt & a, const BigInt & b)
{
  if(a.digits.size() != b.digits.size())
    {
      return 0;
    }
  else
    {
      for(unsigned int i = 0; i < a.digits.size();++i)
      	{
	  if(!(a.digits[i] == b.digits[i]))
	    {
	      return 0;
	    }
      	}
      return 1;
    }
}

int operator < (const BigInt & a, const BigInt & b) 
{
    if(a.digits.size() < b.digits.size())
    {
      return 1;
    }
    else if (b.digits.size() < a.digits.size())
      {
	return 0;
      }
    else
      {
	for(unsigned int i = 0; i < a.digits.size();++i)
	  {
	    if(b.digits[i] < a.digits[i])
	      {
		return 0;
	      }
	  }
	return 1;
      }
}

int operator != (const BigInt & a, const BigInt & b)
{
  return (!(a==b));
}

int operator > (const BigInt & a, const BigInt & b)
{
  return (!(a<b) && !(a==b));
}

int operator >= (const BigInt & a, const BigInt & b)
{
  return (!(a<b));
}

int operator <= (const BigInt & a, const BigInt & b)
{
  return ((a<b) || (a==b));
}
