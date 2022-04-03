//Tanvir Sandhu
//CSE 101 - Alex Pang
//Program 2
//October 31, 2021

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Queue.h"
// Implemeting Queue

/*
TODO: define the Queue structure using 'typedef struct Queue' - this queue holds integer values
the Queue struct has the following fields:
- head: corresponding to the head of the queue
- tail: indicating the tail of the queue
- length: length of the array used for implementing the queue
- count: number of elements in the queue
- array: (pointer to) the array used for implementing the queue
- id: (pointer to) the array of client id used for implementing the queue
*/

typedef struct Queue {
	 int length;
	 int head;
	 int tail;
	 int count; 
	 int *array;
	 int *id;
}Queue;
typedef Queue* QueuePtr;


//------------------------------------------------------------------------

/*
TODO: implement the initializeQueue - this function instantiates the Queue struct using malloc and sets the values for the fields.
It returns a pointer to the instantiated Queue
*/

//i malloc for the size of Queue and initialize all the values of the queue struct.
Queue* initializeQueue(int n, int* arr, int* id) {
	 QueuePtr q = (QueuePtr)malloc(sizeof(Queue));

	 q->length = n;
	 q->head = 0;
	 q->tail = 0;
	 q->count = 0;
	 q->array = arr;
	 q->id = id;

	 return q;
}




//------------------------------------------------------------------------

/*
TODO: implement Queue destructor - this function frees memory allocated to Queue
*/


//i free the queue using the built-in free func
void destructQueue(Queue* q) {
	 free(q);
}


//------------------------------------------------------------------------

/* TODO: implement the 'enqueue' functionality
This function takes in a queue pointer and int service time 'ser' and adds 'ser' to queue
*/


//in order to add the element at the end of the queue, i create a circular queue using the modulo line the professor gave us in lecture
void enqueue(Queue* q, int i, int ser) {
	 //i set an int variabel to q->length to use throughout this function for easy
	 int len = q->length;
	  if (count(q) >= (q->length)) {
			  //if the queue has reached the maximum allocated space, then an error message is printed.
        fprintf(stdout, "Queue Full\n");
    } else if (count(q) < q->length-1) {
			  //if there is still space in the queue, i add the ser and i to array and id, respectively, at the tail
				q->array[q->tail] = ser;
				q->id[q->tail] = i;
				//modulo line given by professor
				q->tail = (q->tail + 1) % len;
	      //after adding the element, i increase the count by 1 to track the count
				q->count += 1;
    } else if (count(q) == 0) {
			  //if the queue is empty and the first element is being added, both the head and tail or array and id need to be set to the new values
			  q->array[q->head] = ser;
			  q->array[q->tail] = ser;
				q->id[q->head] = i;
			  q->id[q->tail] = i;
				//modulo line given by professor
				q->tail = (q->tail + 1) % len;
				//after adding the element, i increase the count by 1 to track it.
				q->count += 1;
		}
}

//------------------------------------------------------------------------


	 /* TODO: iimplement the 'dequeue' functionality
This function takes in a queue pointer and removes element from head of the queue
*/

int dequeue(Queue* q) {
	 int head;
	 int len = q->length;
	 if (count(q) <= 0) {
			//if the queue is empty, there is nothing to dequeue
			fprintf(stdout, "Queue Empty\n");
	 } else if (count(q) > 0) {
			//if the queue exists, i set the variable head to the value at the current head's index before changing it to the next element and removing the first one.
			head = q->head;
			q->head = (head + 1) % len;
			q->count -= 1;

			return head;
	 } 
}


//------------------------------------------------------------------------

/* TODO: implement the printQueue
This function takes in a queue pointer and prints the contents of the queue in order (head to tail)
*/

void printQueue(Queue* q) {
	 int x = 0;
	 //prints the elements in the array with a for loop that goes until the count of elements in the list.
	 fprintf(stdout, "Queue: ");
	 for (x = 0; x < count(q); x++) {
			fprintf(stdout, "%d ", q->array[x]);
	 }
	 fprintf(stdout, "\n");
}


//------------------------------------------------------------------------

/* TODO: implement the count
This function takes in a queue pointer and returns the 'count' field of the queue
*/

//returns the q count since it is kept in track throughout the program
int count(Queue *q) {
	 return q->count;
}
