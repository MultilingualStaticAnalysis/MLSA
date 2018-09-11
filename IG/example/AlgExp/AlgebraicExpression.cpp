/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
December 16, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Algebraic Expression Source File                                                                                                                                                                            
An Algebraic Expression takes in an infix epression, changes it to a postfix expression, and then calculates the postfix expression.                                                                        
It can also figure out if the expression entered is valid or not.                                                                                                                                           
*/

#include "AlgebraicExpression.h"

AlgebraicExpression::AlgebraicExpression() //default constructor                                                                                                                                            
{
   result = 0;
   infix = "";
   postfix = "";
}

AlgebraicExpression::AlgebraicExpression(string s)
{
   result = 0;
   infix = s;
   postfix = "";
}

void AlgebraicExpression::evaluatePostfix() //calculates the result of the postfix expression                                                                                                               
{
   char c;
   int i, op1, op2, r;
   if(valid()) //if the equation is valid, the result will be calculated                                                                                                                                    
   {
      if(postfix.length() >= 1) //makes sure that the equation has been converted to postfix expression                                                                                                     
      {
         for(int k=0; k<postfix.length(); k++) //loops through the entire postfix expression                                                                                                                
         {
            c = postfix.at(k);
            i = int(c) - int('0');
            if(i >= 0 && i <= 9) //operand                                                                                                                                                                  
               operandStack.push(i); //add operand to stack                                                                                                                                                 
            else //operator                                                                                                                                                                                 
            {
               op2 = operandStack.top(); //takes top two operands from stack for operation                                                                                                                  
               op1 = operandStack.top();
               if(c == '+')
                  r = op1 + op2;
               else if(c == '-')
                  r = op1 - op2;
               else if(c == '*')
                  r = op1 * op2;
               else if(c == '/')
               {
                  if(op2 != 0) //avoids division by 0                                                                                                                                                       
                     r = op1 / op2;
                  else //if trying to divide by 0, error will occur and program will end                                                                                                                    
                  {
                     cerr << "\nError: cannot divide by 0 " << endl;
                     exit( 1 ); //terminate program;                                                                                                                                                        
                  }
               }
              operandStack.push(r); //returns the result of the operation to the stack                                                                                                                     
            }
         }
      }
      if(operandStack.size() == 1) //the only thing left on the stack is the result of the equation                                                                                                         
         result = operandStack.top();
   }
   else //if equation is invalid, error will occur and program will end                                                                                                                                     
   {
      cerr << "\nError: expression is invalid " << endl;
      exit( 1 ); // terminate program;                                                                                                                                                                      
   }
}

void AlgebraicExpression::evaluateInfix() //turns the infix expression into a postfix expression                                                                                                            
{
   char c, op;
   int i;
   if(valid()) //only evaluates infix expression if equation is valid                                                                                                                                       
   {
      for(int k=0; k<infix.length(); k++) //loops through the infix expression                                                                                                                              
      {
         c = infix.at(k);
         i = int(c) - int('0');
         if(i >= 0 && i <= 9) //operand                                                                                                                                                                     
            postfix += c; //append operand to postfix string                                                                                                                                                
         else if(c == '(')
            operatorStack.push(c); //add opening parentheses to stack                                                                                                                                       
         else if(c == ')')
         {
            op = operatorStack.top();
            while(op != '(') //until closing opening parentheses is found                                                                                                                                   
            {
               postfix += op; //add operator to postfix string                                                                                                                                              
               op = operatorStack.top(); //get next element from stack                                                                                                                                      
            }
         }
         else if(c == '+'||c == '-'||c == '*'||c == '/') //operator                                                                                                                                         
         {
            if(!operatorStack.isEmpty())
            {
               op = operatorStack.peek(); //look at top of stack, but don't access it                                                                                                                       
               while(!operatorStack.isEmpty() && op != '(' && precedence(op, c))
               {
                  postfix += operatorStack.top(); //add operator of greater precedence to postfix string                                                                                                    
                  if(!operatorStack.isEmpty())
                     op = operatorStack.peek();
               }
            }
            operatorStack.push(c); //add original operator to stack                                                                                                                                         
         }
      }
      while(!operatorStack.isEmpty()) //any leftover operators still on stack should be added to postfix string                                                                                             
      {
         op = operatorStack.top();
         postfix += op;
      }
   }
   else //if equation is invalid, an error will occur and the program will end                                                                                                                              
   {
      cerr << "\nError: expression is invalid " << endl;
      exit( 1 ); // terminate program;                                                                                                                                                                      
   }
}

