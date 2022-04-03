//Tanvir Sandhu
//CSE 101 - Alex Pang
//Program 2
//October 31, 2021

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.c"
#include"PriorityQueue.h"
#include"Queue.h"

/* TODO: implement get_min
 * returns minumum element in heap/shortest processing time
 * */


//Because the minimum element should be at the head of the array/heap, i can just return the element at the front, aka the element at index 0.
int get_min(Heap* h) {
	 array_to_Heap(h->array, h->id, h->len, h->size);
	 return h->id[0];
}



//------------------------------------------------------------------------
//
///* TODO: implement extract_min
//extracts and returns min element in heap
//note that heap property must be maintained after extraction
//also check for valid input (cannot extract from empty heap)

int extract_min(Heap* h) {
	 //i call array to heap here to make sure the heap is heapified.
	 array_to_Heap(h->array, h->id, h->len, h->size);
	  int x = 0;	 
		//if the heap is empty, nothing can be extracted and it will return nothing.
	  if (h->size > 0) {
        //if the heap exists, both heads of array and id are removed and replaced by the next value of the list
				x = h->id[0];
				int j = 0;
        for (j = 0; j < h->size; j += 1) {
            h->array[j] = h->array[j+1];
						h->id[j] = h->id[j+1];
        }
				//the size is then decremented to account for the extracted min
        h->size -= 1;
				//re do the heap to make sure it is heapified
			  array_to_Heap(h->array, h->id, h->len, h->size);
				//then i return the variable that holds the head of id before it was changed.
        return x;
    } 
}


////------------------------------------------------------------------------
//
///* TODO: implement increase_priority
//This function increases priority of element at index i to 'new_value'

void increase_priority(Heap* h, int i, int new_value, int idn) {
	 //if the new value has a greater priority (is smaller) than the current value, then it is replaced with the new value and id.
	 if (h->array[i] >= new_value) {
			//printf("new val: %d", new_value);
			//printf("index: %d", i);
			h->array[i] = new_value;
			h->id[i] = idn;
			//heapified to preserve the heap
			array_to_Heap(h->array, h->id, h->len, h->size);
	 } else if (i == h->size) {
			//if the new value's desired index is at the end of the heap, we add it the same way without replacing any value.(used for insert)
			h->array[i] = new_value;
			h->id[i] = idn;
			//heapified to preserve the heap
			array_to_Heap(h->array, h->id, h->len, h->size);
	 }
}

////------------------------------------------------------------------------
//
///* TODO: implement insert functionality
//This function inserts priority 'value' into heap
//You will need to have implemented the increase_priority and use it here
//

void insert(Heap* h, int id, int value) {
	 //if the heap is already at maximum capacity already, the function will return nothing and continue
	 if (h->size == h->len) {
			return;
	 } else if (h->len > h->size) {
			//if the heap still has space, the value is inserted, the size is increased, and it is heaped when in increase priority
			increase_priority(h, h->size, value, id);
			h->size += 1;
			//array_to_Heap(h->array, h->id, h->len, h->size);
	 }
}
