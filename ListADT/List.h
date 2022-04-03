//----------------------------------------------------
// List.h
// Header file for List ADT
// Implement your List ADT as a linked
// list of integers.
// ---------------------------------------------------

typedef struct ListObj* ListPtr;

// Constructors-Destructors --------------------------

ListPtr newList( void );		// returns reference to new empty list.
void freeList( ListPtr* pL );	// Frees memory associated with *pL, sets *pL to NULL.

// Access functions ----------------------------------
  
int  length( ListPtr L );		// returns number of elements in L.
				// throws an error if L does not exist.
int  max( ListPtr L );		// returns index of element with highest value,
				// throws an error if L is empty, or L does not exist.
				// return value varies from 0..length(L)-1
int  find( ListPtr L, int i );	// returns the index of first occurence of i in L.
				// returns -1 if i is not found in L.


// Manipulation functions ----------------------------

int delElement( ListPtr L, int i );	// deletes the ith element of L and return the data of it.
					// throws an error if L has less than i+1 elements.
void appendList( ListPtr L, int i );	// append i to the end of L.
					// throws an error if L does not exist.

// Other functions ----------------------------
void printList( ListPtr L );	// print all data of L with pattern "%d, " and a newline at the end