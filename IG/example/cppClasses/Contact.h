// Anne Marie Bogar                                                                                                                                                                                         
// December 4, 2013                                                                                                                                                                                         
// Final Lab                                                                                                                                                                                                
// Contact Header File                                                                                                                                                                                      

#include <iostream>
#include <string>
using namespace std;
#ifndef CONTACT_H
#define CONTACT_H

class Contact
{
protected:
   string first_name, last_name, dob, telephone, email;
   char type;
   virtual void display();
   // Outputs the values of the variable on the screen                                                                                                                                                      
   virtual void edit();
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
   virtual void read(istream& in);
   virtual void print(ostream& out);
   //virtual friend istream& operator >>(istream& ins, Contact& c);                                                                                                                                         
   // Allows a Contact instance to be taken from the file                                                                                                                                                   
   // Takes in the values stored in the file                                                                                                                                                                
   // and assigns them to the Contact variables                                                                                                                                                             
   //virtual friend ostream& operator <<(ostream& outs, const Contact& c);                                                                                                                                  
   // Allows a Contact instance to be stored in the file                                                                                                                                                    
   // Stores the value from each Contact variable in the file                                                                                                                                               
   friend class AddressBook;
   Contact(string name1, string name2, string date, string number, string e_address);
   // Assigns parameter values to Contact member variables                                                                                                                                                  
   Contact() {}
   // Assigns all Contact member variables a value of ""                                                                                                                                                    
};

#endif
