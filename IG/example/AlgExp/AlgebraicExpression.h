/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
December 16, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Algebraic Expression Header File                                                                                                                                                                            
An Algebraic Expression takes in an infix epression, changes it to a postfix expression, and then calculates the postfix expression.                                                                        
It can also figure out if the expression entered is valid or not.                                                                                                                                           
*/

#ifndef ALGEBRAICEXPRESSION_H
#define ALGEBRAICEXPRESSION_H

#include "Stack.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <typeinfo>
using namespace std;

class AlgebraicExpression
{
   friend istream& operator >>(istream& ins, AlgebraicExpression& ae);
private:
   Stack<char> operatorStack; //stack for evaluating infix expression                                                                                                                                       
   Stack<int> operandStack; //stack for evaluating postfix expression                                                                                                                                       
   int result; //result of equation                                                                                                                                                                         
   string infix; //infix expression                                                                                                                                                                         
   string postfix; //postfix expression                                                                                                                                                                     
   bool precedence(char op1, char op2); //checks if op1 has precedence over op2                                                                                                                             

public:
   AlgebraicExpression(); //default constructor                                                                                                                                                             
   AlgebraicExpression(string s); //constructor (s = infix)                                                                                                                                                 
   void evaluatePostfix(); //calculates the result of the postfix expression                                                                                                                                
   void evaluateInfix(); //converts infix expression into a postfix expression                                                                                                                              
   int getResult(); //returns result of postfix expression                                                                                                                                                  
   bool valid(); //checks validity of infix expression                                                                                                                                                      
};

#endif
