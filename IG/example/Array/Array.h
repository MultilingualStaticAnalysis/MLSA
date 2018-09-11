//Anne Marie Bogar                                                                                                                                                                                          
//October 3, 2014                                                                                                                                                                                           
//Data Structures                                                                                                                                                                                           
//Array Header File                                                                                                                                                                                         
//The Array class allows for an array to function as any other data type, with an assignment operator, comparison operators, and iostream operators. The Array class uses dynamic arrays so that each Array\
 instance can be of different sizes. Similar to the vector class, the array class can be initialized to hold a variety of data types (e.g. int, char, double, string)                                       

#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <typeinfo>
#include <string>
using namespace std;
#ifndef ARRAY_H
#define ARRAY_H

template <class T>
class Array {

   // global functions - the ostream and istream operators are overloaded inside the class definition                                                                                                       
   friend ostream &operator<<( ostream &output, const Array<T> &a )
   {
      int i;

      cout << endl;

      // output private ptr-based array                                                                                                                                                                     
      for ( i = 0; i < a.size; i++ )
      {
         output << right << setw(10) << a.dArr[i];

         if ( (i + 1) % 4 == 0 ) // 4 numbers per row of output                                                                                                                                             
            output << endl;
      }

      if ( i % 4 != 0 ) // end last line of output                                                                                                                                                          
         output << endl;

      return output; // enables cout << x << y;                                                                                                                                                             
   }

   friend istream &operator>>( istream &input, Array<T> &a )
   {
      vector<T> v;
      T t;
      input >> t;

      while(t != a.DELIM)//takes in all the integers entered up until DELIM is entered                                                                                                                      
      {
         v.push_back(t); //adds the element entered to the vector                                                                                                                                           
         input >> t;
      }

      Array<T> b(v.size()); //initializes the array with the size of vector v                                                                                                                               
      if(b.dArr == NULL) //if b's dynamic array has no memory allocated                                                                                                                                     
      {
         cerr << "Error! Dynamic memory not allocated! Abort program!" << endl << endl;
         exit(1);
      }

      for(int k=0; k<b.size; k++)
         b.dArr[k] = v[k]; //assigning the values in the vector to the newly created dynamic array                                                                                                          

      a = b; //assign b to a                                                                                                                                                                                
      return (input); // enables cin >> x >> y;                                                                                                                                                             
   }


   // public data members and member functions                                                                                                                                                              
public:
   // Class Constructors                                                                                                                                                                                    
   //Array(); //default constructor                                                                                                                                                                         
   Array(int s = 10); // constructor takes an integer and creates a dynamic array of size s                                                                                                                 
   Array( const Array<T> & ); // copy constructor                                                                                                                                                           
   ~Array(); // destructor                                                                                                                                                                                  

   // Overloaded operator functions                                                                                                                                                                         
   const Array<T> &operator=( const Array<T> & ); // assignment operator                                                                                                                                    
   bool operator==( const Array<T> & ) const; // equality operator                                                                                                                                          

   // inequality operator; returns opposite of == operator                                                                                                                                                  
   bool operator!=( const Array<T> &right ) const;

   // subscript operator for non-const objects returns modifiable lvalue                                                                                                                                    
   T &operator[]( int );

   // subscript operator for const objects returns rvalue                              
   T operator[]( int ) const;

   // accessor functions                                                                                                                                                                                    
   int getSize() const; // returns the size of the array                                                                                                                                                    

   T getDELIM(); // returns the DELIM size                                                                                                                                                                  

   void setDELIM(T d);
// private data members and member functions                                                                                                                                                                
private:
   T DELIM; // flag to signal end of (user) input                                                                                                                                                           
   static const int DEFAULT_SIZE = 10; //when the default constructor is called, the dynamic array has a size of 10                                                                                         
   static T iVal; //default value                                                                                                                                                                           

   int size; // number of filled elements in the array                                                                                                                                                      
   T* dArr; //pointer used for dynamic array                                                                                                                                                                
};

template <class T>
T Array<T>::iVal; //allows all template functions to use iVal                                                                                                                                               

template <class T>
Array<T>::Array(int s)
{
   size = s;
   dArr = new T[size];
   DELIM = iVal; //DELIM has not been set, so it is given a default value for the moment                                                                                                                    

   for ( int i = 0; i < size; i++ )
      dArr[i] = iVal; //dArr is initialized with default values                 
}

