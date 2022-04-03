//Tanvir Sandhu 
//December 6, 2021
//CSE 101 - Alex Pang
//Program 5

#include "Graph.h"
#include "List.h"
#include "PQueue.h"
#include "Dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Point {
    int x;
    int y;
} Point;

Point *create_point(int x, int y) {
    Point *p = malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}

//prints the KVPair in k:v format
void dataPrinter(void *data) {
	 int *woo = (int*)data;

	 fprintf(stdout, "%d \n", woo);

	 }

//prints a KVPair in the correct format
void dictPrinter(void *data) {
	 KVPair *kvp = (KVPair*)data;
	 fprintf(stdout, "%d: %d\n", kvp->key, kvp->value);
}

//compares the keys of two kv pairs and returns 0 if they're equal
int dictCompare(void *obj1, void *obj2) {
	 KVPair *kvp = (KVPair*)obj1;
	 KVPair *kvp2 = (KVPair*)obj2;
	 int* key = (int*)kvp->key;
	 int* key2 = (int*)kvp2->key;
	 if (key == key2) {
			return 0;
	 } else {
			return 1;
	 }
}

//free the data of a kv pair when given one
void freeData(void *data) {
	 free(data);
	 data = NULL;
}

//compares two KVPairs for key and value to sort the list in order of value and (A-Z) key
//this function is used by the list sort function to compare each kv pair and sort the list based on that
int listCompare(void *obj1, void *obj2) {
	 KVPair *obj = (KVPair*)obj1;
	 KVPair *obj3 = (KVPair*)obj2;
	 //fprintf(stdout, "yiggity");
	 if (obj3->value == obj->value) {
			//i had to use strcmp for the keys of each kv pair 
			if (strcmp(obj->key, obj3->key) < 0) {
				 return 1;
			} else if (strcmp(obj->key, obj3->key) > 0) {
				 return -1;
			} else if (strcmp(obj->key, obj3->key) == 0) {
				 return 0;
			}
	 } else if (obj3->value > obj->value) {
			return -1;
	 } else {
			return 1;
	 }
}

//the hash function i created to return the unsigned long version of the void* key
unsigned long hashkey(void *key) {
	 unsigned long new = (unsigned long) key;
	 return new;
}
//Hint: The ListPtrs will store ints for bfs and a_star.
//      You need to define the dataCompare, dataPrinter and freeData functions here. 


/**
 * @brief Implements the bst algorithm to find the shortest path between 2 nodes in an unweighted graph.
 * 
 * @param g The graph to search through
 * @param vertex_start The index of the vertex in the graph from where to start the search.
 * @param vertex_end The index of the vertex in the graph that needs to be reached.
 * @param vertices_explored The value in this pointer should be set to the number of vertices that were visited by the algorithm.
 * @return ListPtr A list of the nodes that make up the path from the start to the end, including the start and end nodes.
 */
