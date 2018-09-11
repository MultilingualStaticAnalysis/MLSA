// Anne Marie Bogar                                                                                                                                                                                         
// December 5, 2013                                                                                                                                                                                         
// Homework 10                                                                                                                                                                                              
// Priority Queue Implementation file                                                                                                                                                                       

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "Queue.h"
#include "PriorityQueue.h"
using namespace std;

namespace queuesavitch
{
   //Uses cstddef:                                                                                                                                                                                          
   PriorityQueue::PriorityQueue() : Queue()
   {
      //Intentionally empty.                                                                                                                                                                                
   }

   PriorityQueue::PriorityQueue(const PriorityQueue& aPQueue)
   {
      front = aPQueue.front;
      back = aPQueue.back;
      // Self-test exercise 12                                                                                                                                                                              
   }

   PriorityQueue::~PriorityQueue()
   {
      //The definition of the destructor is Self-Test Exercise 13.                                                                                                                                          
   }

   //Uses cstdlib and iostream:                                                                                                                                                                             
   int PriorityQueue::remove()
   {
      if (empty())
      {
         cout << "Error: Removing an item from an empty queue.\n";
         exit(1);
      }
      QueueNodePtr p = front;
      QueueNodePtr discard, previous, here;
      QueueNodePtr next;
      int target = front->data;
      while(p->link != NULL)
      {
         here = p->link;
         if(here->data < target) // if a node has a value smaller than the first node's                                                                                                                     
         {
            target = here->data;
            discard = here;
            previous = p;
         }
         p = p->link;
      }

      if(target == front->data) // if the first node holds the smallest value                                                                                                                               
      {
         discard = front;
        front = front->link;
      }
      else if(discard->link == NULL) // if the last node holds the smallest value                                                                                                                           
         back = previous;
      else // if a middle node holds the smallest value                                                                                                                                                     
         previous->link = discard->link;
      if (front == NULL) //if you removed the last node                                                                                                                                                     
         back = NULL;

      delete discard;

      return target;
   }
}//queuesavitch                                                                                                                                                                                             


