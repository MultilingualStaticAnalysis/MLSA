// Anne Marie Bogar                                                                                                                                                                                         
// October 23, 2013                                                                                                                                                                                         
// Lab 02                                                                                                                                                                                                   
// Address Book                                                                                                                                                                                             

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <vector>
using namespace std;
ifstream in_stream;
ofstream out_stream;
class Contact
{
      string first_name, last_name, dob, telephone, email;
      void display();
      // Outputs the values of the variable on the screen                                                                                                                                                   
      void edit();
      // Gives user a choice of which variable to edit,                                                                                                                                                     
      // then assigns the variable picked the new value entered by the user                                                                                                                                 
   public:
      friend istream& operator >>(istream& ins, Contact& c);
      // Allows a Contact instance to be taken from the file                                                                                                                                                
      // Takes in the values stored in the file                                                                                                                                                             
      // and assigns them to the Contact variables                                                                                                                                                          
      friend ostream& operator <<(ostream& outs, const Contact& c);
      // Allows a Contact instance to be stored in the file                                                                                                                                                 
      // Stores the value from each Contact variable in the file                                                                                                                                            
      friend void add(vector<Contact>& list);
      // Creates a Contact using the values the user enters                                                                                                                                                 
      // Adds the new Contact to the vector list                                                                                                                                                            
      friend void search(vector<Contact>& list);
      // Prompts the user to enter a last name                                                                                                                                                              
      // Searches the vector list for a Contact with the same last name                                                                                                                                     
      // Displays the Contact information if the Contact is found                                                                                                                                           
      friend void show_list(vector<Contact>& list);
      // Displays the Contact information of all the Contacts in vector list                                                                                                                                
      friend void leave(vector<Contact>& list);
      // Writes the Contact instances from vector list into the file                                                                                                                                        
      // Exits the program using the exit function                                                                                                                                                          
      friend void initialize(vector<Contact>& list);
      // Takes in Contacts from the file and places them into vector list                                                                                                                                   
      friend void edit_contact(vector<Contact>& list);
      // Prompts user to enter a first and last name of a Contact                                                                                                                                           
      // Searches vector list for the Contact with the same names                                                                                                                                           
      // If the Contact is found, calls Contact member function edit()                                                                                                                                      
      friend void delete_contact(vector<Contact>& list);
      // Prompts user to enter a first and last name of a Contact                                                                                                                                           
      // Searches vector list for the Contact with the same names                                                                                                                                           
      // If the Contact is found, the instance is deleted from list                                                                                                                                         
      Contact(string name1, string name2, string date, string number, string e_address);
      // Contact constructor                                                                                                                                                                                
      // Assigns parameter values to Contact member variables                                                                                                                                               
      Contact();
      // Assigns all Contact member variables a value of ""                                                                                                                                                 
};

int main()
{
   int choice;
   string name;
   vector<Contact> list;
   initialize(list);
   list.pop_back();

   cout << endl << "Welcome to your Address Book!" << endl;
   do
   {
      cout << endl;
      cout << "Please choose an option:" << endl;
      cout << "(1) Add a new contact" << endl;
      cout << "(2) Search by last name" << endl;
      cout << "(3) Show the complete list" << endl;
      cout << "(4) Edit a contact" << endl;
      cout << "(5) Delete a contact" << endl;
      cout << "(6) Exit" << endl;
      cin >> choice;
      cout << endl;
      switch(choice)
      {
         case 1:
            add(list);
            break;
         case 2:
            search(list);
            break;
         case 3:
           show_list(list);
            break;
         case 4:
            edit_contact(list);
            break;
          case 5:
            delete_contact(list);
            break;
         case 6:
            leave(list);
         default:
            cout << "Not a possible choice." << endl;
      }
   } while(1);
}

Contact::Contact(string name1, string name2, string date, string number, string e_address)
{
   first_name = name1;
   last_name = name2;
   dob = date;
   telephone = number;
   email = e_address;
}

Contact::Contact(): first_name(""), last_name(""), dob(""), telephone(""), email("")
{
}

void Contact::display()
{
   cout << "First Name:       " << first_name << endl;
   cout << "Last Name:        " << last_name << endl;
   cout << "Telephone Number: " << telephone << endl;
   cout << "Date of Birth:    " << dob << endl;
   cout << "Email Address:    " << email << endl;
   cout << "-----------------------------------------" << endl;
}

