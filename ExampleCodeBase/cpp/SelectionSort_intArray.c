/* intArray.c -- File with some library functions
 */
#include "SelectionSort_intArray.h"

void printIntArray(int a[], int n)
     /* n is the number of elements in the array a.
      * These values are printed out, five per line. */
{
  int i;

  for (i=0; i<n; ){
    printf("\t%d ", a[i++]);
    if (i%5==0)
      printf("\n");
  }
  printf("\n");
}

int getIntArray(int a[], int nmax, int sentinel)
     /* It reads up to nmax integers and stores then in a; sentinel 
      * terminates input. */
{
  int n = 0;
  int temp;

  do {
    printf("Enter integer [%d to terminate] : ", sentinel);
    scanf("%d", &temp);
    if (temp==sentinel) break;
    if (n==nmax)
      printf("array is full\n");
    else 
      a[n++] = temp;
  }while (1);
  return n;
}


void selectionSort(int a[], int n)
/* It sorts in non-decreasing order the first N positions of A. It uses 
 * the selection sort method.
 */
{
  int lcv;
  int rh;      /*Elements in interval rh..n-1 are in their final position*/
  int where;   /*Position where we have current maximum*/
  int temp;    /*Used for swapping*/
  
  for(rh=n-1;rh>0;rh--){
    /*Find position of largest element in range 0..rh*/
    where = 0;
    for (lcv=1;lcv<=rh;lcv++)
      if (a[lcv]>a[where])
	where = lcv;
    temp = a[where];
    a[where] = a[rh];
    a[rh] = temp;
  }
}
