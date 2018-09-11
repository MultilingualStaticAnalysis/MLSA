/* Implementation for the Time Class (Time.cpp) */
#include <iostream>
#include <iomanip>
#include "Time.h"    // include header of Time class
using namespace std;
 
// Constructor with default values. No input validation
Time::Time(int h, int m, int s) {
   hour = h;
   minute = m;
   second = s;
}
 
// public getter for private data member hour
int Time::getHour() const {
   return hour;
}
 
// public setter for private data member hour. No input validation
void Time::setHour(int h) {
   hour = h;
}
 
// public getter for private data member minute
int Time::getMinute() const {
   return minute;
}
 
// public setter for private data member minute. No input validation
void Time::setMinute(int m) {
   minute = m;
}
 
// public getter for private data member second
int Time::getSecond() const {
   return second;
}
 
// public setter for private data member second. No input validation
void Time::setSecond(int s) {
   second = s;
}
 
// Set hour, minute and second. No input validation
void Time::setTime(int h, int m, int s) {
   setHour(h);
   setMinute(m);
   setSecond(s);
}
 
// Print this Time instance in the format of "hh:mm:ss", zero filled
void Time::print() const {
   cout << setfill('0');    // zero-filled, need <iomanip>, sticky
   cout << setw(2) << hour  // set width to 2 spaces, need <iomanip>, non-sticky
        << ":" << setw(2) << minute
        << ":" << setw(2) << second << endl;
}
 
// Increase this instance by one second
void Time::nextSecond() {
   ++second;
   if (second >= 60) {
      setSecond(0);
      setMinute(++minute);
   }
   if (minute >= 60) {
      setMinute(0);
      setHour(++hour);
   }
   if (hour >= 24) {
      setHour(0);
   }
}