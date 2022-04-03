//Tanvir Sandhu
//CSE 101 - Alex Pang
//Program 2
//October 31, 2021

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.h"

// TODO: Implement funcs for fetching parent and left/right child


//the index of the parent of the element at index i is given by the formula in the function, so i return its index for use in heapify
int parent(int i) {
	 //printf("parent ind: %d\n", x);
	 int x = ((i - 1) / 2);
	 return x;
}

//the index of the left child of the element at index i is given by the formula in the function, so i return its index for use in heapify
int left (int i) {
	 int x = (2 * i) + 1;
	 //printf("left ind: %d\n", x);
	 return x;
}

//the index of the right child of the element of index i is given by the same formula as above except adding two instead of one, since c floor divides, so i return its index for use in heapify.
int right (int i) {
	 int x = (2 * i) + 2;
	 //printf("right ind: %d\n", x);
	 return x;
}

int size(Heap *h);
int len(Heap *h);


//------------------------------------------------------------------------

// TODO: Helper function for swapping A[i] and A[j] elements in an array


//I store the element at index i in an int variable and switch index i to hold j's element. Then, i place the stored value of i into j.
void swap(int* A, int i, int j) {
	 int x = A[i];
	 A[i] = A[j];
	 A[j] = x;
}


//------------------------------------------------------------------------

/* TODO: declare the Heap struct as in the header file
This Heap struc has the following fields:
- len: length of the array used for implementing the heap
- size: number of elements in the backbone array that are 'heapified' or ordered as heap
- array: (pointer to) array used for implementing the heap
- id: (pointer to) array of client id used for implementing the heap
*/

typedef struct Heap {
	 int len;
	 int size;
	 int *array;
	 int *id;
}Heap;
typedef Heap* HeapPtr;

//------------- -----------------------------------------------------------

/* TODO: implement initializeHeap function which instantiates a heap using malloc.
It returns a pointer to the instantiated heap
*/


//i malloc the size of the heap and initialize all of the values to the new heap parameters.
Heap* initializeHeap(int len, int h_size, int* arr, int* id) {
			Heap* ptr = (Heap*)malloc(sizeof(Heap));

			ptr->len = len;
			ptr->size = h_size;
			ptr->array = arr;
			ptr->id = id;

			return ptr;
 	 }


//------------------------------------------------------------------------


/*  TODO: implement heap destructor that frees memory allocated to heap */


//i free the memory allocated for the heap and make sure that the heap is null.
void destructHeap(Heap* h) {
			free(h);
}


//------------------------------------------------------------------------

/* TODO: implement 'heapify' function, given a heap pointer and an index i
This function maintain (min) Heap property given an index i for heap h
*/

void heapify(Heap* h, int i) {

	 //i first check if the parent element is greater than the current element
	 if (h->array[i] <= h->array[parent(i)]) {
			//if it is, then as long as that index is within the amount of values in the heap, i swap the values to heapify in both arrays.
			if (parent(i) <= h->size-1) {
				 swap(h->array, i, parent(i));
				 swap(h->id, i, parent(i));
			}
	 } 
	 //i then do the same checks for for the left and right children of the element at index i to make sure that the the smallest element is at the top.
	 if (h->array[i] >= h->array[left(i)]) {
			if (left(i) <= h->size-1) {
				 swap(h->array, i, left(i));
				 swap(h->id, i, left(i));
			}
	 } 
	 if (h->array[i] >= h->array[right(i)]) {
			if (right(i) <= h->size-1) {
				 swap(h->array, i, right(i));
				 swap(h->id, i, right(i));
			}
	 } 
}


//------------------------------------------------------------------------

/* TODO: implement array_to_heap function
You may use initializeHeap function for implementing this function
*/

//this function creates a min heap using the previous functions
Heap* array_to_Heap(int* A, int* id, int len, int size) {
	 //heap is initialized
	 Heap* h = initializeHeap(len, size, A, id);

	 //x is initialized for the for loop and y is used to hold the index of the value the heapify is starting from
	 int y = parent((h->size) - 1);
	 int x;
	 
	 //i start from the end of the array to guarantee correct heap
	 for (x = y; x >= 0; x-=1) {
			//printf("%d\n", h->array[x]);
			heapify(h, x);
	 }
	 //to make sure there are no leaks, i transfer the newly created heap to a different Heap * and return it, while freeing the old pointer.
	 Heap *newheap = h;
	 free(h);
	 return newheap;
}


//------------------------------------------------------------------------

/* TODO: implement utility functions:
- size(): returns the size field of a heap
- len(): returns the length field of a heap
*/

//h->size keeps track of size so i just return its value
int size(Heap *h) {
	 return h->size;
}

//h->len keeps track of len so i just return its value
int len(Heap *h) {
	 return h->len;
}

//to print the heap, i print each id value from 0 until its size
void printHeap(Heap* h) {
	 int x;

	 for (x = 0; x < h->size; x++) {
			fprintf(stdout, "%d ", h->id[x]);
	 }
	 fprintf(stdout, "\n");
}

