//Tanvir Sandhu
//December 6, 2021
//CSE 101 - Alex Pang 
//Program 5

#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "Graph.h"

typedef struct Graph{
    int num_vertices;
    ListPtr *adjacency_list; // Is an array of ListPtrs for faster access
} Graph; 

int compareData(void *obj1, void *obj2) {
	 int ob1 = *((int *)obj1);
	 int ob2 = *((int *)obj2);

	 if (ob1 == ob2) {
			return 0;
	 } //else if (ob1 < ob2) {
			//return -1;
	 //} else if (ob1 > ob2) {
			//return 1;
	 //}
}

void printerData(void *data){

}

void dataFree(void* data) {
	 free(data);
	 data = NULL;
}

// Hints: You will need to implement a ListPtr DataCompare, DataPrinter and 
//        freeData for the lists used in the adjacency list. These will be ints.
//        You can copy this from the ones in prog5.c, but they should have different name to avoid a namesapce collision.
//TODO: Implement all functions from the header file.

Graph *graph_create(int numVertices) {
	 //malloc for graph and initialize variables
	 Graph *g = (Graph*)malloc(sizeof(Graph));

	 g->num_vertices = numVertices;
	 g->adjacency_list = (ListPtr*)malloc(numVertices * sizeof(ListPtr));

	 //creating lists for the amount of vertices
	 for (int k = 0; k < numVertices; k++) {
			g->adjacency_list[k] = list_create(compareData, printerData, dataFree);
	 }
	 //printf("%d", numVertices);
	 return g;
}

void graph_destroy(Graph *g) {
	 free(g);
	 g = NULL;
}

bool graph_add_edge(Graph *g, int v1, int v2) {
	 //malloc for int* versions of the inputs
	 int *vt1 = (int*)malloc(sizeof(int));
	 int *vt2 = (int*)malloc(sizeof(int));
	 *vt1 = v1;
	 *vt2 = v2;
	 
	 //if its the same vertex, exit false
	 if (v1 == v2) {
			return false;
	 }
	 //if v1 is out of bounds, exit false;
	 if (v1 >= g->num_vertices) {
    return false;
	 }
	 //if the edge already exits, exit false
	 if (list_find_element(g->adjacency_list[v1], vt2) != -1 && list_find_element(g->adjacency_list[v2], vt1) != -1) {
			return false;
	 }
	 //if v2 is out of bounds, exit false;
	 if (v2 >= g->num_vertices) {
			return false;
	 } else {
			//otherwise, i append the edge to the adjlist both ways
			list_append(g->adjacency_list[v2], vt1);
			//printf("appended\n");
			list_append(g->adjacency_list[v1], vt2);
			//printf("appended\n");
			return true;
	 }
	 return true;
}

bool graph_add_nodes(Graph *g, int numVertices) {
	 //as long as the graph exists, the new numVertices is the sum of the previous and the amount we're adding
	 if (g) {
			int new = g->num_vertices + numVertices;

			//realloc for the amount of new nodes and create lists for the new one
			//set the num_vertices to the new value
			g->adjacency_list = realloc(g->adjacency_list, new * sizeof(ListPtr));
			for (int k = g->num_vertices; k < new; k++) {
				 g->adjacency_list[k] = list_create(compareData, printerData, dataFree);
			}
			g->num_vertices = new;
			return true;
	 }
	 return false;
}

bool graph_remove_edge(Graph *g, int v1, int v2) {
	 //malloc for int* versions of the inputs
	 int *vt1 = (int*)malloc(sizeof(int));
	 int *vt2 = (int*)malloc(sizeof(int));
	 *vt1 = v1;
	 *vt2 = v2;
	 
	 //if they are equal, then exit false
	 if (v1 == v2) {
			return false;
	 } 
	 //if either entry is out of bounds, exit false
	 if (v1 < 0 || v2 < 0 || v1 >= g->num_vertices || v2 >= g->num_vertices) {
			return false;
	 }
	 //else, we can continue with the removal
	 //i find the points index within the neighbor list and then delete it from both inputs lists
	 int i = 0;
	 int j = 0;
	 i = list_find_element(g->adjacency_list[v1], vt2);
	 j = list_find_element(g->adjacency_list[v2], vt1);
	 if (i != -1) {
			if (j != -1) {
			//i = list_find_element(g->adjacency_list[v1], vt2);
			//j = list_find_element(g->adjacency_list[v2], vt1);

				 list_del_index(g->adjacency_list[v1], i);
				 list_del_index(g->adjacency_list[v2], j);

				 return true;
			} else {
				 return false;
			}
	 } else {
			return false;
	 } 	 
}

bool graph_has_edge(Graph *g, int v1, int v2) {
	 //malloc for int* versions of the input
	 int *vt1 = (int*)malloc(sizeof(int));
	 int *vt2 = (int*)malloc(sizeof(int));
	 *vt1 = v1;
	 *vt2 = v2;
	 
	 //if theey're equal to each other, exit false
	 if (v1 == v2) {
			return false;
	 } 
	 //if either entry is out of bounds, exit false
	 if (v1 < 0 || v2 < 0 || v1 >= g->num_vertices || v2 >= g->num_vertices) {
			return false;
	 }
	 //if the edge exists, return true
	 if (list_find_element(g->adjacency_list[v1], vt2) != -1 && list_find_element(g->adjacency_list[v2], vt1) != -1) {
			return true;
	 } else {
			return false;
	 }
}

ListPtr graph_get_neighbors(Graph *g, int vertex) {
	 //if the vertex is out of bounds, return NULL
	 if (vertex <= -1) {
			return NULL;
	 //if it doesn't exist in the list, return NULL
	 } else if (g->adjacency_list[vertex] == NULL) {
			return NULL;
	 //otherwise, return its ListPtr
	 } else {
			return g->adjacency_list[vertex];
	 }
}

int graph_num_vertices(Graph *g) {
	 //returns the num_vertices of the graph
	 return g->num_vertices;
}

int graph_num_edges(Graph *g) {
	 //for loop that iterates through the adjacency list and checks the length of each list of edges,
	 //and adds it to itself to find the total
	 int edges = 0;

	 for (int k = 0; k < g->num_vertices; k++) {
			int len = list_length(g->adjacency_list[k]);
			edges += len;
	 }
	 //because i add to the dictionary both ways, i have to divide by two before i return
	 edges = edges / 2;
	 return edges;
}


