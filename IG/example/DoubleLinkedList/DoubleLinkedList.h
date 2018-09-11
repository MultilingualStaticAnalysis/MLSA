/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 25, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Double Linked List Header File                                                                                                                                                                              
*/

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "LinkedList.h"
#include "Node.h"

template <class T>
class DoubleLinkedList : public LinkedList
{
protected:
   Node<T>* tail;
public:
   DoubleLinkedList(); //default constructor                                                                                                                                                                
   DoubleLinkedList(const DoubleLinkedList<T>& dl, bool sort = false); //copy constructor. Sorts list if requested                                                                                          
   ~DoubleLinkedList(); //destructor                                                                                                                                                                        
   Node<T>* getTail() const;
   void append(Node<T>* n); //adds Node at end of list                                                                                                                                                      
   void deleteAtPos(int pos); //deletes node at specified position                                                                                                                                          
   void insertAtPos(Node<T>* n, int pos); //inserts node at specified position                                                                                                                              
   void displayAscending() const; //displays list head to tail                                                                                                                                              
   void displayDescending() const; //displays list tail to head                                                                                                                                             
   void sort(bool ascend = true); //sorts list either in ascending or descending order                                                                                                                      
};

template <class T>
DoubleLinkedList::DoubleLinkedList() //default constructor                                                                                                                                                  
{
   head = NULL;
   tail = NULL;
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& dl, bool sort) //copy constructor, can also sort new list                                                                                  
{
   head = NULL;
   tail = NULL;
   Node<T>* nPtr;

   if(!dl.isEmpty())
   {
      Node<T>* curr = dl.head;
      while(curr) //copies each node                                                                                                                                                                        
      {
         nPtr = new Node<T>(*curr); //creates new Node with the copy Student                                                                                                                                
         append(nPtr); //append new node to the new list                                                                                                                                                    
         curr = curr -> getNext();
      }
      if(sort) //if user requests the new list to be sorted                                                                                                                                                 
         selectionSort(); //sorts list using the selectionSort method                                                                                                                                       
   }
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() //destructor                                                                                                                                                       
{
   Node<T>* curr = head;
   Node<T>* del;
   while(curr)
   {
      del = curr;
      curr = curr -> getNext();
      delete del; //releases the Node memory                                                                                                                                                                
   }
   del = NULL;
   head = NULL;
   tail = NULL;
}

template <class T>
Node<T>* DoubleLinkedList<T>::getTail() const //returns the tail                                                                                                                                            
{
   return tail;
}

template <class T>
void DoubleLinkedList<T>::append(Node<T>* n) //appends new Node to list                                                                                                                                     
{
   Node<T>* curr;
   if(head == NULL)
      head = n; //first Node added to the list                                                                                                                                                              
   else
   {
      curr = head;
      while(curr -> getNext()) //finds the last Node in the list                                                                                                                                            
         curr = curr -> getNext();
      curr -> setNext(n); //appends Node onto the end of the list                                                                                                                                           
      n -> setPrev(curr);
   }
   tail = n; //Node is added to end of list, so tail points to new Node                                                                                                                                     
}

template <class T>
void DoubleLinkedList<T>::deleteAtPos(int pos) //deletes a node at the position indicated in the list                                                                                                       
{
   Node<T>* curr = head;
   if(pos <= getNumNode() && pos > 0) //if position is in list parameters and the list is not empty                                                                                                         
   {
      for(int k=1; k<pos; k++) //loop to arrive at the position                                                                                                                                             
      {
         curr = curr->getNext();
      }
      if(pos == getNumNode()) //last node in the list                                                                                                                                                       
         tail = curr->getPrev(); //tail points to second-last node                                                                                                                                          
      else
         curr->getNext()->setPrev(curr->getPrev());
      if(pos == 1) //first node in the list                                                                                                                                                                 
         head = curr->getNext(); //head points to second node                                                                                                                                               
      else
         curr->getPrev()->setNext(curr->getNext());
      delete curr; //deletes node                                                                                                                                                                           
      curr = NULL;
   }
}

template <class T>
void DoubleLinkedList<T>::insertAtPos(Node<T>* n, int pos) //inserts a node at the position indicated in the list                                                                                           
{
   Node<T>* curr = head;
   if(pos <= getNumNode() && pos > 0) //if position is in list parameters and the list is not empty                                                                                                         
   {
      for(int k=1; k<pos; k++) //loop to arrive at the position requested                                                                                                                                   
      {
         curr = curr->getNext();
      }
      n->setNext(curr); //sets up new Node's next and prev pointers                                                                                                                                         
      n->setPrev(curr->getPrev());
      curr->setPrev(n);
      if(pos == 1) //if node is the first in the list                                                                                                                                                       
         head = n; //head points to the new Node                                                                                                                                                            
      else
         n->getPrev()->setNext(n);
   }
}

template <class T>
void DoubleLinkedList<T>::displayAscending() const //displays list from head to tail                                                                                                                        
{
   display(); //calls display function defined in LinkedList.cpp                                                                                                                                            
}

template <class T>
void DoubleLinkedList<T>::displayDescending() const //displays list from tail to head
{
   Node<T>* curr = tail;
   while(curr != NULL) //goes through all Nodes                                                                                                                                                             
   {
      cout << curr -> getObject() << endl; //displays Student information                                                                                                                                   
      curr = curr -> getPrev(); //goes to the previous Node in the list                                                                                                                                     
   }
}

template <class T>
void DoubleLinkedList<T>::sort(bool ascend) //sorts the list, either in ascending or descending order                                                                                                       
{
   if(ascend) //ascending order                                                                                                                                                                             
      selectionSort();
   else //descending order                                                                                                                                                                                  
      bubbleSort(); //function was changed to accomodate descending order in LinkedList.cpp                                                                                                                 
}

#endif
