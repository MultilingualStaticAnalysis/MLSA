// Anne Marie Bogar                                                                                                                                                                                         
// September 26, 2014                                                                                                                                                                                       
// Data Structures                                                                                                                                                                                          
// HugeInteger Header File                                                                                                                                                                                  

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

class HugeInteger
{
   friend ostream& operator <<(ostream& outs, const HugeInteger& hi);
   friend istream& operator >>(istream& ins, HugeInteger& hi);

private:
   static const int MAXDIGITS = 40;
   int digits[MAXDIGITS];
   vector<int> num;
   char sign;
   bool operator >(const HugeInteger& h2) const;
   HugeInteger returnBad() const;
   bool overflow(vector<int> v) const;
   bool overflow(vector<char> v) const;
   void setUp(const HugeInteger& h, int a1[], int a2[], int& len1, int& len2, char& s) const;

public:
   HugeInteger();
   HugeInteger(vector<char> vec);
   HugeInteger(vector<int> vec);
   HugeInteger(vector<int> vec, char s);
   HugeInteger& operator =(const HugeInteger& h2);
   HugeInteger operator +(const HugeInteger& h2) const;
   HugeInteger operator *(const HugeInteger& h2) const;
   HugeInteger operator -(const HugeInteger& h2) const;
   bool operator ==(const HugeInteger& h2) const;
   bool operator !=(const HugeInteger& h2) const;
   bool operator >=(const HugeInteger& h2) const;
   bool operator <=(const HugeInteger& h2) const;
   bool isBad() const;
   bool isZero() const;
   friend class Equation;
};

#endif