void Contact::edit()
{
   int choice;
   do
   {
      cout << "Choose the number of what you would like to edit:\n";
      cout << "(1) First name\n" << "(2) Last name\n" << "(3) Phone number\n" << "(4) Date of birth\n" << "(5) Email address\n" << "(6) Save and finish\n";
      cin >> choice;
      cout << endl;
      switch(choice) // checks which choice the user entered                                                                                                                                                
      {
        case 1:
            cout << "Enter the new first name: ";
            cin >> first_name;
            cout << endl;
            break;
         case 2:
            cout << "Enter the new last name: ";
            cin >> last_name;
            cout << endl;
            break;
         case 3:
            cout << "Enter the new phone number: ";
            cin >> telephone;
            cout << endl;
            break;
         case 4:
            cout << "Enter the new date of birth: ";
            cin >> dob;
            cout << endl;
            break;
         case 5:
            cout << "Enter the new email address: ";
            cin >> email;
            cout << endl;
            break;
         case 6:
            return;
         default:
            cout << "Not a possible choice.\n";
      }
   }while (1);
}

istream& operator >>(istream& ins, Contact& c)
{
   ins >> c.first_name >> c.last_name >> c.dob >> c.telephone >> c.email;
   return ins;
}

ostream& operator <<(ostream& outs, const Contact& c)
{
   outs << c.first_name << endl;
   outs << c.last_name << endl;
   outs << c.dob << endl;
   outs << c.telephone << endl;
   outs << c.email << endl;
   return outs;
}

void initialize(vector<Contact>& list)
{
   Contact c;
   in_stream.open("AddressBook.txt"); // opens file AddressBook.txt                                                                                                                                         
   if(in_stream.fail()) // If the file does not open, the program will exit                                                                                                                                 
   {
      cout << "Input file opening failed.\n";
      exit(1);
   }

   while( !in_stream.eof()) // reads in the values from the file to the end of the file                                                                                                                     
   {
      in_stream >> c;
      list.push_back(c); // adds Contact c to the vector list                                                                                                                                               
   }
   in_stream.close(); // closes the file                                                                                                                                                                    
}

void add(vector<Contact>& list)
{
   string f_name, l_name, date, number, e_address;
   cout << "Please enter the first name of the entry: ";
   cin >> f_name;
   cout << "Please enter the last name of the entry: ";
   cin >> l_name;
   cout << "Please enter the entry's telephone number (put dashes in between): ";
   cin >> number;
   cout << "Please enter the entry's date of birth (mm/dd/yyyy): ";
   cin >> date;
   cout << "Please enter the entry's email address: ";
   cin >> e_address;
   Contact c(f_name, l_name, date, number, e_address); // creats Contact c with entered values                                                                                                              
   list.push_back(c); // adds Contact c to vector list                                                                                                                                                      
}

void search(vector<Contact>& list)
{
   string name;
   cout << "Please enter a last name to search: ";
   cin >> name;
   cout << endl;
   int found = 0;
   for(int k = 0; k < list.size(); k++) // searches vector list                                                                                                                                             
   {
      if(list[k].last_name == name) // if the last names are the same                                                                                                                                       
      {
         list[k].display(); // displays Contact values on screen by calling display function                                                                                                                
         found++;
      }
   }
   if(found == 0) // No Contact was found that has the same last name
      cout << "Contact not found. " << endl;
}

void show_list(vector<Contact>& list)
{
   for(int k = 0; k < list.size(); k++) // access all Contacts in vector list                                                                                                                               
   {
   list[k].display();
   }
}

void delete_contact(vector<Contact>& list)
{
   string Fname, Lname;
   cout << "Enter the first and last names of the contact you would like to delete: ";
   cin >> Fname >> Lname;
   cout << endl;
   int found = 0;
   for(int k = 0; k < list.size(); k++) // Searches through the vector list                                                                                                                                 
   {
      if((list[k].last_name == Lname) && (list[k].first_name == Fname))
      {
         list.erase(list.begin() + k); // Deletes the Contact from list                                                                                                                                     
         found++;
      }
   }
   if(found == 0)
      cout << "Contact not found. " << endl;
}

void edit_contact(vector<Contact>& list)
{
   string Fname, Lname;
   cout << "Enter the first and last names of the contact you would like to edit: ";
   cin >> Fname >> Lname;
   cout << endl;
   int found = 0;
   for(int k = 0; k < list.size(); k++)
   {
      if((list[k].last_name == Lname) && (list[k].first_name == Fname))
      {
         list[k].edit(); // edits the Contact through edit function                                                                                                                                         
         found++;
         cout << "Your edited contact:\n" << endl;
         list[k].display(); // displays the Contact information through display function                                                                                                                    
      }
   }
   if(found == 0)
      cout << "Contact not found." << endl;
}

void leave(vector<Contact>& list)
{
   out_stream.open("AddressBook.txt"); // opens file AddressBook.txt                                                                                                                                        
   if(out_stream.fail()) // If the file cannot open, the program ends                                                                                                                                       
   {
      cout << "Output file opening failed.\n";
      exit(1);
   }

   for(int k = 0; k < list.size(); k++)
   {
      out_stream << list[k]; // Puts the Contacts from list into the file                                                                                                                                   
   }
   out_stream.close(); // closes the file                                                                                                                                                                   
   exit(0); // ends the program                                                                                                                                                                             
}