bool AlgebraicExpression::precedence(char op1, char op2) //decided precedence of operators (* and / are greater than + and -)                                                                               
{
   //precendence if an op1 is greater than or equal to (in precendence) op2                                                                                                                                 
   bool prec = true; //assume precedence                                                                                                                                                                    
   if(op1 == '+' || op1 == '-') //if op1 is + or - and op2 is * or /, there is no precendence                                                                                                               
   {
         if(op2 == '*' || op2 == '/')
            prec = false;
   }
   return prec;
}

int AlgebraicExpression::getResult() //returns the result of the equation                                                                                                                                   
{
   return result;
}

istream& operator >>(istream& ins, AlgebraicExpression& ae) //makes cin >> AlgebraicExpression possible                                                                                                     
{
   ins >> ae.infix; //the only thing initially needed in an AlgebraicExpression is the infix expression                                                                                                     
}

bool AlgebraicExpression::valid() //checks to see whether the infix expression is valid                                                                                                                     
{
   char c, h;
   bool valid = true; //assume valid                                                                                                                                                                        
   Stack<char> paren, op;
   int countOp=0, countInt=0, j, i;
   if(infix.length() > 1)
   {
      for(int k=0; k<infix.length(); k++) //loops though infix expression                                                                                                                                   
      {
         c = infix.at(k);
         i = int(c) - int('0');

         if(c == '(') //checks if parentheses have pairs                                                                                                                                                    
            paren.push(c);
         else if(c == ')')
         {
            if(!paren.isEmpty())
               paren.pop();
            else
               valid = false; //no pair                                                                                                                                                                     
         }
         else if(c=='+' || c=='*' || c=='/' || c=='-') //checks if each operator has two operands                                                                                                           
            op.push(c);
         else if(i>=0 && i<=9)
         {
            if(!op.isEmpty())
               op.pop();
         }
      }
      if(!paren.isEmpty()) //no pair                                                                                                                                                                        
         valid = false;
      if(!op.isEmpty()) //no two operands        
         valid = false;
   }

   c = infix.at(0);
   i = int(c) - int('0');
   if(!(c == '(' || (i>=0 && i<=9))) //checks if the first element in the expression is a number or open parentheses                                                                                        
      valid = false;

   if(infix.length() > 1)
   {
      for(int k=0; k<infix.length()-1; k++)
      {
         c = infix.at(k);
         i = int(c) - int('0');
         h = infix.at(k+1);
         j = int(h) - int ('0');
         if(c == '(' && (h=='+' || h=='-' || h=='*' || h=='/')) // *(                                                                                                                                       
            valid = false;
         if(h == ')' && (c=='+' || c=='-' || c=='*' || c=='/')) // *)                                                                                                                                       
            valid = false;
         if(h == '(' && (i>=0 && i<=9)) // 9(                                                                                                                                                               
            valid = false;
         if(c == ')' && (j>=0 && j<=9)) // )9                                                                                                                                                               
            valid = false;
         if(c=='+' || c=='-' || c=='*' || c=='/') //checks for expressions without operators                                                                                                                
            countOp++;
         if(i>=0 && i<=9)
            countInt++;
      }
      if(countInt > 1 && countOp < 1) //invalid if expression has more than one number but no operators                                                                                                     
         valid = false;
   }

   return valid;
}

