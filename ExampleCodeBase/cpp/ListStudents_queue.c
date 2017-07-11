/* queue.c -- Generic unbounded queue ADT for fized size values.
 */

#include <stdio.h>
#include <stdlib.h>
#include "ListStudents_queue.h"

queue *init(int n){
  /* It creates, initializes, and returns a queue that stores values
     of size n */
  queue *q;

  if((q=(queue *)malloc(sizeof(queue)))==NULL){
    perror("malloc");
    exit(1);
  }
  q->nodesize=n;
  q->head=NULL;
  q->tail=NULL;
  return q;
}

void final(queue *q){
  /* It frees all storage associated with the queue q */
  char *s;

  if((s=(char *)malloc(q->nodesize))==NULL){
    perror("malloc");
    exit(1);
  }
  while(get(q,s));
  free(q);
  free(s);
}

void put(queue *q, void * s){
  /* It inserts a copy of the value *s in the queue q */
  nodeptr p;
  void *r;
  
  if ((p=(nodeptr)malloc(sizeof(node)))==NULL){
    perror("malloc");
    exit(1);
  }
  if ((r=(void *)malloc(q->nodesize))==NULL){
    perror("malloc");
    exit(1);
  }
  bcopy(s,r,q->nodesize);
  p->value = r;
  p->next = NULL;
  if (q->head == NULL)
    q->head = p;
  else
    q->tail->next = p;
  q->tail = p;
}

int get(queue *q, void *s){
  /*It obtains in *s a copy of a value from queue q. It returns true
    iff such a record existed */
  nodeptr p;

  if(p=q->head){
    q->head = q->head->next;
    if((q->head)==NULL)
      q->tail = NULL;
    bcopy(p->value,s,q->nodesize);
    free(p->value);
    free(p);
    return 1;
  }else
    return 0;
}
