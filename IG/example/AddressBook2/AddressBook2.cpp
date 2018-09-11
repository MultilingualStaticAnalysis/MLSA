// Anne Marie Bogar                                                                                                                                                                                         
// November 20, 2013                                                                                                                                                                                        
// Lab 03                                                                                                                                                                                                   
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
   protected:
      string first_name, last_name, dob, telephone, email, fax;
      int age;
      char type;
      void display();
      // Outputs the values of the variable on the screen                                                                                                                                                   
      void edit();
      // Gives user a choice of which variable to edit,                                                                                                                                                     
      // then assigns the variable picked the new value entered by the user                                                                                                                                 
      bool matchLastName(string name);
      // Compares the string name with the Contact's last_name                                                                                                                                              
      // Returns true if the two variables are the same                                                                                                                                                     
      bool match(string Fname, string Lname);
      // Compares the string Fname with the Contact's first_name                                                                                                                                            
      // and the string Lname witht he Contact's last_name                                                                                                                                                  
      // Returns true if both sets of variables are the same                                                                                                                                                
   public:
      friend bool operator >(Contact& a, Contact& b);
      // Comtares the last_name of each Contact                                                                                                                                                             
      // Returns true if Contact b's last_name is alphabetically                                                                                                                                            
      // lower (towards the front of the alphabet)                                                                                                                                                          
      friend bool operator ==(Contact& a, Contact& b);
      // Compares the last_name of eact Contact                                                                                                                                                             
      // Returns true if the last_name of both Contacts are equal                                                                                                                                           
      friend istream& operator >>(istream& ins, Contact& c);
      // Allows a Contact instance to be taken from the file                                                                                                                                                
      // Takes in the values stored in the file                                                                                                                                                             
      // and assigns them to the Contact variables                                                                                                                                                          
      friend ostream& operator <<(ostream& outs, const Contact& c);
      // Allows a Contact instance to be stored in the file                                                                                                                                                 
      // Stores the value from each Contact variable in the file                                                                                                                                            
      friend class AddressBook;
      Contact(string name1, string name2, string date, string number, string e_address, int years);
      // Personal contact constructor                                                                                                                                                                       
      // Assigns parameter values to Contact member variables                                                                                                                                               
      Contact(string name1, string name2, string date, string number, string e_address, string fax_num);
      Contact() {}
      // Assigns all Contact member variables a value of ""                                                                                                                                                 
};
class AddressBook
{
      vector<Contact> book;
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
      friend void swap(int a, int b, vector<Contact>& v);
      // Swaps the value of one variable in vector book with another variable                                                                                                                               
      // in book                                                                                                                                                                                            
};
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
   cout << "(5) Delete a contact" << endl;
   cout << "(6) Exit" << endl;
   cin >> choice;
   cout << endl;
   return choice;

}

Contact::Contact(string name1, string name2, string date, string number, string e_address, int years)
{
   first_name = name1;
   last_name = name2;
   dob = date;
   telephone = number;
   email = e_address;
   age = years;
   fax = "---";
   type = 'p';
}

Contact::Contact(string name1, string name2, string date, string number, string e_address, string fax_num)
{
   first_name = name1;
   last_name = name2;
   dob = date;
   telephone = number;
   email = e_address;
   fax = fax_num;
   age = -1;
   type = 'b';
}

void Contact::display()
{
   cout << "First Name:       " << first_name << endl;
   cout << "Last Name:        " << last_name << endl;
   cout << "Telephone Number: " << telephone << endl;
   cout << "Date of Birth:    " << dob << endl;
   cout << "Email Address:    " << email << endl;
   if(type == 'b')
      cout << "Fax Number:       " << fax << endl;
   else
      cout << "Age:              " << age << endl;
   cout << "-----------------------------------------" << endl;
}

