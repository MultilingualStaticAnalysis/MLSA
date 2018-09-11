// Anne Marie Bogar                                                                                                                                                                                         
// December 4, 2013                                                                                                                                                                                         
// Final Lab                                                                                                                                                                                                
// BusinessContact Implementation File                                                                                                                                                                      

#include <iostream>
#include <string>
#include "Contact.h"
#include "BusinessContact.h"
using namespace std;

BusinessContact::BusinessContact(string name1, string name2, string date, string number, string e_address, string fax_num) : Contact(name1, name2, date, number, e_address)
{
   fax = fax_num;
   type = 'b';
}

void BusinessContact::display()
{
   Contact::display();
   cout << "Fax Number:       " << fax << endl;
   cout << "-----------------------------------------" << endl;
}

void BusinessContact::edit()
{
   int choice;
   do
   {
      cout << "Choose the number of what you would like to edit:\n";
      cout << "(1) First name\n" << "(2) Last name\n" << "(3) Phone number\n" << "(4) Date of birth\n" << "(5) Email address\n" << "(6) Fax Number\n" << "(7) Save and finish\n";
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
            cout << "fax number: ";
            cin >> fax;
            break;
         case 7:
            break;
         default:
            cout << "Not a possible choice.";
      }
      cout << endl;
   }while (choice != 7);
}

void BusinessContact::read(istream& in)
{
   Contact::read(in);
   in >> fax;
}

void BusinessContact::print(ostream& out)
{
   out << 'b' << endl;
   Contact::print(out);
   out << fax << endl;
}
