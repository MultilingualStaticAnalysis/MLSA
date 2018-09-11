/* Test object pointer, reference and array (TestTimeObject.cpp) */
#include <iostream>
#include "Time.h"
using namespace std;
 
int main() {
   // Ordinary object
   Time t1(1, 2, 3);
   t1.print();  // 01:02:03
 
   // Object pointer
   Time* ptrT1 = &t1;
   (*ptrT1).print(); // 01:02:03
   ptrT1->print();   // 01:02:03
      // anObjectPtr->member is the same as (*anObjectPtr).member
 
   // Object reference
   Time& refT1 = t1; // refT1 is an alias to t1
   refT1.print();    // 01:02:03
 
   // Dynamic allocation
   Time* ptrT2 = new Time(4, 5, 6); // allocate dynamically
   ptrT2->print(); // 04:05:06
   delete ptrT2;   // deallocate
 
   // Object Array
   Time tArray1[2];    // tArray1 is an array of Time with 2 elements
                       // Use default constructor for all elements
   tArray1[0].print();  // 00:00:00
   tArray1[1].print();  // 00:00:00
 
   //Time tArray2[2] = {Time(7, 8, 9), Time(10)}; // Invoke constructor
   //tArray2[0].print();  // 07:08:09
   //tArray2[1].print();  // 10:00:00
 
   Time* ptrTArray3 = new Time[2]; // ptrTArray3 is a pointer to Time
            // Dynamically allocate an array of Time with 2 elements via new[]
   ptrTArray3[0].print();  // 00:00:00
   ptrTArray3[1].print();  // 00:00:00
   delete[] ptrTArray3;    // Deallocate dynamic array via delete[]
 
   // C++11 syntax, compile with -std=c++0x
   //Time* ptrTArray4 = new Time[2] {Time(11, 12, 13), Time(14)}; // Invoke constructor
   //ptrTArray4->print();        // 11:12:13
   //(ptrTArray4 + 1)->print();  // 14:00:00
   //delete[] ptrTArray4;
}
