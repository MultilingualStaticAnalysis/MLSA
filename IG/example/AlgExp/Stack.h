/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
December 9, 2014                                                                                                                                                                                            
Data Structures                                                                                                                                                                                             
Stack Template Header File                                                                                                                                                                                  
The Stack class is a vactor of elements of type T. The elements can be pushed on, popped off, topped off (taken off the stack, but the value returned),                                                     
and peeked at. One can also access the size of the stack and see if the stack is empty or not                                                                                                               
*/

#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <typeinfo>
#include <string>
using namespace std;

template <class T>
class Stack
{
private:
   vector<T> stack;
public:
   Stack() {} //default constructor                                                                                                                                                                         
   Stack(vector<T> v); //constructor                                                                                                                                                                        
   void pop(); //pops top element off stack and discards                                                                                                                                                    
   T top(); //pops top element off stack and returns value                                                                                                                                                  
   void push(T t); //puts element on top of stack                                                                                                                                                           
   bool isEmpty(); //checks to see if the stack is empty                                                                                                                                                    
   T peek(); //returns value of top element without popping it off                                                                                                                                          
   int size(); //returns size of stack                                                                                                                                                                      
};

template <class T>
Stack<T>::Stack(vector<T> v) //constructor                                                                                                                                                                  
{
   for(int k=0; k<v.size(); k++)
      stack.push_back(v[k]);
}

template <class T>
void Stack<T>::pop() //pops top element off stack and discards                                                                                                                                              
{
   if(!isEmpty())
      stack.pop_back();
}

template <class T>
T Stack<T>::top() //pops top element off stack and returns value                                                                                                                                            
{
   T t;
   if(!isEmpty())
   {
      t = stack.back(); //access top element                                                                                                                                                                
      stack.pop_back(); //descard top element                                                                                                                                                               
   }
}

template <class T>
void Stack<T>::push(T t) //puts element onto top of stack                                                                                                                                                   
{
   stack.push_back(t);
}

template <class T>
bool Stack<T>::isEmpty() //checks if the stack is empty                                                                                                                                                     
{
   bool empty = true;
   if(stack.size() > 0)
      empty = false;
   return empty;
}

template <class T>
T Stack<T>::peek() //access the top element of the stack without popping it off                                                                                                                             
{
   T t;
   if(!isEmpty())
      t = stack.back(); //access element                                                                                                                                                                    
   return t;
}

template <class T>
int Stack<T>::size() //returns the size of the stack                                                                                                                                                        
{
   return stack.size(); //size of vector                                                                                                                                                                    
}

#endif
