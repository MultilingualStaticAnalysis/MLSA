/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 25, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Double Linked List Source File                                                                                                                                                                              
The Double Linked List is a list that enploys Nodes that point to the next Node in the list as well as the previous Node in the list.                                                                       
The Double Linked List has a head that points to the first node in the list and a tail that points to the last node in the list.                                                                            
The List can add and delete nodes, display the list in ascending and descending order, and sort the list both is ascending and descending order.                                                            
*/

#include "DoubleLinkedList.h"
#include "LinkedList.h"

DoubleLinkedList::DoubleLinkedList() //default constructor                                                                                                                                                  
{
   head = NULL;
   tail = NULL;
}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& dl, bool sort) //copy constructor, can also sort new list                                                                                        
{
   head = NULL;
   tail = NULL;
   Node* nPtr;
   Student* sPtr;
   if(!dl.isEmpty())
   {
      Node* curr = dl.head;
      while(curr) //copies each node                                                                                                                                                                        
      {
         nPtr = new Node(*curr); //creates new Node with the copy Student                                                                                                                                   
         append(nPtr); //append new node to the new list                                                                                                                                                    
         curr = curr -> getNext();
      }
      if(sort) //if user requests the new list to be sorted                                                                                                                                                 
         selectionSort(); //sorts list using the selectionSort method                                                                                                                                       
   }
}

DoubleLinkedList::~DoubleLinkedList() //destructor                                                                                                                                                          
{
   Node* curr = head;
   Node* del;
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

Node* DoubleLinkedList::getTail() const //returns the tail                                                                                                                                                  
{
   return tail;
}

void DoubleLinkedList::append(Node* n) //appends new Node to list                                                                                                                                           
{
   Node* curr;
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

void DoubleLinkedList::deleteAtPos(int pos) //deletes a node at the position indicated in the list                                                                                                          
{
   Node* curr = head;
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

void DoubleLinkedList::insertAtPos(Node* n, int pos) //inserts a node at the position indicated in the list                                                                                                 
{
   Node* curr = head;
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

void DoubleLinkedList::displayAscending() const //displays list from head to tail                                                                                                                           
{
   display(); //calls display function defined in LinkedList.cpp
}

void DoubleLinkedList::displayDescending() const //displays list from tail to head                                                                                                                          
{
   Node* curr = tail;
   while(curr != NULL) //goes through all Nodes                                                                                                                                                             
   {
      cout << curr -> getStudent() << endl; //displays Student information                                                                                                                                  
      curr = curr -> getPrev(); //goes to the previous Node in the list                                                                                                                                     
   }
}

void DoubleLinkedList::sort(bool ascend) //sorts the list, either in ascending or descending order                                                                                                          
{
   if(ascend) //ascending order                                                                                                                                                                             
      selectionSort();
   else //descending order                                                                                                                                                                                  
      bubbleSort(); //function was changed to accomodate descending order in LinkedList.cpp                                                                                                                 
}

