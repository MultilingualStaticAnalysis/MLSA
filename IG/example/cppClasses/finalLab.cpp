// Anne Marie Bogar                                                                                                                                                                                         
// December 4, 2013                                                                                                                                                                                         
// Final Lab                                                                                                                                                                                                
// Address Book                                                                                                                                                                                             

#include <iostream>
#include "Contact.h"
#include "AddressBook.h"
#include "PersonalContact.h"
#include "BusinessContact.h"
using namespace std;
int get_choice();
// Displays the menu for the Address Book program and prompts the user to                                                                                                                                   
// enter a number relating to which action the user wants to perform.                                                                                                                                       
// Returns the number the user enters                                                                                                                                                                       

int main()
{
   int choice;
   AddressBook address_book;

   cout << endl << "Welcome to your Address Book!" << endl;
   choice = get_choice();
   while(choice != 6)
   {
      switch(choice)
      {
         case 1:
            address_book.add();
            address_book.sort();
            break;
         case 2:
            address_book.search();
            break;
         case 3:
            address_book.display_book();
            break;
         case 4:
            address_book.edit_contact();
            break;
         case 5:
            address_book.delete_contact();
            break;
         default:
            cout << "Not a possible choice." << endl;
      }
      choice = get_choice();
   }
}

int get_choice()
{
   int choice;
   cout << endl;
   cout << "Please choose an option:" << endl;
   cout << "(1) Add a new contact" << endl;
   cout << "(2) Search by last name" << endl;
   cout << "(3) Show the complete list" << endl;
   cout << "(4) Edit a contact" << endl;
   cout << "(6) Exit" << endl;
   cin >> choice;
   cout << endl;
   return choice;
}
