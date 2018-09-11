//Anne Marie Bogar                                                                                                                                                                                          
//October 3, 2014                                                                                                                                                                                           
//Data Structures                                                                                                                                                                                           
//Array Source File                                                                                                                                                                                         
//The Array class allows for an array to function as any other type, with an assignment operator, comparison operators, and iostream operators. The Array class uses dynamic arrays so that each Array inst\
ance can be of different sizes.                                                                                                                                                                             

#include "Array.h" // Array class definition                                                                                                                                                                

//default constructor for class Array. Creates a dynamic array with a default size and initializes all elements to 0.                                                                                       
Array::Array()
{
   size = 0;
   dArr = new int[DEFAULT_SIZE];

   for ( int i = 0; i < DEFAULT_SIZE; i++ )
      dArr[i] = 0;
}

Array::Array(int s)
{
   size = s;
   dArr = new int[size];

   for ( int i = 0; i < size; i++ )
      dArr[i] = 0;
}

// copy constructor for class Array which receives as                                                                                                                                                       
// and argument an object of class Array and uses it to                                                                                                                                                     
// initialize the data members of the object the constructor                                                                                                                                                
// instantiated.                                                                                                                                                                                            
//                                                                                                                                                                                                          
// Note that the argument passed must be received a reference                                                                                                                                               
// to prevent infinite recursion                                                                                                                                                                            
Array::Array( const Array &arrayToCopy ) : size( arrayToCopy.size )
{

   // Copy every element of the passed array to the                                                                                                                                                         
   // data member of the array object the function                                                                                                                                                          
   // was called on.                                                                                                                                                                                        
   dArr = new int[size];
   for ( int i = 0; i < size; i++ )
      dArr[i] = arrayToCopy.dArr[i]; // copy into object                                                                                                                                                    
}

Array::~Array()//destructor for class Array                                                                                                                                                                 
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
const Array &Array::operator=( const Array &right )
{
   size = right.size;

   // Check to see if the arrays are the same object                                                                                                                                                        
   if ( &right != this ) // this avoids self-assignment                                                                                                                                                     
   {
      if(dArr == NULL)
      {
         cerr << "Error! Dynamic memory not allocated! Abort program!" << endl << endl;
         exit(1);
      }
      else
      {
         delete[] dArr;//delete existing dynamic array so that the new dynamic array can have the right size                                                                                                
         dArr = new int[size];
         for ( int i = 0; i < size; i++ )
            dArr[i] = right.dArr[i]; // copy array into object                                                                                                                                              
      }
   }

   return *this; // enables x = y = z                                                                                                                                                                       
}

bool Array::operator==( const Array &right ) const
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

// overloaded subscript operator for non-const Arrays                                                                                                                                                       
//                                                                                                                                                                                                          
// Note reference return creates a modifiable lvalue and therefore                                                                                                                                          
// allows this member function to be invoked on array object to                                                                                                                                             
// that are left hand operand as arrObj[i] = 5                                                                                                                                                              
//                                                                                                                                                                                                          
// For this reason this member function cannot be invoked on                                                                                                                                                
// const objects.                                                                                                                                                                                           
int &Array::operator[]( int subscript )
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
int Array::operator[]( int subscript ) const
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

// overloaded input operator for class Array;                                                                                                                                                               
// inputs values for entire Array                                                                                                                                                                           
istream &operator>>( istream &input, Array &a )
{
   vector<int> v;
   int c;

   input >> c;
   while(c != Array::DELIM)//takes in all the integers entered up until DELIM is entered                                                                                                                    
   {
      v.push_back(c);
      input >> c;
   }

   Array b(v.size());
   if(b.dArr == NULL)
   {
      cerr << "Error! Dynamic memory not allocated! Abort program!" << endl << endl;
      exit(1);
   }

   for(int k=0; k<b.size; k++)
      b.dArr[k] = v[k];

   a = b;
   return (input); // enables cin >> x >> y;                                                                                                                                                                
}

ostream &operator<<( ostream &output, const Array &a )// output all the elements in the array as  four numbers per row.                                                                                     
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

// accessor function for data member size                                                                                                                                                                   
int Array::getSize() const
{
   return size; // number of elements in Array                                                                                                                                                              
}
