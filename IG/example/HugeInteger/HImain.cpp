//Anne Marie Bogar                                                                                                                                                                                          
//September 26, 2014                                                                                                                                                                                        
//Data Structures                                                                                                                                                                                           
//HugeInteger Main File                                                                                                                                                                                     

#include <iostream>
#include "HugeInteger.h"
#include <vector>
#include <string>
using namespace std;
void initialize(HugeInteger& h1, HugeInteger& h2, char& s);
void equate(const HugeInteger& h1, const HugeInteger& h2, HugeInteger& h3, char s);

int main()
{
   HugeInteger hi1, hi2, hi3;
   char sign;

   initialize(hi1, hi2, sign);//initializes variables with values entered by the user                                                                                                                       

   if(hi1.isBad() || hi2.isBad())//if either HugeInteger is returned with a "bad" array, then the number exceeded the digit limit                                                                           
      return 1;

   equate(hi1, hi2, hi3, sign); //equates the operation that the user requested and displays result                                                                                                         

   return 0;
}

void initialize(HugeInteger& h1, HugeInteger& h2, char& s)
{
   cout << endl << "Enter an equation(+, *, -, ==, !=, <=, >=): ";
   cin >> h1 >> s >> h2; //initializes HugeIntegers with the value entered by the user, and the operation sign with operation the user requested                                                            
   cout << endl;
}

void equate(const HugeInteger& h1, const HugeInteger& h2, HugeInteger& h3, char s)
{
   cout << "The equation you entered is: ";

   switch(s)//decideds which operation to do based on user input                                                                                                                                            
   {
      case '+':
         cout << h1 << " + " << h2 << endl << endl;
         h3 = h1 + h2;
         if(h3.isBad())//if the sum exceeds digit limit, the HugeInteger returned will have a "bad" array                                                                                                   
            break;
         cout << "The sum of " << h1 << " and " << h2 << " is " << h3 << endl << endl;
         break;
      case '*':
         cout << h1 << " * " << h2 << endl << endl;
         h3 = h1 * h2;
         if(h3.isBad())
            break;
         cout << "The product of " << h1 << " and " << h2 << " is " << h3 << endl << endl;
         break;
      case '-':
         cout << h1 << " - " << h2 << endl << endl;
         h3 = h1 - h2;
         if(h3.isBad())
            break;
         cout << "The difference between " << h1 << " and " << h2 << " is " << h3 << endl << endl;
         break;
      case '=':
         cout << h1 << " == " << h2 << endl << endl;
         if(h1 == h2)
            cout << h1 << " is equal to " << h2 << endl << endl;
         else
            cout << h1 << " is not equal to " << h2 << endl << endl;
         break;
      case '!':
         cout << h1 << " != " << h2 << endl << endl;
         if(h1 != h2)
            cout << h1 << " is not equal to " << h2 << endl << endl;
         else
            cout << h1 << " is equal to " << h2 << endl << endl;
         break;
      case '<':
         cout << h1 << " <= " << h2 << endl << endl;
         if(h1 <= h2)
            cout << h1 << " is less than or equal to " << h2 << endl << endl;
         else
            cout << h1 << " is greater than " << h2 << endl << endl;
         break;
      case '>':
         cout << h1 << " >= " << h2 << endl << endl;
         if(h1 >= h2)
            cout << h1 << " is greater than or equal to " << h2 << endl << endl;
         else
            cout << h1 << " is less than " << h2 << endl << endl;
         break;
      default: //if the requested operation is not offered, default will run                                                                                                                                
         cout << "INVALID" << endl << endl;
   }
}

