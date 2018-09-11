/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
March 11, 2016                                                                                                                                                                                              
Lab 3                                                                                                                                                                                                       
                                                                                                                                                                                                            
1. The program still worked when I made threads and threadsParams local variables instead of dynamically allocated.                                                                                         
   Child threads have access to variables in the parent thread as long as those variables are declared in                                                                                                   
   a global scope, menaing that they are not defined in a loop, if statement, or function.                                                                                                                  
                                                                                                                                                                                                            
2. printf("Search function address = %p\n", Search);                                                                                                                                                        
   cout << "the address of the local variable 'count' is " << &count << endl;                                                                                                                               
   cout << "the address of the local variable 'pos' is " << &pos << endl;                                                                                                                                   
   cout << "the address of global variable 'threadsParams' is " << &threadParams << endl;                                                                                                                   
                                                                                                                                                                                                            
3. You could use std::future to find out the status of each thread. Use the wait_for function to set time intervals                                                                                         
   for checking the status of threads.                                                                                                                                                                      
*/

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

//global variables are shared by all threads                                                                                                                                                                

//Define the struct to be returned (by pointer) by each search thread                                                                                                                                       
struct ThreadReturn{
   int count;
   int pos;
};
//Define the struct to be passed (by pointer) to each search thread                                                                                                                                         
struct ThreadParam {
   int * array;
   int value;
   int startIndex;
   int endIndex;
};

//To pass the function to pthread_create, we need to match the                                                                                                                                              
//argument expected by pthread_create: take generic pointer as parameter,                                                                                                                                   
//and return a generic pointer                                                                                                                                                                              
void * Search  (void * arg)
{
   ThreadParam * param = (ThreadParam *) arg;
   int * array = param->array;
   int start = param->startIndex;
   int end = param->endIndex;
   int value = param->value;
   int count = 0;
   int pos = 0;

   cout <<"Search array["<<start<<"..."<<end<<"] for value "<<
      value<<endl;
   //search through designated area for the target number and first position                                                                                                                                
   for(int k=start; k<=end; k++)
   {
      if(array[k] == value)
      {
         count++;
         if(count == 1)
            pos = k;
      }
   }
   ThreadReturn * r = new ThreadReturn;
   r->count = count;
   r->pos = pos;
   return (void *)r;
}


int main(int argc, char * argv[])
{
   pthread_t * threads;
   ThreadParam * threadsParams;

   const int MAX_SIZE=10000;
   int BigArray[MAX_SIZE];

   int thread_num;
   int status, i;
   int pos, value;

   //Todo: prepare the array to be sorted for                                                                                                                                                               
   // You can fill the array with random numbers (taking values in the range of 1...100)                                                                                                                    

   for(int k=0; k<MAX_SIZE; k++)
   {
      BigArray[k] = rand()%200+1;
   }

   cout <<"What values to search:";
   cin >> value;

   do {
      cout <<"How many threads to create:";
      cin >> thread_num;
   } while (thread_num<=1);

   //threads = new pthread_t[thread_num]; //dynamically allocate the thread handler ...                                                                                                                     
   pthread_t threads[thread_num];

   //threadsParams = new ThreadParam[thread_num];                                                                                                                                                           
   ThreadParam threadsParams[thread_num];

   int increase = (MAX_SIZE / thread_num) - 1;
   int start = 0;
   int end = increase;

   for (i=0; i<thread_num; i++){
      //Todo: prepare the argument to be passed to i-th Search thread                                                                                                                                       
      //                                                                                                                                                                                                    
      threadsParams[i].value = value;
      threadsParams[i].startIndex = start;
      threadsParams[i].endIndex = end;
      threadsParams[i].array = BigArray;

      status = pthread_create (&threads[i], NULL, Search, (void *)&(threadsParams[i]));

      if (status!=0){
         printf ("oops, pthread_create returned error code %d\n", status);
         exit(-1);

      }
      start += increase;
      end += increase;
      //printf("Search function address = %p\n", Search);                                                                                                                                                   

   }

   void * ret;
   //EZ: Important that we wait for all threads to finish before ending the main thread ...                                                                                                                 
   for (i=0; i<thread_num; i++){
      pthread_join (threads[i],(void **)&ret);
      cout << "Thread " << i << " returns having counted "
           << ((ThreadReturn *)ret)->count << " instances of the number "
           << value << " with the first instance being at position "
           << ((ThreadReturn *)ret)->pos << endl;
   }
}
