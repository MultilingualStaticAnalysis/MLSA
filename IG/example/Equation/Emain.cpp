//Anne Marie Bogar                                                                                                                                                                                          
//September 30, 2014                                                                                                                                                                                        
//Data Structures                                                                                                                                                                                           
//Equation Main File                                                                                                                                                                                        

#include <iostream>
#include "Equation.h"
#include "HugeInteger.h"
using namespace std;

int main()
{
   Equation e;

   cout << endl << "Enter an equation: ";
   cin >> e;

   while(!e.end()) //if user enters 0x0, e.end will be true                                                                                                                                                 
   {
      e.calculate(); //calculates the equation requested by the user and displays the result                                                                                                                
      cout << "Enter another equation (or 0x0 to exit): ";
      cin >> e;
   }

   return 0;
}