void Contact::edit()
{
   int choice;
   do
   {
      cout << "Choose the number of what you would like to edit:\n";
      cout << "(1) First name\n" << "(2) Last name\n" << "(3) Phone number\n" << "(4) Date of birth\n" << "(5) Email address\n";
      if(type == 'b')
         cout << "(6) Fax Number\n" << "(7) Save and finish\n";
      else
         cout << "(6) Age\n" << "(7) Save and finish\n";
      cin >> choice;
      cout << endl << "Enter the new ";;
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
            if(type == 'b')
            {
               cout << "fax number: ";
               cin >> fax;
            }
            else
            {
               cout << "age: ";
               cin >> age;
            }
            break;
         case 7:
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

bool operator >(Contact& a, Contact& b)
{
   return a.last_name > b.last_name;
}

bool operator ==(Contact& a, Contact& b)
{
   return a.last_name == b.last_name;
}

istream& operator >>(istream& ins, Contact& c)
{
   ins >> c.first_name >> c.last_name >> c.dob >> c.telephone >> c.email >> c.fax >> c.age >> c.type;;
   return ins;
}

ostream& operator <<(ostream& outs, const Contact& c)
{
   outs << c.first_name << endl;
   outs << c.last_name << endl;
   outs << c.dob << endl;
   outs << c.telephone << endl;
   outs << c.email << endl;
   outs << c.fax << endl;
   outs << c.age << endl;
   outs << c.type << endl;
   return outs;
}

AddressBook::AddressBook()
{
   Contact c;
   in_stream.open("AddressBook.txt"); // opens file AddressBook.txt                                                                                                                                         
   if(in_stream.fail()) // If the file does not open, the program will exit                                                                                                                                 
   {
      cout << "Input file opening failed.\n";
      exit(1);
   }

   while(!in_stream.eof()) // reads in the values from the file to the end of the file                                                                                                                      
   {
      in_stream >> c;
      book.push_back(c); // adds Contact c to the vector list                                                                                                                                               
   }
   in_stream.close(); // closes the file                                                                                                                                                                    
   book.pop_back();
}

void AddressBook::add()
{
   string f_name, l_name, date, number, e_address, fax_num;
   int choice = 0, years;
   while(choice != 1 && choice != 2)
   {
      cout << "Would you like to create a (1) personal contact, or (2) business contact? ";
      cin >> choice;
      if(choice != 1 && choice != 2)
         cout << "Not a possible choice.\n";
   }

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
   if(choice == 1)
   {
      cout << "Please enter the entry's age: ";
      cin >> years;
      Contact personal(f_name, l_name, date, number, e_address, years);
      book.push_back(personal);
   }
   else if(choice == 2)
   {
      cout << "Please enter the entry's fax number: ";
      cin >> fax_num;
      Contact business(f_name, l_name, date, number, e_address, fax_num);
      book.push_back(business);
   }
}

void AddressBook::search()
{
   string name;
   cout << "Please enter a last name to search: ";
   cin >> name;
   cout << endl;
   int found = 0;
   for(int k = 0; k < book.size(); k++) // searches vector list                                                                                                                                             
   {
      if(book[k].matchLastName(name)) // if the last names are the same                                                                                                                                     
      {
         book[k].display(); // displays Contact values on screen by calling display function                                                                                                                
         found++;
      }
   }
   if(found == 0) // No Contact was found that has the same last name                                                                                                                                       
      cout << "Contact not found. " << endl;
}

void AddressBook::display_book()
{
   for(int k = 0; k < book.size(); k++) // access all Contacts in vector list                                                                                                                               
   {
   book[k].display();
   }
}

void AddressBook::delete_contact()
{
   string Fname, Lname;
   cout << "Enter the first and last names of the contact you would like to delete: ";
   cin >> Fname >> Lname;
   cout << endl;

   for(int k = 0; k < book.size(); k++) // Searches through the vector list                                                                                                                                 
   {
      if(book[k].match(Fname, Lname))
      {
         book.erase(book.begin() + k); // Deletes the Contact from list                                                                                                                                     
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
   for(int k = 0; k < book.size(); k++)
   {
      if(book[k].match(Fname, Lname))
      {
         book[k].edit(); // edits the Contact through edit function
         cout << "Your edited contact:\n" << endl;
         book[k].display(); // displays the Contact information through display function                                                                                                                    
         return;
      }
   }
   cout << "Contact not found." << endl;
}

void swap(int a, int b, vector<Contact>& v)
{
   Contact temp = v[a];
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
         if(book[k] > book[k+1])
         {
            swap(k, k+1, book);
            swaped = true;
         }
         if(book[k] == book[k+1])
         {
            if(book[k].first_name > book[k+1].first_name)
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
   out_stream.open("AddressBook.txt"); // opens file AddressBook.txt                                                                                                                                        
   if(out_stream.fail()) // If the file cannot open, the program ends                                                                                                                                       
   {
      cout << "Output file opening failed.\n";
      exit(1);
   }

   for(int k = 0; k < book.size(); k++)
   {
      out_stream << book[k]; // Puts the Contacts from list into the file                                                                                                                                   
   }
   out_stream.close(); // closes the file                                                                                                                                                                   
   exit(0); // ends the program                                                                                                                                                                             
}
