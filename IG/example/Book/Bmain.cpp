/* Test Driver for the Book class (TestBook.cpp) */
#include <iostream>
#include "Book.h"
using namespace std;
 
int main() {
   // Declare and construct an instance of Author
   Author peter("Peter Jones", "peter@somewhere.com", 'm');
   peter.print();  // Peter Jones (m) at peter@somewhere.com
 
   // Declare and construct an instance of Book
   Book cppDummy("C++ for Dummies", peter, 19.99);
   cppDummy.print();
      // 'C++ for Dummies' by Peter Jones (m) at peter@somewhere.com
 
   peter.setEmail("peter@xyz.com");
   peter.print();   // Peter Jones (m) at peter@xyz.com
   cppDummy.print();
      // 'C++ for Dummies' by Peter Jones (m) at peter@somewhere.com
 
   cppDummy.getAuthor().setEmail("peter@abc.com");
   cppDummy.print();
      // 'C++ for Dummies' by Peter Jones (m) at peter@somewhere.com
}