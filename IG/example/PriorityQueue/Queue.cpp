// Anne Marie Bogar                                                                                                                                                                                         
// December 5, 2013                                                                                                                                                                                         
// Homework 10                                                                                                                                                                                              
// Queue Implementation file                                                                                                                                                                                

//DISPLAY 13.23 Implementation of the Queue Class                                                                                                                                                           
//This is the implementation file queue.cpp.                                                                                                                                                                
//This is the implementation of the class Queue.                                                                                                                                                            
//The interface for the class Queue is in the header file queue.h.                                                                                                                                          
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "Queue.h"
using namespace std;

namespace queuesavitch
{
   //Uses cstddef:                                                                                                                                                                                          
   Queue::Queue( ) : front(NULL), back(NULL)
   {
      //Intentionally empty.                                                                                                                                                                                
   }

   Queue::Queue(const Queue& aQueue)
   {
      front = aQueue.front;
      back = aQueue.back;
   }
   //The definition of the copy constructor is Self-Test Exercise 12.                                                                                                                                       

   Queue::~Queue( )
   {
      /*if(front != NULL)                                                                                                                                                                                   
      {                                                                                                                                                                                                     
         QueueNodePtr here = front;                                                                                                                                                                         
         QueueNodePtr discard;                                                                                                                                                                              
         while(here->link != NULL)                                                                                                                                                                          
         {                                                                                                                                                                                                  
            discard = here;                                                                                                                                                                                 
            here = here->link;                                                                                                                                                                              
            delete discard;                                                                                                                                                                                 
         }                                                                                                                                                                                                  
         }*/
   }
   //The definition of the destructor is Self-Test Exercise 13.                                                                                                                                             

   //Uses cstddef:                                                                                                                                                                                          
   bool Queue::empty( ) const
   {
      return (back == NULL);//front == NULL would also work                                                                                                                                                 
   }

   //Uses cstddef:                                                                                                                                                                                          
   void Queue::add(int item)
   {
      if (empty( ))
      {
         front = new QueueNode;
         front->data = item;
       back = front;
      }

      else
      {
         QueueNodePtr temp_ptr;
         temp_ptr = new QueueNode;

         temp_ptr->data = item;
         temp_ptr->link = NULL;
         back->link = temp_ptr;
         back = temp_ptr;
      }
   }

   //Uses cstdlib and iostream:                                                                                                                                                                             
   int Queue::remove( )
   {
      if (empty( ))
      {
         cout << "Error: Removing an item from an empty queue.\n";
         exit(1);
      }

      int result = front->data;

      QueueNodePtr discard;
      discard = front;
      front = front->link;
      if (front == NULL) //if you removed the last node                                                                                                                                                     
         back = NULL;

      delete discard;

      return result;
   }
}//queuesavitch                                                                                                                                                                                             


