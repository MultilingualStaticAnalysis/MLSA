//Anne Marie Bogar                                                                                                                                                                                          
//October 14, 2014                                                                                                                                                                                          
//Data Structures                                                                                                                                                                                           
//Array Driver File                                                                                                                                                                                         
//Lab 3B                                                                                                                                                                                                    
//Initiates Arrays for integers, doubles, characters, and strings and compares them to similar Arrays                                                                                                       

#include "Array.h"

template <typename T>
void instantiateArray(Array<T>& a);//creates array and compares it to other arrays                                                                                                                          

int main()
{
   // Instantiate an Array of doubles                                                                                                                                                                       
   cout << "\nTESTING DOUBLES:\n";
   Array<double> dbl;
   dbl.setDELIM(-999); //sets the DELIM based on Array type for input purposes                                                                                                                              
   instantiateArray(dbl);

   // Instantiate an Array of integers                                                                                                                                                                      
   cout << "\nTESTING INTEGERS:\n";
   Array<int> i;
   i.setDELIM(-999);
   instantiateArray(i);

   // Instantiate an Array of characters                                                                                                                                                                    
   cout << "\nTESTING CHARS:\n";
   Array<char> c;
   c.setDELIM('*');
   instantiateArray(c);

   // Instantiate an Array of strings                                                                                                                                                                       
   cout << "\nTESTING STRINGS:\n";
   Array<string> s;
   s.setDELIM("-999");
   instantiateArray(s);

   return 0;
}

template <typename T>
void instantiateArray(Array<T>& a)
{
   static T dVal; //is initialized with a default T value                                                                                                                                                   

   cout << "\nEnter any amount of elements or " << a.getDELIM() << " to end input: ";
   cin >> a;
   cout << a.getSize() << " elements were entered\n" << a << endl;

   cout << "Initializing second array from the array originally created" << endl;
   Array<T> b(a); //initializing a new array as a copy of the original                                                                                                                                      
   cout << "the new array has " << b.getSize() << " elements\n" << b << endl;

   cout << "The original array and second array are ";
   if(a==b) //checks to see if a and b are the same arrays                                                                                                                                                  
      cout << "equal" << endl;
   else
      cout << "not equal" << endl;

   cout << "Creating a third array from user input...";
   Array<T> c; //creates default array c of the same type as array a                                                                                                                                        
   c.setDELIM(a.getDELIM()); //sets the DELIM of c to the same as a                                                                                                                                         
   cout << "\nEnter any amount of elements or " << c.getDELIM() << " to end input: ";
   cin >> c;
   cout << c.getSize() << " elements were entered\n" << c << endl;

   cout << "The original array and third array are ";
   if(a==c) //checks if a and c are the same array                                                                                                                                                          
      cout << "equal" << endl;
   else
      cout << "not equal" << endl;

   cout << "Copying the elements from the third array to the original one" << endl;
   a = c; //copies the array of c to a                                                                                                                                                                      
   cout << "The original array now has " << a.getSize() << " elements:\n" << a << endl;

   //uses overloaded subscript operator to print out value at a[5]                                                                                                                                          
   cout << "In the original array, the element at subscript 5 is " << a[5] << endl;

   // use overloaded subscript operator to create lvalue                                                                                                                                                    
   cout << "\n\nAssigning " << dVal << " to the subscript [5] position" << endl;
   a[ 5 ] = dVal; //a[5] is assigned dVal's value                                                                                                                                                           
   cout << "After assignment, the original array:\n" << a << endl;
}
