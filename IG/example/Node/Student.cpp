/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 9, 2014                                                                                                                                                                                            
Data Structures                                                                                                                                                                                             
Student Source File                                                                                                                                                                                         
A Student object has a first name, last name, middle initial, social security number, and age. Each variable can be set and returned.                                                                       
The information can also be displayed on the screen in an easy-to-read format using the << operator                                                                                                         
*/

#include "Student.h"
using namespace std;

Student::Student(const Student& s) //copy constructor                                                                                                                                                       
{
   fname = s.fname;
   lname = s.lname;
   mi = s.mi;
   ssn = s.ssn;
   age = s.age;
}

void Student::setName(string f, string l, char m) //sets name (first, last, and middle initial)                                                                                                             
{
   fname = f;
   lname = l;
   mi = m;
}

void Student::setSSN(int s) //sets Social Security number                                                                                                                                                   
{
   ssn = s;
}

void Student::setAge(int a) //sets age                                                                                                                                                                      
{
   age = a;
}

string Student::getFirstName() const //returns first name                                                                                                                                                   
{
   return fname;
}

string Student::getLastName() const //returns last name                                                                                                                                                     
{
   return lname;
}

char Student::getMiddleInitial() const //returns middle initial                                                                                                                                             
{
   return mi;
}

int Student::getSSN() const //returns Social Security Number                                                                                                                                                
{
   return ssn;
}

int Student::getAge() const //returns age
{
   return age;
}

ostream& operator <<(ostream& outs, const Student& s) //displays Student information on the screen                                                                                                          
{
   cout << "Student:\t\t  " << s.lname << ", " << s.fname << " " << s.mi << endl;
   cout << "Social Security number:\t  " << s.ssn << endl;
   cout << "Age:\t\t\t  " << s.age << endl;
   cout << "------------------------------------------------------" << endl;

   return outs;
}

istream& operator >>(istream& ins, Student& s) //used for getting student information from txt file                                                                                                         
{
   ins >> s.fname >> s.lname >> s.mi >> s.ssn >> s.age;
}

void Student::print(ostream& out) //used for saving student information into a txt file                                                                                                                     
{
   out << fname << endl;
   out << lname << endl;
   out << mi << endl;
   out << ssn << endl;
   out << age << endl;
}

bool Student::operator >(const Student& s) const
{
   return (lname.compare(s.lname) > 0);
}

bool Student::operator <(const Student& s) const
{
   return (lname.compare(s.lname) < 0);
}