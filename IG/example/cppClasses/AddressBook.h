// Anne Marie Bogar                                                                                                                                                                                         
// December 4, 2013                                                                                                                                                                                         
// Final Lab                                                                                                                                                                                                
// AddressBook Header File                                                                                                                                                                                  

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include "Contact.h"
#include "PersonalContact.h"
#include "BusinessContact.h"
using namespace std;
#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

class AddressBook
{
   vector<Contact*> book;
public:
   AddressBook();
   // Takes in Contacts from the file and places them into vector list                                                                                                                                      
   ~AddressBook();
   // Writes the Contact instances from vector list into the file                                                                                                                                           
   // Exits the program using the exit function                                                                                                                                                             
   void add();
   // Creates a Contact using the values the user enters                                                                                                                                                    
   // Adds the new Contact to the vector list                                                                                                                                                               
   void search();
   // Prompts the user to enter a last name                                                                                                                                                                 
   // Searches the vector list for a Contact with the same last name                                                                                                                                        
   // Displays the Contact information if the Contact is found                                                                                                                                              
   void display_book();
   // Displays the Contact information of all the Contacts in vector list                                                                                                                                   
   void edit_contact();
   // Prompts user to enter a first and last name of a Contact                                                                                                                                              
   // Searches vector list for the Contact with the same names                                                                                                                                              
   // If the Contact is found, calls Contact member function edit()                                                                                                                                         
   void delete_contact();
   // Prompts user to enter a first and last name of a Contact                                                                                                                                              
   // Searches vector list for the Contact with the same names                                                                                                                                              
   // If the Contact is found, the instance is deleted from list                                                                                                                                            
   void sort();
   // Alphabetizes vector book, first by last_name and then by first_name                                                                                                                                   
   friend void swap(int a, int b, vector<Contact*>& v);
   // Swaps the value of one variable in vector book with another variable                                                                                                                                  
   // in book                                                                                                                                                                                               
};

#endif
