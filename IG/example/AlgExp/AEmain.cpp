/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
December 16, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Algebraic Expressions Driver File                                                                                                                                                                           
Driver prompts the user to enter an equation or - to quit. The program then checks whether the equation is valid, and if it is not,                                                                         
the program prompts the user to enter another equation. When the equation is proven valid, the equation's infix epression is then                                                                           
converted to postfix expression. Then, the postfix expression is evaluated, and the result is printed out.                                                                                                  
The program then prompts the user for another equation or - to quit.                                                                                                                                        
*/

#include "AlgebraicExpression.h"
#include "Stack.h"
using namespace std;

int main()
{
   AlgebraicExpression* aPtr;
   string s;
   cout << "\nEnter an equation or - to quit: ";
   cin >> s;
   while(s != "-")
   {
      aPtr = new AlgebraicExpression(s);
      while(!aPtr->valid())
      {
         cout << "\nExpression is invalid! Please enter a new expression: ";
         cin >> s;
         aPtr = new AlgebraicExpression(s);
      }
      aPtr->evaluateInfix();
      aPtr->evaluatePostfix();
      cout << aPtr->getResult() << endl;
      cout << "\nEnter an equation or - to quit: ";
      cin >> s;
   }
   cout << endl;

   return 0;
}