ListPtr bfs(Graph *g, int vertex_start, int vertex_end, long *vertices_explored) {
    //Perform bfs traversal. Make sure to store who the parent of each node in your traversal is.
    // Mark visited nodes to maek sure not to visit them twice
		//fprintf(stdout, "%d, %d\n", vertex_start, vertex_end);
		
		//malloc space for an int * to cast the inputs as int*
	  int* begin = (int*)malloc(sizeof(int));
		int* finish = (int*)malloc(sizeof(int));
		*begin = vertex_start;
		*finish = vertex_end;

		//where i declare all lists and kvpairs used in the function
	  //fprintf(stdout, "%d", vertex_start);
		ListPtr list;
	  list = list_create(listCompare, dataPrinter, freeData);
		ListPtr travel;
		travel = list_create(listCompare, dataPrinter, freeData);
	  Dictionary *d = dictionary_create(graph_num_vertices(g), hashkey, dictCompare, dictPrinter, freeData);
		//created the starting KVPair between the start vertext and the NULL vertex it came from
		KVPair *kvp = kvpair_create((void*)vertex_start, NULL);
	  
		//malloc for int* to hold the current node i am exploring and int to hold the index
		int ind = 0;
		int* current = (int*)malloc(sizeof(int));	
	  
		//appending the start point to the list and the kvp pair to the dictionary
		list_append(list, begin);
		dictionary_insert(d, kvp);
		//dictionary_print(d);

		//list_print(list);

	  //implementing the bfs algorithm 
		while (list_length(list) > 0) {
			 //dequeue for the current vertex
			current = (int*)list_del_index(list, ind);
			//count for output incremented
			*vertices_explored +=1;
			//if the current vertex has already reached the end, then break
			if (*current == vertex_end) {
				 break;
			}	
			//i create a list pointer to hold the list for the neighbors of the current vertex
			ListPtr neighbors = graph_get_neighbors(g, *current);
			//list_print(neighbors);
			int x = 0;
			//for the length of the neighbors list, i iterate through the neighbors, and if the neighbor is not already visited,
			//it becomes the current node and added to the dictionary as a pair
			while (x < list_length(neighbors)) {
				 int* next = (int*)malloc(sizeof(int));
				 next = list_get_index(neighbors, x);
				 if (dictionary_find(d, (void*)*next) == NULL) {
						list_append(list, next);
						KVPair *new = kvpair_create((void*)*next, (void*)*current);
						dictionary_insert(d, new);
	  		 }
				 x += 1;
			}
			//dictionary_print(d);
		}
		//dictionary_print(d);
		//fprintf(stdout, "%ld", vertices_explored);
		//list_print(list);
	  
		//*vertices_explored = dictionary_size(d) - 1;
		
		//current node is set to the last vertex
	  current = finish;
		//as i iterate through the list, until i have reached the start node again, i insert the node to index 0 (basically queueing),
		//and find the vertex that it came from so i can make that the current node and insert it all over again
		while (*current != *begin) {
			list_insert(travel, ind, *current);
			KVPair* found = dictionary_find(d, (void*)*current);
			//fprintf(stdout, "%d %d\n", *current, found->value);
			int *yeet = (int*)found->value;
			*current = yeet;
			//fprintf(stdout, "%d %d\n", *current, found->value);
		}
	  //inserting the start vertex as it is skipped over in the while loop
		list_insert(travel, ind, vertex_start);
		//list_print(travel);
		return travel;
		exit(0);
}

/**
 * @brief Implements the A* search algorithm to find the shortest path between 2 nodes in an unweighted graph.
 * 
 * @param g The graph to search through
 * @param nodeArr Array of positions of the graph vertices on a 2d plane. Note this is a pointer to a contiguous array, where nodeArr[i] should correspond to node i in the graph. 
 * @param vertex_start The index of the vertex in the graph from where to start the search.
 * @param vertex_end The index of the vertex in the graph that needs to be reached.
 * @param vertices_explored The value in this pointer should be set to the number of vertices that were visited by the algorithm.
 * @return ListPtr A list of the nodes that make up the path from the start to the end, including the start and end nodes.
 */
ListPtr a_star(Graph *g, Point *nodeArr, int vertex_start, int vertex_end, long *vertices_explored) {
    //Perform a star traversal. Make sure to store who the parent of each node in your traversal is, and the path cost up to that node.
    return NULL;
}


