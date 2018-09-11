// Anne Marie Bogar                                                                                                                                                                                         
// September 24, 2013                                                                                                                                                                                       
// Homework 5 problem #1                                                                                                                                                                                    
// Write a program that reads in two positive integers that have possibly large number of digits (in a character array) and then outputs the sum of the two digits using an integer dynamic array           

#include <iostream>
#include <cstdlib>
using namespace std;
void get_numbers(char a[], int& size);
// Precondition: a is a char array with a size of 100 but no values yet. size has a value of 0                                                                                                              
//Postcondition: a contains the numbers that the user entered. size has the value of the number of variables used in array a.                                                                               
void convert(char a[], int p[], int size);
//Precondition: array a contains an array of number characters. p is a dynamic array with no values yet. size has the value of the number of variables used in array a and the size of dynamic array p      
// Postcondition: p contains all the values of a, but in reverse order                                                                                                                                      
void add(int a[], int b[], int c[], int size_a, int size_b);
//Precondition: a and b are dynamic arrays that contain a list of int variables. c is a dynamic array with no values yet and is the same size as the largest of the two other dymanic arrays. size_a has th\
e value of the size of a, and size_b has the value of the size of b.                                                                                                                                        
//Postcondition: c contains a list of integers that are the sum of a and b                                                                                                                                  
void output(int c[], int size);
//Precondition: dynamic array c contains a list of integers                                                                                                                                                 
//Postcondition: the contents of c are displayed on the screen, but in reverse order                                                                                                                        
const int LIMIT = 100;

int main()
{
   char arrayA[LIMIT], arrayB[LIMIT], choice;
   do
   {
      int *a, *b, *c, size_a = 0, size_b = 0, size_c = 0;

      get_numbers(arrayA, size_a); // fills arrayA with a list of numbers                                                                                                                                   
      get_numbers(arrayB, size_b);

      a = new int[size_a]; // makes a dynamic array called a                                                                                                                                                
      b = new int[size_b];
      if(size_a > size_b)
      {
         c = new int[size_a];
         size_c = size_a;
      }
      else
      {
         c = new int[size_b];
         size_c = size_b;
      }

      convert(arrayA, a, size_a); // copies arrayA's values to dynamic array a in reverse order                                                                                                             
      convert(arrayB, b, size_b);
      add(a, b, c, size_a, size_b); // adds the two values from a and b, and puts the new value into c                                                                                                      
      output(c, size_c); // displays values in c in reverse order (the sum of arrayA and arrayB)                                                                                                            

      delete []a; // deletes the dynamic arrays                                                                                                                                                             
      delete []b;
      delete []c;
      cout << "Would you like to do more addition? Enter y or Y to continue, and any other character to quit: ";
      cin >> choice;
   } while(choice == 'y' || choice == 'Y');
   return 0;
}

void get_numbers(char a[], int& size)
{
   char character;
   int x = 0;
   cout << "Enter a number (cannot be more than " << LIMIT << " digits). Type a period (.) after the number when you are finished entering: ";
   cin >> character;
   while(x <= LIMIT)
   {
      if(character == '.') // stops function if a period is entered                                                                                                                                         
         break;
      if(x == LIMIT)
      {
         cout << "The integer entered exceeds the limit.The program has experienced integer overflow and will quit now.\n";
         exit(1);
      }
      a[x] = character; // assigns the entered value into an array variable                                                                                                                                 
      cin >> character;
      size++; // the size increases as numbers are added                                                                                                                                                    
      x++;
   }
}

void convert(char a[], int p[], int size)
{
   char character;
   int x = 0;
   for(int k = size-1; k >= 0; k--)
   {
      character = a[k];
      p[x] = int(character) - int('0');
      x++;
   }
}

void add(int a[], int b[], int c[], int size_a, int size_b)
{
   int num, carry_over = 0;
   if(size_a > size_b)
   {
      for(int k = 0; k < size_a-1; k++)
      {
         if(k < size_b)
            num = a[k] + b[k] + carry_over;
         else
            num = a[k] + carry_over;
         carry_over = num/10; // carry_over holds the number in the tens place                                                                                                                              
         num = num % 10; // num holds the number in the ones place                                                                                                                                          
         c[k] = num;
      }
      c[size_a-1] = a[size_a-1] + carry_over; // the last variable in the array holds the entire number (ones and tens place). Allows for the sum to be more than the LIMIT.                                
   }
   else
   {
      for(int k = 0; k < size_b-1; k++)
      {
         if(k < size_a)
            num = a[k] + b[k] + carry_over;
         else
            num = b[k] + carry_over;
        carry_over = num/10;
         num = num % 10;
         c[k] = num;
      }
      if (size_a == size_b) // if a and b are the same size, the a variable is added into the equation                                                                                                      
         c[size_b-1] = b[size_b-1] + a[size_b-1] + carry_over;
      else // if b is bigger, the a variable is not added in                                                                                                                                                
         c[size_b-1] = b[size_b-1] + carry_over;
   }
}

void output(int c[], int size)
{
   cout << "The sum of those two numbers is: ";
   for(int k = size-1; k >= 0; k--) // outputs the values in c in reverse order                                                                                                                             
      cout << c[k];
   cout << endl;
}
