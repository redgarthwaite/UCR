#include <iostream>
#include "BigInt.cc"
#include "BigInt.h"
using namespace std;

int main()
{

  string in;
  cout << "Enter in a string of integers:\n";
  cin >> in;
  BigInt b = BigInt(5);
  




  BigInt a = BigInt(in);
  BigInt c = a;
  cout << c << endl << endl << endl;

  cout << "NUMBER CONSTRUCTOR: "  <<  b << endl << endl << endl;


  c = c + a;
  cout << c << endl;

  return 0;
}
