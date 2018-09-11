/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 12, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Linked List Source File                                                                                                                                                                                     
The linked list has a Node pointer called head that is the front of the list. A linked list can add Nodes, delete Nodes, display the information from the Nodes, and sort the Nodes by Student last name (u\
sing three different functions)                                                                                                                                                                             
*/

#include "LinkedList.h"
#include "Node.h"
#include "Student.h"
using namespace std;

LinkedList::LinkedList() //default constructor                                                                                                                                                              
{
   head = NULL;
}

LinkedList::LinkedList(const LinkedList& l, bool sort) //copy constructor. Sorts the list by age is sort = true                                                                                             
{
   head = NULL;
   Node* nPtr;
   Student* sPtr;
   if(!l.isEmpty())
   {
      Node* curr = l.head;
      while(curr)
      {
         nPtr = new Node(*curr); //creates new Node with the copy Student                                                                                                                                   
         if(sort && head) //if the user requested the list sorted and the list has at least one Node                                                                                                        
            insert(nPtr);
         else //if the user did not request the list to be sorted OR is the list is just beginning                                                                                                          
            append(nPtr);
         curr = curr -> getNext();
      }
   }
}

LinkedList::~LinkedList() //decostructor releases all the dynamically allocated memory                                                                                                                      
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
}

int LinkedList::getNumNode() const //returns the number of Nodes in the linked list                                                                                                                         
{
   Node* curr = head;
   int count = 0;
   while(curr)
   {
     count++; //adds to count for every Node in the list                                                                                                                                                   
      curr = curr -> getNext();
   }
   return count;
}

Node* LinkedList::getHead() const//returns head                                                                                                                                                             
{
   return head;
}

void LinkedList::append(Node* n) //adds a Node to the end of the linked list                                                                                                                                
{
   Node* curr;
   if(head == NULL)
      head = n; //first Node added to the list                                                                                                                                                              
   else
   {
      curr = head;
      while(curr -> getNext() != NULL) //finds the last Node in the list                                                                                                                                    
         curr = curr -> getNext();
      curr -> setNext(n); //appends Node onto the end of the list                                                                                                                                           
   }
}

bool LinkedList::deleteNode(string target) //deletes Node with the specified first name                                                                                                                     
{
   bool del = false;
   Node* curr = head;
   int pos = 1;
   while(curr && !del) //finds the last Node in the list                                                                                                                                                    
   {
      if(curr->getStudent().getFirstName() != target) //if the student is not the one being searched for                                                                                                    
      {
         curr = curr->getNext(); //get next node                                                                                                                                                            
         pos++;
      }
      else //student is the target                                                                                                                                                                          
      {
         deleteAtPos(pos); //delete the node                                                                                                                                                                
         del = true;
      }
   }
 return del;
}

void LinkedList::deleteAtPos(int pos) //deletes node at the specified positiion                                                                                                                             
{
   Node* curr = head;
   Node* prev = NULL; //prev starts at NULL because curr starts at head                                                                                                                                     
   if(pos <= getNumNode() && pos > 0) //if position is in list parameters and the list is not empty                                                                                                         
   {
      if(pos == 1) //node is at the beginning of the list                                                                                                                                                   
         head = curr->getNext(); //takes node out of list                                                                                                                                                   
      else //node is in the middle of the list or at the end                                                                                                                                                
      {
         for(int k=1; k<pos; k++) //loop to arrive at the position                                                                                                                                          
         {
            prev = curr; //goes to next node                                                                                                                                                                
            curr = curr->getNext();
         }
         prev->setNext(curr->getNext()); //takes node out of the list                                                                                                                                       
      }
      delete curr; //deletes node                                                                                                                                                                           
      curr = NULL;
   }
}

void LinkedList::display() const //displays the entire list of Student information on the screen                                                                                                            
{
   displayNode(head);
}

void LinkedList::displayNode(Node* curr) const
{
   if(curr) //checks to see if curr is not NULL                                                                                                                                                             
   {
      cout << curr -> getStudent() << endl; //displays Student information                                                                                                                                  
      displayNode(curr -> getNext()); //calls display with the next Node in the list                                                                                                                        
   }
}

bool LinkedList::isEmpty() const //checks if the list is empty                                                                                                                                              
{
   bool empty = false;
   if(head == NULL) //is head is NULL, then there is no list of Nodes                                                                                                                                       
      empty = true;
   return empty;
}

