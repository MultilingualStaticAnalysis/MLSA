//Anne Marie Bogar                                                                                                                                                                                          
//September 30, 2014                                                                                                                                                                                        
//Data Structures                                                                                                                                                                                           
//Equation Header File                                                                                                                                                                                      

#ifndef EQUATION_H
#define EQUATION_H
#include <iostream>
#include <string>
#include <vector>
#include "HugeInteger.h"
using namespace std;

class Equation
{
   friend ostream& operator <<(ostream& outs, const Equation& hi);
   friend istream& operator >>(istream& ins, Equation& hi);

private:
   HugeInteger op1;
   HugeInteger op2;
   HugeInteger result;
   char sign;
   bool condition;

public:
   Equation();
   Equation(HugeInteger& h1, HugeInteger& h2, char s, bool c);
   Equation& operator =(const Equation& e2);
   void calculate();
   bool end() const;

};

#endif
