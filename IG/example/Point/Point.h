/* The Point class Header (Point.h) */
#ifndef POINT_H
#define POINT_H
 
// Point class declaration
class Point {
private:
   // private data members (variables)
   int x;
   int y;
 
public:
   // Declare member function prototypes
   Point(int x = 0, int y = 0);  // Constructor with default values
   int getX() const;
   void setX(int x);
   int getY() const;
   void setY(int y);
   void setXY(int x, int y);
   double getMagnitude() const;
   double getArgument() const;
   void print() const;
};
 
#endif