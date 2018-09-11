/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 9, 2014                                                                                                                                                                                            
Data Structures                                                                                                                                                                                             
Node Header File                                                                                                                                                                                            
*/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

template <class T>
class Node
{
private:
   //Student* sPtr; //points to Student object                                                                                                                                                              
   T* tPtr;
   Node<T>* next; //points to next Node in list                                                                                                                                                             
   Node<T>* prev;
public:
   Node();
   Node(T* t);
// Node(Student* s);                                                                                                                                                                                        
// Node(string f, string l, char m, int ss, int a);                                                                                                                                                         
   Node(const Node<T>& n);
   ~Node();
   Node<T>* getNext() const;
   Node<T>* getPrev() const;
   T getObject() const;
// Student getStudent() const;                                                                                                                                                                              
   void setNext(Node<T>* n);
   void setPrev(Node<T>* p);
};

template <class T>
Node<T>::Node() //default constructor. All pointers are set to NULL                                                                                                                                         
{
   tPtr = NULL;
   next = NULL;
   prev = NULL;
}

template <class T>
Node<T>::Node(T* t) //constructor takes in a Student pointer                                                                                                                                                
{
   tPtr = t;
   next = NULL;
   prev = NULL;
}

template <class T>
Node<T>::Node(const Node<T>& n) //copy constructor                                                                                                                                                          
{
   tPtr = new T(n.getObject()); //calls copy constructor of Student                                                                                                                                         
   next = NULL;
   prev = NULL;
}

template <class T>
Node<T>::~Node() //releases memory of dynamically allocated memory of Student object                                                                                                                        
{
   if(tPtr)
   {
      delete tPtr;
      tPtr = NULL;
   }
}

template <class T>
Node<T>* Node<T>::getNext() const //returns the next Node in the list                                                                                                                                       
{
   return next;
}

template <class T>
Node<T>* Node<T>::getPrev() const
{
   return prev;
}

template <class T>
void Node<T>::setNext(Node<T>* n) //sets the next Node in the list                                                                                                                                          
{
   next = n;
}

template <class T>
void Node<T>::setPrev(Node<T>* p)
{
   prev = p;
}

template <class T>
T Node<T>::getObject() const //returns the Student object of the Node                                                                                                                                       
{
   return *tPtr;
}

#endif
