//Tanvir Sandhu
//CSE 101
//October 10, 2021
//Homework 1

#include "List.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	// Declare a new list
	ListPtr list = newList();
	// Accept input from the user	
	char action;
	int j; 
	// Perform desired operation on list
	if ((fscanf("sampleInput.txt", "%c %d", &action, &j)) != EOF) {
		if (action == "MAX") {
			max(list);
		} else if (action == "LENGTH") {
			length(list);
		} else if (action == "FIND") {
			find(list, j);
		} else if (action == "APPEND") {
			appendList(list, j);
		} else if (action == "PRINT")
			printList(list);
	} else {
		return -1;
	}
}