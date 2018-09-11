/* Test Driver for the Time class (TestTime.cpp) */
#include <iostream>
#include "Time.h"    // include header of Time class
using namespace std;
 
int main() {
   Time t1(23, 59, 59);   // Test constructor
 
   // Test all public member functions
   t1.print();       // 23:59:59
   t1.setHour(12);
   t1.setMinute(30);
   t1.setSecond(15);
   t1.print();       // 12:30:15
   cout << "Hour is "   << t1.getHour()   << endl;
   cout << "Minute is " << t1.getMinute() << endl;
   cout << "Second is " << t1.getSecond() << endl;
 
   Time t2;     // Test constructor with default values for hour, minute and second
   t2.print();  // 00:00:00
   t2.setTime(1, 2, 3);
   t2.print();  // 01:02:03
 
   Time t3(12); // Use default values for minute and second
   t3.print();  // 12:00:00
 
   // Test nextSecond()
   Time t4(23, 59, 58);
   t4.print();
   t4.nextSecond();
   t4.print();
   t4.nextSecond();
   t4.print();
 
   // No input validation
   Time t5(25, 61, 99); // values out of range
   t5.print();  // 25:61:99
}