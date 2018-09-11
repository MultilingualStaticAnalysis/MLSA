/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 21, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Insert Sort                                                                                                                                                                                                 
Takes an array and sorts it by the Insert Sort Method                                                                                                                                                       
*/

#include <iostream>
using namespace std;
void sort(int arr[], int length);
void moveDown(int arr[], int n, int replace);
void display(int arr[], int length);

int main()
{
   int a1[5] = {9, 23, 1, 77, 43};
   int a2[10] = {28, 7, 14, 73, 2, 52, 100, 32, 10, -5};
   int a3[7] = {67, 18, 25, 0, 704, 37, 8};

   cout << "\nOriginal arrays: " << endl;
   display(a1, 5);
   display(a2, 10);
   display(a3, 7);

   sort(a1, 5);
   sort(a2, 10);
   sort(a3, 7);

   cout << "\nSorted arrays: " << endl;
   display(a1, 5);
   display(a2, 10);
   display(a3, 7);

   return 0;
}

void sort(int arr[], int length) //sorts the array from smallest number to largest                                                                                                                          
{
   for(int k=0; k<length-1; k++)
   {
      int curr = arr[k+1]; //curr is the first element of the unsorted array                                                                                                                                
      for(int j=k; j>=0 && arr[j] > curr; j--) //goes through sorted array from bottom to top                                                                                                               
         moveDown(arr, j, curr);
   }
}

void moveDown(int arr[], int n, int replace) //moves one element in array down and replaces the old spot with the value of replace                                                                          
{
   arr[n+1] = arr[n];
   arr[n] = replace;
}

void display(int arr[], int length) //displays the elements int the array                                                                                                                                   
{
   cout << endl;
   for(int k=0; k<length; k++)
      cout << arr[k] << " ";
   cout << endl;
}