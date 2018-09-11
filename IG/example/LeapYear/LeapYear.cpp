// Anne Marie Bogar                                                                                                                                                                                         
// April 4, 2013                                                                                                                                                                                            
// Extra Credit (modified Lab 07)                                                                                                                                                                           
// A date is entered by the user, and the program checks whether the date is valid based on the month, day, and whether or not the year is a leap year                                                      

#include <iostream>
using namespace std;
bool date_checker(int month, int day, int year); // Declare boolean function date_checker                                                                                                                   
bool leap_year(int year); // Declare boolean function leap_year                                                                                                                                             
void enter_date(int& month, int& date, int& year); // Declare void function enter_date                                                                                                                      

int main ()
{
   int month, day, year; // Variable declarations                                                                                                                                                           
   char ans;

   cout << "Welcome to Date Checker!\n";
   cout << endl << "Now taking inputs from the user ... \n";
   do
   {
      enter_date(month, day, year); // Calls function enter_date                                                                                                                                            

      if(date_checker(month, day, year)) // Calls function date_checker using entered data and checks if it returns true                                                                                    
         cout << "Date " << month << "/" << day << "/" << year << " is valid.\n";
      else
         cout << "Date " << month << "/" << day << "/" << year << " is NOT valid.\n";

      cout << "Do you want to continue? Enter Y or y to continue:\n";
      cin >> ans; // Assigns entered data into variable ans                                                                                                                                                 
   } while (ans == 'y' || ans == 'Y'); // If user entered either y or Y, the loop will go again                                                                                                             
   return 0; // Ends program                                                                                                                                                                                
}

bool date_checker(int month, int day, int year) // Defines function date_checker                                                                                                                            
//precondition: variables month, day, and year hold the appropriate date that the user entered                                                                                                              
//postcondition: The dates are checked to see if they are valid (only 12 months, and number of days appropriate to the given month)                                                                         
{
   switch (month) // Checks data in variable month                                                                                                                                                          
   {
      case 4:
      case 6:
      case 9:
      case 11:
         if (day >= 1 && day <= 30) // April, June, Sept., and Nov. have 30 days                                                                                                                            
            return true; // Returns a true value because the date is valid                                                                                                                                  
         else
            return false; // Returns a false value because the date is invalid                                                                                                                              
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
         if (day >= 1 && day <= 31) // Jan., March, May, July, August, Oct., and Dec. have 31 days                                                                                                          
            return true;
         else
            return false;
      case 2:
         if(leap_year(year)) // Checks if the year entered is a leap year or not                                                                                                                            
         {
            if (day >= 1 && day <= 29) // February has 29 days during leap years                                                                                                                            
               return true;
            else
               return false;
         }
         else
         {
            if (day >= 1 && day <= 28) // February only has 28 days during years that are not leap years                                                                                                    
               return true;
            else
               return false;
         }
      default: // The value in month is not 1-12, so there is no corresponding month                                                                                                                        
         return false;
   }
}

bool leap_year(int year) // Function definition                                                                                                                                                             
//precondition: The variable contains the year the user entered                                                                                                                                             
//postcondition: the function returns true if the year is a leap year, based on the algorithm                                                                                                               
{
   if (year%400 == 0) // If a year is divisible by 400, then it is a leap year                                                                                                                              
      return true;
   else if (year%100 == 0) // A year that is divisible by 100 but not by 400 is not a leap year                                                                                                             
      return false;
   else if (year%4 == 0) // Most years that are divisible by 4 (except the prior examples) are leap years                                                                                                   
      return true;
   else
      return false;
}

void enter_date(int& month, int& day, int& year) // Function definition with call-by-reference parameters                                                                                                   
//precondition: variables month, day, and year are the same variables as defined in the main function, and await an assignment                                                                              
//postcondition: The variables are assigned the data that the user enters                                                                                                                                   
{
   cout << "Please enter a date using the following format: mm dd yyyy\n";
   cin >> month >> day >> year; // The entered data are assigned to the appropriate call-by-reference variables                                                                                             
}
