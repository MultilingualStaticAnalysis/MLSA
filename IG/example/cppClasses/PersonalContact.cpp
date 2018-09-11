// Anne Marie Bogar                                                                                                                                                                                         
// December 4, 2013                                                                                                                                                                                         
// Final Lab                                                                                                                                                                                                
// PersonalContact Implementation File                                                                                                                                                                      

#include <iostream>
#include <string>
#include "Contact.h"
#include "PersonalContact.h"
using namespace std;

PersonalContact::PersonalContact(string name1, string name2, string date, string number, string e_address, int years) : Contact(name1, name2, date, number, e_address)
{
   //Contact(name1, name2, date, number, e_address);                                                                                                                                                        
   age = years;
   type = 'p';
}

void PersonalContact::display()
{
   Contact::display();
   cout << "Age:              " << age << endl;
   cout << "-----------------------------------------" << endl;
}

void PersonalContact::edit()
{
   int choice;
   do
   {
      cout << "Choose the number of what you would like to edit:\n";
      cout << "(1) First name\n" << "(2) Last name\n" << "(3) Phone number\n" << "(4) Date of birth\n" << "(5) Email address\n" << "(6) Age\n" << "(7) Save and finish\n";
      cin >> choice;
      cout << endl << "Enter the new ";
      switch(choice) // checks which choice the user entered                                                                                                                                                
      {
         case 1:
            cout << "first name: ";
            cin >> first_name;
            break;
         case 2:
            cout << "last name: ";
            cin >> last_name;
            break;
         case 3:
            cout << "phone number: ";
            cin >> telephone;
            break;
         case 4:
            cout << "date of birth: ";
            cin >> dob;
            break;
         case 5:
            cout << "email address: ";
            cin >> email;
            break;
         case 6:
            cout << "age: ";
            cin >> age;
            break;
         case 7:
            break;
         default:
            cout << "Not a possible choice.";
      }
      cout << endl;
   }while (choice != 7);
}

void PersonalContact::read(istream& in)
{
   Contact::read(in);
   in >> age;
}

void PersonalContact::print(ostream& out)
{
   out << 'p' << endl;
   Contact::print(out);
   out << age << endl;
}
