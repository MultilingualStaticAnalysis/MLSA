/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
October 31, 2014                                                                                                                                                                                            
Data Structures                                                                                                                                                                                             
Recursive Search Lab                                                                                                                                                                                        
The program searches through a list of descending numbers to find the one the user requests                                                                                                                 
*/

#include <iostream>
using namespace std;
bool binarySearch(int a[], int begin, int end, int element, int& position); //uses recursion to search for a number in an array                                                                             
                                                                            //that goes from lowest number to highest number                                                                                
int main()
{
   int pos;
   int a[11] = {3, 4, 7, 10, 13, 15, 21, 23, 44, 56, 60};

   if(binarySearch(a, 0, 10, 44, pos))
      cout << "44 is at position " << pos << endl;
   else
      cout << "44 is not in the array" << endl;
   if(binarySearch(a, 0, 10, 10, pos))
      cout << "10 is at position " << pos << endl;
   else
      cout << "10 is not in the array" << endl;
   if(binarySearch(a, 0, 10, 12, pos))
      cout << "12 is at position " << pos << endl;
   else
      cout << "12 is not in the array" << endl;

   return 0;
}

bool binarySearch(int a[], int begin, int end, int element, int& position)
{
   bool found = false;
   int mid = 0;
   if(begin <= end && !found)
      mid = (begin + end)/2; //mid is the middle of the array being looked at                                                                                                                               
   if(begin > end && !found){} //if the array has been searched through and the element is not there, just return false                                                                                     
   else
   {
      if(element == a[mid]) //element is found!                                                                                                                                                             
      {
         found = true;
         position = mid+1;
      }
      else
      {
         if(element < a[mid])
         {
            found = binarySearch(a, begin, mid-1, element, position); //call search function but end at position before mid                                                                                 
         }
         else
         {
            found = binarySearch(a, mid+1, end, element, position); //call search function but begin at position after mid                                                                                  
         }
      }
   }
   return found;
}

