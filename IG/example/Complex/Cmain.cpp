/* Test Driver for the Complex class (TestComplex.cpp) */
#include <iostream>
#include <iomanip>
#include "Complex.h"
using namespace std;
 
int main() {
   Complex c1, c2(4, 5);
   c1.print();  // (0,0)
   c2.print();  // (4,5)
 
   c1.setValue(6, 7);
   c1.print();  // (6,7)
 
   c1.setReal(0);
   c1.setImag(8);
   c1.print();  // (0,8)
 
   cout << boolalpha;  // print true/false instead of 0/1
   cout << "Is real? " << c1.isReal() << endl;           // false
   cout << "Is Imaginary? " << c1.isImaginary() << endl; // true
 
   c1.addInto(c2).addInto(1, 1).print();  // (5,14)
   c1.print();  // (5,14)
 
   c1.addReturnNew(c2).print();   // (9,19)
   c1.print();  // (5,14) - no change in c1
   c1.addReturnNew(1, 1).print(); // (6,15)
   c1.print();  // (5,14) - no change in c1
}