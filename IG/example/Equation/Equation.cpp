//Anne Marie Bogar                                                                                                                                                                                          
//September 30, 2014                                                                                                                                                                                        
//Data Structures                                                                                                                                                                                           
//Equation Source File                                                                                                                                                                                      

#include <iostream>
#include "Equation.h"
#include "HugeInteger.h"
using namespace std;

Equation::Equation()
{
   condition = true;
}

Equation::Equation(HugeInteger& h1, HugeInteger& h2, char s, bool c)
{
   op1 = h1;
   op2 = h2;
   sign = s;
   condition = c;
}

Equation& Equation::operator =(const Equation& e2) //assigns one Equation object to another                                                                                                                 
{
   op1 = e2.op1;
   op2 = e2.op2;
   result = e2.result;
   sign = e2.sign;
   condition = e2.condition;

   return *this;
}

void Equation::calculate()
{
   if(!condition)//checks to see if HugeIntegers in the equation are good                                                                                                                                   
      cout << "Error! The numbers in the equation exceed the digit limit." << endl << endl;
   else
   {
      switch(sign)//decideds which operation to do based on user input                                                                                                                                      
      {
         case '+':
            result = op1 + op2;
            if(result.isBad())//if the sum exceeds digit limit, the HugeInteger returned will have a "bad" array                                                                                            
               break;
            cout << *this;
            break;
         case '*':
            result = op1 * op2;
            if(result.isBad())
               break;
            cout << *this;
            break;
         case '-':
            result = op1 - op2;
            if(result.isBad())
               break;
            cout << *this;
            break;
         case '=':
            if(op1 == op2)
               cout << *this << "is true." << endl << endl;
            else
               cout << *this << "is false." << endl << endl;
            break;
         case '!':
            if(op1 != op2)
               cout << *this << "is true." << endl << endl;
            else
               cout << *this << "is false." << endl << endl;
            break;
         case '<':
            if(op1 <= op2)
               cout << *this << "is true." << endl << endl;
            else
               cout << *this << "is false." << endl << endl;
            break;
         case '>':
            if(op1 >= op2)
               cout << *this << "is true." << endl << endl;
            else
               cout << *this << "is false." << endl << endl;
            break;
         default: //if the requested operation is not offered, default will run                                                                                                                             
            cout << "The equation entered is: INVALID" << endl << endl;
      }
   }
   return;
}

bool Equation::end() const // checks to see if the user entered 0x0                                                                                                                                         
{
   return (op1.isZero() && op2.isZero() && sign=='x');
}

ostream& operator <<(ostream& outs, const Equation& e)
{
   if(e.sign == '+' || e.sign == '*' || e.sign == '-') //if the operation was +,*, or -, the anser will have a result                                                                                       
      outs << endl << e.op1 << " " << e.sign << " " << e.op2 << " = " << e.result << endl << endl;
   else //for the comparison operators                                                                                                                                                                      
      outs << endl << e.op1 << " " << e.sign << "= " << e.op2 << " ";
   return outs;
}

istream& operator >>(istream& ins, Equation& e)
{
   bool c;
   char s;
   HugeInteger h1, h2;

   ins >> h1 >> s >> h2;
   if(h1.isBad() || h2.isBad()) //registers that the equation is bad                                                                                                                                        
      c = false;
   else
      c = true;

   Equation temp(h1, h2, s, c);
   e = temp;

   return ins;
}
