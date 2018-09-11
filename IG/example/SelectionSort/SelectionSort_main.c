/* selectionMain.c -- Read an integer array, print it, then sort it and
 * print it. Use the selection sort method.
 * Use library cis71.
 */
#include "SelectionSort_intArray.h"

#define NMAX 10

int main(void) {
  int x[NMAX];
  int hmny;
  int who;
  int where;

  hmny = getIntArray(x, NMAX, 0);
  if (hmny==0)
    printf("This is the empty array!\n");
  else{
    printf("The array was: \n");
    printIntArray(x,hmny);
    selectionSort(x,hmny);
    printf("The sorted array is: \n");
    printIntArray(x,hmny);
  }
}
