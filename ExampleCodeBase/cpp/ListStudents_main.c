/* studentlistmain.c -- Reads a file containing a sequence of records
 *                  representing students, places them into a linked
 *                  list (a queue), then writes that  out to a new files.
 *                  The names of the files are passed in as command
 *                  line parameters.
 */

#include <stdio.h>
#include "ListStudents_queue.h"

#define NAMESIZE 25

typedef struct {
  char name[NAMESIZE];
  int  midterm;
  int final;
  int homeworks;
} student;

typedef student *studentptr;


void writeStudentList(char filename[], queue *q)
     /* filename is the name of the file where we will
      * write sequentially the list accessed from q.
      */
{
  FILE *fd;  /* File descriptor used for filename */
  studentptr s;

  if((fd=fopen(filename,"w"))==NULL){
    perror("fopen");
    exit(1);
  }
  while(get(q, s)){
    fprintf(fd,"%s %d %d %d\n",
	    s->name, 
	    s->midterm, 
	    s->final, 
	    s->homeworks);
  }
  fclose(fd);
}

int readStudentList(char filename[], queue *q)
     /* It reads student records from file filename 
      * and stores them in q.
      * It returns the number of records actually read.
      */
{
  FILE *fd;  /* File descriptor used for filename */
  int i=0;
  student temp;
  
  if((fd=fopen(filename,"r"))==NULL){
    perror("fopen");
    exit(1);
  }
  while(fscanf(fd,"%s %d %d %d",
	       temp.name, 
	       &temp.midterm,
	       &temp.final, 
	       &temp.homeworks)!=EOF){
    put(q,&temp);
    i++;
  }
  fclose(fd);
  return i;
}

int main(int argc, char *argv[]){
  int n;
  queue *q;

  if(argc!=3){
    printf("Usage: %s infile outfile\n", argv[0]);
    exit(0);
  }
  q = init(sizeof(student));
  n = readStudentList(argv[1],q);
  writeStudentList(argv[2],q);
  final(q);
}
