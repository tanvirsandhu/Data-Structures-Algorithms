//----------------------------------------------------
// Queue.h
// Header file for Queue ADT
// Queue implementation using an array of integers
// ---------------------------------------------------


typedef struct Queue Queue;

// Constructor-Destructor ------------------------------------

// Initialize Queue from and array of ints of length n
Queue* initializeQueue(int n, int* arr);

// Free memory allocated to queue
void destructQueue(Queue* q);

// Queue Functionalities ------------------------------------

// Add element 'ser' into queue
void enqueue(Queue* q, int ser);

// Remove the element from front of queue
void dequeue(Queue* q);

// Utility Functions ----------------------------------------

// prints queue
void printQueue(Queue* q);


// Return the length of the queue
int count(Queue* q);
