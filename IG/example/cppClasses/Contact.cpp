// Anne Marie Bogar
// December 4, 2013
// Final Lab
// Contact Implementation File

#include <iostream>
#include <string>
#include "Contact.h"
using namespace std;

Contact::Contact(string name1, string name2, string date, string number, string e_address)
{
   first_name = name1;
   last_name = name2;
   dob = date;
   telephone = number;
   email = e_address;
}

void Contact::display()
{
   cout << "First Name:       " << first_name << endl;
   cout << "Last Name:        " << last_name << endl;
   cout << "Telephone Number: " << telephone << endl;
   cout << "Date of Birth:    " << dob << endl;
   cout << "Email Address:    " << email << endl;
}

void Contact::edit()
{
   int choice;
   do
   {
      cout << "Choose the number of what you would like to edit:\n";
      cout << "(1) First name\n" << "(2) Last name\n" << "(3) Phone number\n" << "(4) Date of birth\n" << "(5) Email address\n" << "(6) Save and finish\n";
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
            break;
         default:
            cout << "Not a possible choice.";
      }
      cout << endl;
   }while (choice != 7);
}

bool Contact::matchLastName(string name)
{
   return last_name == name;
}

bool Contact::match(string Fname, string Lname)
{
   return ((last_name == Lname) && (first_name == Fname));
}

void Contact::read(istream& in)
{
   in >> first_name >> last_name >> telephone >> dob >> email;
}

void Contact::print(ostream& out)
{
   out << first_name << endl;
   out << last_name << endl;
   out << telephone << endl;
   out << dob << endl;
   out << email << endl;
}
             
