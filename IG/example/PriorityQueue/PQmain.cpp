// Anne Marie Bogar                                                                                                                                                                                         
// December 5, 2013                                                                                                                                                                                         
// Homework 10                                                                                                                                                                                              
// Main File                                                                                                                                                                                                

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "Queue.h"
#include "PriorityQueue.h"
using namespace std;
using namespace queuesavitch;
int main()
{
   Queue q;
   q.add(3);
   q.add(9);
   q.add(72);
   q.add(825);
   q.add(0);
   q.add(52);

   cout << "A queue filled with random numbers: \n";
   cout << q.remove() << endl;
   cout << q.remove() << endl;
   cout << q.remove() << endl;
   cout << q.remove() << endl;
   cout << q.remove() << endl;
   cout << q.remove() << endl;

   PriorityQueue pq;
   pq.add(3);
   pq.add(9);
   pq.add(72);
   pq.add(825);
   pq.add(0);
   pq.add(52);

   cout << endl << "A priority queue filled with the same numbers: \n";
   cout << pq.remove() << endl;
   cout << pq.remove() << endl;
   cout << pq.remove() << endl;
   cout << pq.remove() << endl;
   cout << pq.remove() << endl;
   cout << pq.remove() << endl;

   return 0;
}
