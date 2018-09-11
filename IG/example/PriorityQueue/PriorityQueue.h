// Anne Marie Bogar                                                                                                                                                                                         
// December 5, 2013                                                                                                                                                                                         
// Homework 10                                                                                                                                                                                              
// Priority Queue Header file                                                                                                                                                                               

#include "Queue.h"
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
namespace queuesavitch
{
   /* struct QueueNode                                                                                                                                                                                      
    {                                                                                                                                                                                                       
       int data;                                                                                                                                                                                            
       QueueNode *link;                                                                                                                                                                                     
    };                                                                                                                                                                                                      
                                                                                                                                                                                                            
    typedef QueueNode* QueueNodePtr;*/

    class PriorityQueue : public Queue
    {
    public:
       PriorityQueue( );
       //Initializes the object to an empty queue.                                                                                                                                                          
       PriorityQueue(const PriorityQueue& aPQueue);
       ~PriorityQueue( );
       int remove( );
       //Precondition: The queue is not empty.                                                                                                                                                              
       //Returns the item at the front of the queue and                                                                                                                                                     
       //removes that item from the queue.                                                                                                                                                                  
    };
}//queuesavitch                                                                                                                                                                                             
#endif //PRIORITYQUEUE_H