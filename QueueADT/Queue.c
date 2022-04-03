//Tanvir Sandhu
//October 24, 2021
//CSE 101 - Alex Pang
//Homework 2

#include <stdlib.h>
#include <stdio.h>
#include <assert.h> 
#include "Queue.h"
// Implemeting Queue

/*
TODO: define the Queue structure using 'typedef struct Queue' - this queue holds integer values
the Queue struct has the following fields:
- head: corresponding to the head of the queue
- tail: indicating the tail of the queue
- length: length of the array used for implementing the queue
- count: number of elements in the queue
- array: (pointer to) the array used for implementing the queue
*/

typedef struct Queue {
    int length;
    int head;
    int tail;
    int count; 
    int *array;
}Queue;
typedef Queue* QueuePtr;

//------------------------------------------------------------------------

/*
TODO: implement the initializeQueue - this function instantiates the Queue struct using malloc and sets the values for the fields.
It returns a pointer to the instantiated Queue
*/
Queue* initializeQueue(int n, int* arr) {
    QueuePtr q = (QueuePtr)malloc(n);

    q->length = n;
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    q->array = arr;

    return q;
}


//------------------------------------------------------------------------

/*
TODO: implement Queue destructor - this function frees memory allocated to Queue
*/
void destructQueue(Queue* q) {
    free(q);
}


//------------------------------------------------------------------------

/* TODO: implement the 'enqueue' functionality
This function takes in a queue pointer and int service time 'ser' and adds 'ser' to queue
*/
void enqueue(Queue* q, int ser){
    if (q->count == (q->length-1)) {
        fprintf(stdout, "NOT ENOUGH SPACE IN QUEUE\n");
    } else if (q->count > 0) {
			   //printf("else");
				 q->tail += 1;
			   q->array[q->tail] = ser;
				 //printf("%d", q->tail);
			   q->count += 1;
    } else if (q->count == 0) {
				 //printf("if");
			   q->array[q->head] = ser;
				 q->array[q->tail] = ser;
				 q->count += 1;

    } 
}


//------------------------------------------------------------------------

/* TODO: implement the 'dequeue' functionality
This function takes in a queue pointer and removes element from head of the queue
Print "Empty Queue" if there's not element to remove
*/
void dequeue(Queue* q) {
    int x;
    if (q->count == 0) {
        fprintf(stdout, "Queue Empty\n");
    } else {
        x = q->array[q->head];
				//printf("head: %d", q->array[q->head]);
        //free(q->array[q->head]);
        for (int j = 0; j < q->count-1; j++) {
					  q->array[j] = q->array[j+1];
			  }
        //return x;
				q->tail -= 1;
				q->count -= 1;
    }
}


//------------------------------------------------------------------------

/* TODO: implement the printQueue
This function takes in a queue pointer and prints the contents of the queue in order (head to tail)
*/
void printQueue(Queue* q) {
    int x = 0;
		fprintf(stdout, "Queue: ");
    while (x < q->count) {
        fprintf(stdout, "%d ", q->array[x]);
        x += 1;
    }
		fprintf(stdout, "\n");
}

//------------------------------------------------------------------------

/* TODO: implement the count
This function takes in a queue pointer and returns the 'count' field of the queue
*/

int count(Queue* q) {
    return q->count;
}
