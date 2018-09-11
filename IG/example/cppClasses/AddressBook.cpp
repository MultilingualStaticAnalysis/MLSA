// Anne Marie Bogar                                                                                                                                                                                         
// December 4, 2013                                                                                                                                                                                         
// Final Lab                                                                                                                                                                                                
// AddressBook Implementation File                                                                                                                                                                          

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include "Contact.h"
#include "AddressBook.h"
#include "PersonalContact.h"
#include "BusinessContact.h"
using namespace std;
ifstream in_stream;
ofstream out_stream;

AddressBook::AddressBook()
{
   Contact* c;
   char contact_type;
   in_stream.open("AddressBook2.txt"); // opens file AddressBook.txt                                                                                                                                        
   if(in_stream.fail()) // If the file does not open, the program will exit                                                                                                                                 
   {
      cout << "Input file opening failed.\n";
      exit(1);
   }

   while(!in_stream.eof()) // reads in the values from the file to the end of the file                                                                                                                      
   {
      in_stream >> contact_type;
      if(contact_type == 'p')
      {
         c = new PersonalContact;
      }
      else if(contact_type == 'b')
      {
         c = new BusinessContact;
      }
      c->read(in_stream);
      book.push_back(c);
   }
   in_stream.close(); // closes the file                                                                                                                                                                    
   book.pop_back();
}

void AddressBook::add()
{
   int choice = 0;
   while(choice != 1 && choice != 2)
   {
      cout << "Would you like to create a (1) personal contact, or (2) business contact? ";
      cin >> choice;
      if(choice != 1 && choice != 2)
         cout << "Not a possible choice.\n";
   }

   cout << "Please enter the information for the contact in all six fields:\n";
   cout << "1. First Name\n";
   cout << "2. Last Name\n";
   cout << "3. Telephone Number\n";
   cout << "4. Date of Birth (mm/dd/yyyy)\n";
   cout << "5. Email Address\n";
   if(choice == 1)
   {
      cout << "6. Age\n";
      Contact* pc = new PersonalContact;
      pc->read(cin);
      book.push_back(pc);
   }
   else if(choice == 2)
   {
      cout << "6. Fax\n";
      Contact* bc = new BusinessContact;
      bc->read(cin);
      book.push_back(bc);
   }
}

void AddressBook::search()
{
   string name;
   cout << "Please enter a last name to search: ";
   cin >> name;
   cout << endl;
   int found = 0;
   cout << "-----------------------------------------" << endl;
   for(vector<Contact*>::iterator it = book.begin(); it != book.end(); it++) //searches vector book                                                                                                         
   {
      if((*it)->matchLastName(name)) // if the last names are the same                                                                                                                                      
      {
         (*it)->display(); // displays Contact values on screen by calling display function                                                                                                                 
         found++;
      }
   }
   if(found == 0) // No Contact was found that has the same last name                                                                                                                                       
      cout << "Contact not found. " << endl;
}

void AddressBook::display_book()
{
   int pnum = 0, bnum = 0;
   cout << "-----------------------------------------" << endl;
   for(vector<Contact*>::iterator it = book.begin(); it != book.end(); it++)// access all Contact*s in book                                                                                                 
   {
      (*it)->display();
   }
   cout << "There are " << book.size() << " contacts in the address book.\n";
}

void AddressBook::delete_contact()
{
   string Fname, Lname;
   cout << "Enter the first and last names of the contact you would like to delete: ";
   cin >> Fname >> Lname;
   cout << endl;

   for(vector<Contact*>::iterator it = book.begin(); it != book.end(); it++)
   {
      if((*it)->match(Fname, Lname))
      {
         book.erase(it); // deletes the Contact from book                                                                                                                                                   
         return;
      }
   }
   cout << "Contact not found. " << endl;
}

void AddressBook::edit_contact()
{
   string Fname, Lname;
   cout << "Enter the first and last names of the contact you would like to edit: ";
   cin >> Fname >> Lname;
   cout << endl;
   for(vector<Contact*>::iterator it = book.begin(); it != book.end(); it++)
   {
      if((*it)->match(Fname, Lname))
      {
         (*it)->edit(); // edits the Contact through edit function                                                                                                                                          
         cout << "Your edited contact:\n" << endl;
         cout << "-----------------------------------------" << endl;
         (*it)->display(); // displays the Contact information through display function                                                                                                                     
         return;
      }
   }
	book[0]->display();
   cout << "Contact not found." << endl;
}

void swap(int a, int b, vector<Contact*>& v)
{
   Contact* temp = v[a];
   v[a] = v[b];
   v[b] = temp;
}

void AddressBook::sort()
{
   bool swaped;
   Contact temp;
   do
   {
      swaped = false;
      for(int k = 0; k < book.size()-1; k++)
      {
         if(book[k]->last_name > book[k+1]->last_name)
         {
            swap(k, k+1, book);
            swaped = true;
         }
         if(book[k]->last_name == book[k+1]->last_name)
         {
            if(book[k]->first_name > book[k+1]->first_name)
            {
               swap(k, k+1, book);
               swaped = true;
            }
         }
      }  
   }while(swaped);
}

AddressBook::~AddressBook()
{
   out_stream.open("AddressBook2.txt"); // opens file AddressBook.txt                                                                                                                                       
   if(out_stream.fail()) // If the file cannot open, the program ends                                                                                                                                       
   {
      cout << "Output file opening failed.\n";
      exit(1);
   }

   //for(int k = 0; k < book.size(); k++)                                                                                                                                                                   
   for(vector<Contact*>::iterator it = book.begin(); it != book.end(); it++)
   {
      (*it)->print(out_stream); // Puts the Contacts from list into the file                                                                                                                                
   }
   out_stream.close(); // closes the file                                                                                                                                                                   
   for(int k = 0; k < book.size(); k++)
   {
      delete book[k];
   }
}