void LinkedList::insert(Node* n) //inserts a Node into the list depending on the Student's last name                                                                                                        
{
   bool foundPos = false;
   Node* curr = head;
   int pos = 1;
   while(curr && !foundPos) //finds the last Node in the list                                                                                                                                               
   {
      if(n->getStudent().getLastName().compare(curr->getStudent().getLastName()) > 0) //student's last name is father down in the alphabet                                                                  
      {
         curr = curr->getNext(); //go to next node                                                                                                                                                          
         pos++;
      }
      else //student is at the right place alphabetically                                                                                                                                                   
      {
         insertAtPos(n, pos); //insert node at that position                                                                                                                                                
         foundPos = true;
      }
   }
   if(!foundPos) //student is last in list alphabetically                                                                                                                                                   
      append(n); //add to end of list                                                                                                                                                                       
}

void LinkedList::insertAtPos(Node* n, int pos) //inserts node at specified position in list                                                                                                                 
{
   Node* before = NULL;
   Node* after = head;
   if(pos <= getNumNode() && pos > 0) //if position is in list parameters and the list is not empty                                                                                                         
   {
      if(pos == 1) //if the node should be placed at the beginning of the list                                                                                                                              
         head = n; //insert node at beginning
      else
      {
         for(int k=1; k<pos; k++) //loop to arrive at the position requested                                                                                                                                
         {
            before = after;
            after = after->getNext();
         }
         before->setNext(n); //insert node                                                                                                                                                                  
      }
      n->setNext(after);
      after = NULL;
   }
}

void LinkedList::bubbleSort() //sorts the list based on the bubble sort algorithm                                                                                                                           
{
   bool sorted = false;

   if(!isEmpty()) //checks if there are nodes in the list                                                                                                                                                   
   {
      for(int k=0; k<getNumNode()-1 && !sorted; k++)
      {
         Node* curr = head; //starts at beginning of the list                                                                                                                                               
         int currPos = 1;
         Node* nextNode = head->getNext(); //compares top node with second node                                                                                                                             
         int nextPos = 2;
         sorted = true; //if sorted is true, that means the list is sorted and the loop will not continue checking                                                                                          
         for(int j=0; j < getNumNode()-1-k; j++)
         {
            if(curr->getStudent().getLastName().compare(nextNode->getStudent().getLastName()) < 0) //if the bottom student is higher in the alphabet
            {
               swap(curr, nextNode, currPos, nextPos); //swaps the two nodes                                                                                                                                
               sorted = false;
            }
            curr = curr->getNext(); //goes to next node                                                                                                                                                     
            currPos++;
            nextNode = nextNode->getNext();
            nextPos++;
         }
      }
   }
}

void LinkedList::selectionSort() //sorts the list based on the selection sort algorithm                                                                                                                     
{
   if(!isEmpty()) //checks if there are nodes in the list                                                                                                                                                   
   {
      for(int k=getNumNode()-1; k>=0; k--)
      {
         Node* curr = head;
         Node* largest = curr; //student with name farthest in the alphabet. Default start at head                                                                                                          
         int currPos = 1;
         int largestPos = currPos; //position of the largest node is defaulted to the first node in the list                                                                                                
         for(int j=0; j<=k; j++)
         {
            if(curr->getStudent().getLastName().compare(largest->getStudent().getLastName()) > 0) //if the student is farther down in the alphabet than the largest                                         
            {
               largest = curr; //that student is the new largest                                                                                                                                            
               largestPos = currPos;
            }
            if(currPos <= k) //moves to net node only if currPos is less than or equal to k                                                                                                                 
            {
               curr = curr->getNext(); //go to the next node                                                                                                                                                
               currPos++;
            }
         }
         if((largestPos != currPos) && (currPos != 1)) //if the largest node is not the last node                                                                                                           
            swap(largest, curr, largestPos, currPos); //swaps the largest node with the last node                                                                                                           
      }
   }
}

void LinkedList::swap(Node*& f, Node*& l, int fPos, int lPos) //swaps two nodes' positions in the list                                                                                                      
{
   Node* fTemp = new Node(*f); //create new nodes that are identical to the ones being swapped                                                                                                              
   Node* lTemp = new Node(*l);

   deleteAtPos(fPos); //deletes first of the two nodes                                                                                                                                                      
   insertAtPos(lTemp, fPos); //places copied node in that position                                                                                                                                          
   deleteAtPos(lPos); //deletes second node                                                                                                                                                                 
   if(lPos > getNumNode()) //if one of the nodes was the last node in the list, append the node                                                                                                             
      append(fTemp);
   else
      insertAtPos(fTemp, lPos); //insert node at the position in the list                                                                                                                                   

   f = lTemp; //swap the pointers that were passed by reference                                                                                                                                             
   l = fTemp;
}


