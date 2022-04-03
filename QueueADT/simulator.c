#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "Queue.h"

#define LEN 100	//code to create queue of array length = 100


int main(int argc, char **argv){

    char line[1024];
    int array[LEN] = {};
	  char command[30];
		char add[5] = "ADD";
		char service[10] = "SERVICE";
		char print[10] = "PRINT";
		char length[10] = "LENGTH";
		int num;


    Queue *q = initializeQueue(40, array);
	  
		while (fgets(line, 1024, stdin) != NULL) {
        sscanf(line, "%s", command);
				//printf("command: %s\n", command);
				if (strcmp(add, command) == 0) {
					 sscanf(line, "%s%i", command, &num);
					 //printf("%i", num);
					 enqueue(q, num);
				} else if (strcmp(service, command) == 0) {
				   dequeue(q);
				} else if (strcmp(print, command) == 0) {
					 printQueue(q);
				} else if (strcmp(length, command) == 0) {
					 printf("Length: %d\n", count(q));
				}
		}


	 //code to free memory allocated to queue

}
