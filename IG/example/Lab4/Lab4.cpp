// Anne Marie Bogar                                                                                                                                                                                         
// April 12, 2016                                                                                                                                                                                           
// Lab 4                                                                                                                                                                                                    
// Priority Lock                                                                                                                                                                                            

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <queue>
#include <stdlib.h>
using namespace std;

struct ThreadParam
{
   int level;
};

class PriorityLock{
public:
   // call this to enter the critical section.                                                                                                                                                              
   // if no thread is in critical section, calling thread is allowed in;                                                                                                                                    
   //  otherwise, it will be put in waiting...                                                                                                                                                              
   void enter (int priority_level);

   // thread call this when it finishes its critical section.                                                                                                                                               
   // if there are more than one threads waiting, the one with highest priority                                                                                                                             
   //  is allowed in.                                                                                                                                                                                       
   void exit();

   PriorityLock();

private:
   // figure out this ...                                                                                                                                                                                   
   priority_queue<int> wait_list;
   pthread_mutex_t lock;
   pthread_cond_t popTop;
};

PriorityLock::PriorityLock()
{
   //initialize variables                                                                                                                                                                                   
   lock = PTHREAD_MUTEX_INITIALIZER;
   popTop = PTHREAD_COND_INITIALIZER;
}

void PriorityLock::enter (int priority_level)
{
   pthread_mutex_lock(&lock);
   wait_list.push(priority_level);
   while(wait_list.top() != priority_level){
      pthread_cond_wait(&popTop, &lock);
   }
   cout << "Length of priority queue: " << wait_list.size() << endl;
   pthread_mutex_unlock(&lock);
}

void PriorityLock::exit()
{
   pthread_mutex_lock(&lock);
   wait_list.pop();
   pthread_cond_broadcast(&popTop);
   pthread_mutex_unlock(&lock);
}

PriorityLock plock;

//main for testing PriorityLock                                                                                                                                                                             
void * ThreadRoutine (void * param)
{
   ThreadParam * p = (ThreadParam *) param;
   int priority_level = p->level;

   cout <<"Thread "<< priority_level << " calling enter \n";
   plock.enter (priority_level);

   cout <<"Thread "<< priority_level << " in critical section \n";

   plock.exit();
   cout << "Thread " << priority_level << " is done\n";
}

int main(int argc, char * argv[])
{
   pthread_t * threads;
   ThreadParam * priorityParams;

   int thread_num;
   int status, i, j;

   do {
      cout <<"How many threads to create:";
      cin >> thread_num;
   } while (thread_num<=1);

   threads = new pthread_t[thread_num]; //dynamically allocate the thread handler ...                                                                                                                       

   priorityParams = new ThreadParam[thread_num];

   for (i=0; i<thread_num; i++){
      //Todo: prepare the argument to be passed in thread                                                                                                                                                   
      //                                                                                                                                                                                                    
      priorityParams[i].level = rand()%100;

      status = pthread_create (&threads[i], NULL, ThreadRoutine, (void *)&(priorityParams[i]));

      if (status!=0){
         printf ("oops, pthread_create returned error code %d\n", status);
         exit(-1);
      }
   }

   //EZ: Important that we wait for all threads to finish before ending the main thread ...                                                                                                                 
   for (i=0; i<thread_num; i++){
      pthread_join (threads[i],NULL);
   }
}

