/* Header for the Time class (Time.h) */
#ifndef TIME_H   // Include this "block" only if TIME_H is NOT defined
#define TIME_H   // Upon the first inclusion, define TIME_H so that
                 //  this header will not get included more than once
class Time {
private:  // private section
   // private data members
   int hour;     // 0 - 23
   int minute;   // 0 - 59
   int second;   // 0 - 59
 
public:   // public section
   // public member function prototypes
   Time(int h = 0, int m = 0, int s = 0); // Constructor with default values
   int getHour() const;   // public getter for private data member hour
   void setHour(int h);   // public setter for private data member hour
   int getMinute() const; // public getter for private data member minute
   void setMinute(int m); // public setter for private data member minute
   int getSecond() const; // public getter for private data member second
   void setSecond(int s); // public setter for private data member second
   void setTime(int h, int m, int s);   // set hour, minute and second
   void print() const; // Print a description of this instance in "hh:mm:ss"
   void nextSecond();  // Increase this instance by one second
};  // need to terminate the class declaration with a semicolon
 
#endif  // end of "#ifndef" block