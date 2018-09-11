/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 9, 2014                                                                                                                                                                                            
Data Structures                                                                                                                                                                                             
Student Header File                                                                                                                                                                                         
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
using namespace std;

class Student
{
   friend ostream& operator <<(ostream& outs, const Student& s);
   friend istream& operator >>(istream& ins, Student& s);
   friend class Node;

private:
   string fname; //first name                                                                                                                                                                               
   string lname; //last name                                                                                                                                                                                
   char mi; //middle initial                                                                                                                                                                                
   int ssn; //social security number                                                                                                                                                                        
   int age; //age                                                                                                                                                                                           

public:
   Student(): fname(""), lname(""), mi(' '), ssn(0), age(0) {} //default constructor                                                                                                                        
   Student(string f, string l, char m, int s, int a): fname(f), lname(l), mi(m), ssn(s), age(a) {}
   Student(const Student& s); //copy constructor                                                                                                                                                            
   void setName(string f, string l, char m);
   void setSSN(int s);
   void setAge(int a);
   string getFirstName() const;
   string getLastName() const;
   char getMiddleInitial() const;
   int getSSN() const;
   int getAge() const;
   void read(istream& in);
   void print(ostream& out);
   bool operator >(const Student& s) const;
   bool operator <(const Student& s) const;
};

#endif
