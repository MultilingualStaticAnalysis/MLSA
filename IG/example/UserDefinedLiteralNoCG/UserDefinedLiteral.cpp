// C++ code to demonstrate working of user defined
// literals (UDLs)
#include<iostream>
using namespace std;

// user defined literals

// KiloGram
long double operator"" _kg( long double x )
{
	return x*1000;
}

// Gram
long double operator"" _g( long double x )
{
	return x;
}

// MiliGram
long double operator"" _mg( long double x )
{
	return x / 1000;
}

// Driver code
int main()
{
	long double weight = 3.6_kg;
	cout << weight << endl;
	cout << ( weight + 2.3_mg ) << endl;
	cout << ( 32.3_kg / 2.0_g ) << endl;
	cout << ( 32.3_mg *2.0_g ) << endl;
	return 0;
}