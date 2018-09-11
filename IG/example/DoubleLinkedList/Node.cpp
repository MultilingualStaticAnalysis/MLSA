/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 9, 2014                                                                                                                                                                                            
Data Structures                                                                                                                                                                                             
Node Source File                                                                                                                                                                                            
The Node has three pointer member variables, one that points to a Student object, one that points to the next Node object in the list,                                                                      
and one that points to the previous Node object in the list.                                                                                                                                                
*/

#include "Node.h"
#include "Student.h"
using namespace std;

Node::Node() //default constructor. All pointers are set to NULL                                                                                                                                            
{
   sPtr = NULL;
   next = NULL;
   prev = NULL;
}

Node::Node(Student* s) //constructor takes in a Student pointer                                                                                                                                             
{
   sPtr = s;
   next = NULL;
   prev = NULL;
}

Node::Node(const Node& n) //copy constructor                                                                                                                                                                
{
   sPtr = new Student(n.getStudent()); //calls copy constructor of Student                                                                                                                                  
   next = NULL;
   prev = NULL;
}

Node::Node(string f, string l, char m, int ss, int a) //constructor creates a dynamically allocated Student object                                                                                          
{
   sPtr = new Student(f, l, m, ss, a);
   next = NULL;
   prev = NULL;
}

Node::~Node() //releases memory of dynamically allocated memory of Student object                                                                                                                           
{
   if(sPtr)
   {
      delete sPtr;
      sPtr = NULL;
   }
}

Node* Node::getNext() const //returns the next Node in the list                                                                                                                                             
{
   return next;
}

Node* Node::getPrev() const
{
   return prev;
}

void Node::setNext(Node* n) //sets the next Node in the list                                                                                                                                                
{
   next = n;
}

void Node::setPrev(Node* p)
{
   prev = p;
}

Student Node::getStudent() const //returns the Student object of the Node                                                                                                                                   
{
   return *sPtr;
}

