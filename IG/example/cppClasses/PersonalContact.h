// Anne Marie Bogar                                                                                                                                                                                         
// December 4, 2013                                                                                                                                                                                         
// Final Lab                                                                                                                                                                                                
// PersonalContact Header File                                                                                                                                                                              

#include <iostream>
#include <string>
#include "Contact.h"
using namespace std;
#ifndef PERSONALCONTACT_H
#define PERSONALCONTACT_H

class PersonalContact : public Contact
{
   protected:
      int age;
      void display();
      // Outputs the values of the variable on the screen                                                                                                                                                   
      void edit();
      // Gives user a choice of which variable to edit,                                                                                                                                                     
      // then assigns the variable picked the new value entered by the user                                                                                                                                 
   public:
      void read(istream& in);
      // Allows a Contact instance to be taken from the file                                                                                                                                                
      // Takes in the values stored in the file                                                                                                                                                             
      // and assigns them to the Contact variables                                                                                                                                                          
      void print(ostream& out);
      // Allows a Contact instance to be stored in the file                                                                                                                                                 
      // Stores the value from each Contact variable in the file                                                                                                                                            
      friend class AddressBook;
      PersonalContact(string name1, string name2, string date, string number, string e_address, int years);
      // Personal contact constructor                                                                                                                                                                       
      // Assigns parameter values to Contact member variables                                                                                                                                               
      PersonalContact() {type = 'p';}
      // Assigns all Contact member variables a value of ""                                                                                                                                                 
};

#endif
