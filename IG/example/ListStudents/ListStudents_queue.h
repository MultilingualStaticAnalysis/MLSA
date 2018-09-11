/* queue.h - Header file for an unbounded queue ADT for
 *           fixed size values.
 */

typedef struct node {
  struct node *next;
  void *value;
}node;

typedef node *nodeptr;

typedef struct {
  int nodesize;  /* Size of the value field of a node */
  nodeptr head;  /* Here we point to the oldest element in the queue */
  nodeptr tail;  /* Here we point to the most recent element in queue*/
} queue;

queue *init(int n);
/* It creates, initializes, and returns a queue that stores values
   of size n */

void final(queue *q);
/* It frees all storage associated with the queue q */

void put(queue *q, void * s);
/* It inserts a copy of the value *s in the queue q */

int get(queue *q, void *s);
/* It obtains in *s a copy of a value from queue q. It returns true
   iff such a record existed */