int main(int argc, char* argv[]) {
    Graph *g;

	  char entry[100];									//holds the current entry
	  char breaker[10] = "=======";			//the breaker between inputs
		int check = 0;										//checker for the breaker "======="
		int first = 0;										//first checker for nodes
		int sec = 0;											//second checker for edges
		int third = 0;										//third checker for start/end nodes
		int x = 0;												//x-coordinate for node
		int y = 0;												//y-coordinate for node
		int edge1 = 0;										//first edge coordinate for edge
		int edge2 = 0;										//second edge coordinate for edge
		int start = 0;										//the starting node
		int end = 0;											//the ending node
		int graph = 0;										//checks if the graph has been created yet
		long explored = 0;								//variable to return the explored amount to for output
		
		ListPtr points;
	  points = list_create(listCompare, dataPrinter, freeData);
		ListPtr searched;
    // argv[1] will tell you if to run bfs or a_star
    int algorithm = (strcmp(argv[1], "bfs") == 0) ? 0 : 1;
    // stdin will contain your input
	  while (fscanf(stdin, "%s", entry) != EOF) {
			//for each "word", i check how many times the breaker char has been hit
			//because the inputs have the same format, if the breaker char has been hit twice,
			//the program knows the next inputs are vectors until the next breakers
			if (strcmp(entry, breaker) == 0) {
				 check += 1;
				 continue;
			} 
			//if input is nodes
			if (check == 2) {
				 //and if i haven't recorded the first coordinate,
				 if (first == 0) {
						//x-coordinate = entry && increment counter
						first += 1;
						x = atoi(entry);
						//fprintf(stdout, "x");
				 } else {
						//first coordinate has been recorded so y-coordinate = entry && counter decremented
						first -= 1;
						y = atoi(entry);
						//then, i create a point with the new x and y and append that point to the list of points
						Point *p = create_point(x, y);
						list_append(points, p);
				 }
			//if nodes are done and it's time to record edges, this loop is entered
			} else if (check == 4) {
				 //if the graph has not been created with the newly discovered length of nodes, this loop is entered
				 if (graph == 0) {
						//if the graph has not been created yet, i create it and change the check to 1
						g = graph_create(list_length(points));
						graph = 1;
				 } 
				 if (sec == 0) {
						//if the first edge has not been checked, i set the first edge to an int and change the second check to 1
						edge1 = atoi(entry);
						sec += 1;
						//fprintf(stdout, "%d: ", edge1);
				 } else if (sec == 1) {
						//if the first edge has been checked, i set the second edge to the input and change the second check back to 0
						edge2 = atoi(entry);
						sec -= 1;
						//fprintf(stdout, "%d\n", edge2);
						//then, i add the edge to the graph with the newly collected info
						graph_add_edge(g, edge1, edge2);
				 } 
			}
			//if edges are done and it is time to perform bfs this loop is entered
			else if (check == 6) {
				 if (third == 0) {
						//if the start node has not been checked, i set it to an int and change the check to 1
						start = atoi(entry);
						third += 1;
				 } else if (third == 1) {
						//if the start node has already been checked, i set the end integer to the entry and change the check to 0
						end = atoi(entry);
						third -= 1;
						//i run the bfs and store the vertices explored to a long 
						explored = 0;
						searched = bfs(g, start, end, &explored);
						
						int y = 0;
						int right = 0;									//counter for right steps
						int left = 0;										//counter for left steps
						int up = 0;											//counter for up steps
						int down = 0;										//counter for down steps
						int ind = 0;										//counter for index

						//for the duration of searched list, i hold the int* value starting from the beginning
						//and then i find the point stored at that value to compare and calculate the steps
						while (y < list_length(searched)-1) {
							 int *one = list_get_index(searched, ind);
							 int *two = list_get_index(searched, ind+1);
							 
							 //the point i come form 
							 Point *p1 = (Point*)list_get_index(points, one);
							 //the point i go to
							 Point *p2 = (Point*)list_get_index(points, two);
							 
							 //because it is cairo, up is when the neighboring y is smaller
							 //fprintf(stdout, "(%d, %d)  (%d, %d)\n", p1->x, p1->y, p2->x, p2->y);
							 if (p1->y > p2->y) {
									up += 1;
							 } 
							 if (p1->x > p2->x) {
									left += 1;
							 } 
							 if (p1->y < p2->y) {
									down += 1;
							 } 
							 if (p1->x < p2->x) {
									right += 1;
							 }
							 y += 1;
							 ind += 1;
						}
						//formatted output
						fprintf(stdout, "%d %d %d %d %d %d\n", explored, list_length(searched)-1, left, right, up, down);
				 }
				 //fprintf(stdout, "%d", explored);
			}
		}
		//list_print(points);

    //free Data structures
    return 0;
}
