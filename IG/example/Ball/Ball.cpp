/* Implementation for the Ball Class (Ball.cpp) */
#include <iostream>
#include <iomanip>
#include "Ball.h"    // include header of Ball class
using namespace std;
 
// Constructor with default values. No input validation
Ball::Ball(double x, double y, double xSpeed, double ySpeed)
      : x(x), y(y), xSpeed(xSpeed), ySpeed(ySpeed) { }  // use member initializer list
 
// public getters/setters for private data members
double Ball::getX() const {
   return x;
}
double Ball::getY() const {
   return y;
}
void Ball::setX(double x) {
   this->x = x;
}
void Ball::setY(double y) {
   this->y = y;
}
double Ball::getXSpeed() const {
   return xSpeed;
}
double Ball::getYSpeed() const {
   return ySpeed;
}
void Ball::setXSpeed(double xSpeed) {
   this->xSpeed = xSpeed;
}
void Ball::setYSpeed(double ySpeed) {
   this->ySpeed = ySpeed;
}
 
// Set position (x,y)
void Ball::setXY(double x, double y) {
   setX(x);
   setY(y);
}
 
// Set speed (xSpeed,ySpeed)
void Ball::setXYSpeed(double xSpeed, double ySpeed) {
   setXSpeed(xSpeed);
   setYSpeed(ySpeed);
}
 
// Move the ball by increases x and y by xSpeed and ySpeed
void Ball::move() {
   setX(x + xSpeed); // increment x by xSpeed
   setY(y + ySpeed); // increment y by ySpeed
}
 
// Print a description about this Ball instance
void Ball::print() const {
   cout << fixed << setprecision(2);
   cout << "Ball @ (" << x << ',' << y << ") with speed ("
        << xSpeed << ',' << ySpeed << ')' << endl;
}