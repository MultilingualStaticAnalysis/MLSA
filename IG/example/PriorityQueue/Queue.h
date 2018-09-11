// Anne Marie Bogar                                                                                                                                                                                         
// December 5, 2013                                                                                                                                                                                         
// Homework 10                                                                                                                                                                                              
// Queue Header file                                                                                                                                                                                        

//DISPLAY 13.21 Interface File for a Queue Class                                                                                                                                                            
//This is the header file queue.h. This is the interface for the class Queue,                                                                                                                               
//which is a class for a queue of symbols.                                                                                                                                                                  
#ifndef QUEUE_H
#define QUEUE_H
namespace queuesavitch
{
    struct QueueNode
    {
       int data;
       QueueNode *link;
    };

    typedef QueueNode* QueueNodePtr;

    class Queue
    {
    public:
       Queue( );
       //Initializes the object to an empty queue.                                                                                                                                                          
       Queue(const Queue& aQueue);
       ~Queue( );
       void add(int item);
       //Postcondition: item has been added to the back of the queue.                                                                                                                                       
       virtual int remove( );
       //Precondition: The queue is not empty.                                                                                                                                                              
       //Returns the item at the front of the queue and                                                                                                                                                     
       //removes that item from the queue.                                                                                                                                                                  
       bool empty( ) const;
       //Returns true if the queue is empty. Returns false otherwise.                                                                                                                                       
    protected:
       QueueNodePtr front;//Points to the head of a linked list.                                                                                                                                            
       //Items are removed at the head                                                                                                                                                                      
       QueueNodePtr back;//Points to the node at the other end of the                                                                                                                                       
       //linked list. Items are added at this end.                                                                                                                                                          
    };
}//queuesavitch                                                                                                                                                                                             
#endif //QUEUE_H