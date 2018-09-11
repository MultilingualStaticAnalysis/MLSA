/* hmw10main.c -- Outline of solution for homework 10, written using
 *                multiple source files.
 */

#include "HWK10_stringarray.h"

#define ARRAYSIZE 2000


int main(void){
  int n;
  linetype linearray[ARRAYSIZE];
  linetype who;
  int where;
  FILE *fdw;  /* FILE descriptor used for "who.dat" */
  FILE *fda;  /* File descriptor used for "answers.dat" */
  
  /* Read unsorted.dat into linearray and return number of lines read */
  n = getStringArray("unsorted.dat", linearray, ARRAYSIZE);
  if (n==0){
    printf("The unsorted.dat file is empty. Good bye.\n");
    exit(0);
  }
  /* Sort the first n lines of linearray */
  stringBubble(linearray,n);
  /* Save the sorted array to sorted.dat */
  writeStringArray("sorted.dat",linearray,n);
  /* Open for reading who.dat */
  if((fdw=fopen("who.dat","r"))==NULL){
    perror("fopen");
    exit(1);
  }
  /* Open for writing answers.dat */
  if((fda=fopen("answers.dat","w"))==NULL){
    perror("fopen");
    exit(1);
  }
  while (getlineX(fdw,who,LINESIZE-1)!=EOF){   /* Read a line from "who.dat" */
    where = stringBinary(linearray,n,who);    /* See where it is in table */
    fprintf(fda,"%d\n",where);            /* Write position to "answer.dat*/
  }
  fclose(fdw);
  fclose(fda);
}