// copy constructor for class Array which receives as                                                                                                                                                       
// and argument an object of class Array and uses it to                                                                                                                                                     
// initialize the data members of the object the constructor                                                                                                                                                
// instantiated.                                                                                                                                                                                            
//                                                                                                                                                                                                          
// Note that the argument passed must be received a reference                                                                                                                                               
// to prevent infinite recursion                                                                                                                                                                            
template <class T>
Array<T>::Array( const Array<T> &arrayToCopy ) : size( arrayToCopy.size )
{

   // Copy every element of the passed array to the                                                                                                                                                         
   // data member of the array object the function                                                                                                                                                          
   // was called on.                                                                                                                                                                                        
   DELIM = arrayToCopy.DELIM;
   dArr = new T[size];
   for ( int i = 0; i < size; i++ )
      dArr[i] = arrayToCopy.dArr[i]; // copy into object                                                                                                                                                    
}

template <class T>
Array<T>::~Array()//destructor for class Array                                                                                                                                                              
{
   if(dArr)
   {
      delete[] dArr;//deletes dynamically allocated memory of array when program ends                                                                                                                       
      dArr = NULL;
   }
}

// overloaded assignment operator that assigns the values                                                                                                                                                   
// of the data members of the array object passed to the                                                                                                                                                    
// data members of the object the function was invoked on.                                                                                                                                                  
//                                                                                                                                                                                                          
// Note that the const return avoids: ( a1 = a2 ) = a3                                                                                                                                                      
template <class T>
const Array<T> &Array<T>::operator=( const Array<T> &right )
{
   // Check to see if the arrays are the same object                                                                                                                                                        
   if ( &right != this ) // this avoids self-assignment                                                                                                                                                     
   {
      size = right.size;
      if(dArr != NULL) //checks of memory has been allocated for the dynamic array                                                                                                                          
      {
         delete[] dArr;//delete existing dynamic array so that the new dynamic array can have the right size                                                                                                
         //cerr << "Error! Dynamic memory not allocated! Abort program!" << endl << endl;                                                                                                                   
         //exit(1);                                                                                                                                                                                         
      }
         dArr = new T[size];
         for ( int i = 0; i < size; i++ )
            dArr[i] = right.dArr[i]; // copy array into object                                                                                                                                              
   }
   return *this; // enables x = y = z                                                                                                                                                                       
}

template <class T>
bool Array<T>::operator==( const Array<T> &right ) const
{
      bool equal = true;

      if ( size != right.size )
         equal = false; // arrays of different number of elements                                                                                                                                           
      else
         for ( int i = 0; i < size; i++ )
            if ( dArr[i] != right.dArr[i] )
            {
               equal = false; // Array contents are not equal, no need to check further                                                                                                                     
               break;
            }
      return( equal );
}

template <class T>
bool Array<T>::operator!=( const Array<T> &right ) const
{
   return ! ( *this == right ); // invokes Array::operator==                                                                                                                                                
}


// overloaded subscript operator for non-const Arrays                                                                                                                                                       
//                                                                                                                                                                                                          
// Note reference return creates a modifiable lvalue and therefore                                                                                                                                          
// allows this member function to be invoked on array object to                                                                                                                                             
// that are left hand operand as arrObj[i] = 5                                                                                                                                                              
//                                                                                                                                                                                                          
// For this reason this member function cannot be invoked on                                                                                                                                                
// const objects.                                                                                                                                                                                           
template <class T>
T &Array<T>::operator[]( int subscript )
{
   // check for subscript out-of-range error                                                                                                                                                                
   //                                                                                                                                                                                                       
   // this is an unrecoverable error so without exception handling,                                                                                                                                         
   // program can only log the error and exit.                                                                                                                                                              
   if ( subscript < 0 || (subscript >= size) )
   {
      cerr << "\nError: Subscript " << subscript
           << " out of range, exiting program" << endl;
      exit( 1 ); // terminate program; subscript out of range                                                                                                                                               
   }

   return dArr[subscript]; // reference return so returning address location not contents                                                                                                                   
}

// overloaded subscript operator for const Arrays. This function                                                                                                                                            
// can only be invoked as a right hand operand, Example:                                                                                                                                                    
// cout << arrObj[i]                                                                                                                                                                                        
//                                                                                                                                                                                                          
// const reference return creates an rvalue                                                                                                                                                                 
template <class T>
T Array<T>::operator[]( int subscript ) const
{
   // check for subscript out-of-range error                                                                                                                                                                
   if ( subscript < 0 || subscript >= size )
   {
      cerr << "\nError: Subscript " << subscript
           << " out of range, exiting program" << endl;
      exit( 1 ); // terminate program; subscript out of range                             
   }

   return dArr[subscript]; // returns copy of this element and not the address location                                                                                                                     
}

// accessor function for data member size                                                                                                                                                                   
template <class T>
int Array<T>::getSize() const
{
   return size; // number of elements in Array                                                                                                                                                              
}

template <class T>
T Array<T>::getDELIM() // returns the DELIM size                                                                                                                                                            
{
   return( DELIM );
}

template <class T>
void Array<T>::setDELIM(T d) //sets the DELIM value based on the data type of the array for input purposes                                                                                                  
{
   DELIM = d;
}

#endif

