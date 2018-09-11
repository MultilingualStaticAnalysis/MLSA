/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
October 28, 2014                                                                                                                                                                                            
Data Structures                                                                                                                                                                                             
Homework #2                                                                                                                                                                                                 
Recursion excercises                                                                                                                                                                                        
*/

#include <iostream>
using namespace std;
void writeLine(char c, int n);
void writeBlock(char c, int m, int n);
int factorial_01(int n);
void factorial_02(int n, int& f);

int main()
{
   int f;
   writeLine('*', 5);
   cout << endl << endl;

   writeBlock('$', 3, 5);

   cout << "8! = " << factorial_01(8) << endl << endl;
   cout << "5! = " << factorial_01(5) << endl << endl;
   cout << "12! = " << factorial_01(12) << endl << endl;

   factorial_02(8, f);
   cout << "8! = " << f << endl << endl;
   factorial_02(5, f);
   cout << "5! = " << f << endl << endl;
   factorial_02(12, f);
   cout << "12! = " << f << endl << endl;

   return 0;
}

//writes character c repeatedly to form a line of n characters                                                                                                                                              
void writeLine(char c, int n)
{
   if(n>1) //stopping case                                                                                                                                                                                  
      writeLine(c, n-1);
   cout << c;
}

//invokes writeLine to write m lines of n characters each                                                                                                                                                   
void writeBlock(char c, int m, int n)
{
   if(m>1) //stopping case                                                                                                                                                                                  
      writeBlock(c, m-1, n);
   writeLine(c, n);
   cout << endl << endl;
}

//returns the factorial of n (n!)                                                                                                                                                                           
int factorial_01(int n)
{
   int fact = 1; //fact must start at 1 for when n=1                                                                                                                                                        
   if(n>1) //stopping case
      fact = (n*factorial_01(n-1));
   return fact;
}

//makes f = the factorial of n (n!)                                                                                                                                                                         
//f is called by reference so that at the function's end, f will have the value of n!                                                                                                                       
//this allows the function to be void and the main function to print out the factorial value                                                                                                                
void factorial_02(int n, int& f)
{
   f=1; //f must start at 1 for when n=1                                                                                                                                                                    
   if(n>1) //stopping case                                                                                                                                                                                  
      factorial_02(n-1, f); //f is called my reference so that its value is changed for each function call                                                                                                  
   f*=n;
}
