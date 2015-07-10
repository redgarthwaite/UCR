// Factorial using BigInts

using namespace std;
#include "BigInt.h"
#include <iostream>
#include <stdlib.h>        // for atoi

// illustrates use of BigInt class
    
BigInt Fact(int);

int main(int argc, char * argv[])
{
    int k;
    int limit;
    BigInt val;

    if (argc > 1){              // command line args?
        limit = atoi(argv[1]);
    }
    else{
        cout << "enter limit ";
        cin >> limit;
    }

    cout << "number \t factorial" << endl;
    cout << "------ \t ---------" << endl << endl;
    for(k = limit; k >= 1; k--)
    {
        val = Fact(k);
        cout << k << "\t" << val << "\t" << endl;
    }
    
    return 0;
}

BigInt Fact(int n)
// Assumes n >= 0
// returns n!     
{
    BigInt prod = 1;
    int k;
    for(k = 1; k <= n; k++)
    {
        prod *= k;
    }
    return prod;
}
