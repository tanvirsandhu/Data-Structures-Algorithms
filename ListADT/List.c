//Tanvir Sandhu
//CSE 101
//October 10, 2021
//Homework 1

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Type 1: List is a list with extra node structure
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
}NodeObj;
typedef NodeObj* NodePtr;

typedef struct ListObj{
    NodePtr head;
    int length;
}ListObj;

ListPtr newList( void ) {
    ListPtr L = (ListPtr)malloc(sizeof(ListPtr));

    L->head = NULL;
    L->length = 0;

    return L;
}

void freeList( ListPtr* pL ) {
    free(pL);
    pL = NULL;
}

int  length( ListPtr L ) {
    if (L == NULL) {
        return 1; 
    } else {
        return L->length;
    }
}

int  max( ListPtr L ) {
    NodePtr list = L->head;
    int index = 0;
    int max = 0;
    
    int i;
    for (i = 0; i < length(L); i += 1) {
        if (list->data > max) {
            max = list->data;
            list = list->next;
            index = i;
        } else {
            list = list->next;
        }
    }
    return index;
}

int  find( ListPtr L, int i ) {
    int j = 0;
    int k = 0;
    NodePtr list = L->head;

    for (k = 0; k < length(L); k += 1) {
        if (list->data == i) {
            return j;
        } else {
            j += 1;
            list = list->next;
        }
    }
    return -1;
}

int delElement( ListPtr L, int i ) {
    int j = 0;
    NodePtr list = L->head;
    while (j < i) {
        if (L->head->data == i) {
            L->head = list->next;
            list->next = list->next->next;
            list = list->next;
        } else if (list->data == i) {
            //finish this
        }
        list = list->next;
        j+=1;
    }
}

void appendList( ListPtr L, int i ) {
    int j = 0;
    NodePtr list = L->head;
    while (j < length(L)) {
        list = list->next;
        j += 1;
    }
    list->next->data = i;
}

void printList( ListPtr L ) {
    int j = 0;
    NodePtr list = L->head;
    printf("(");
    for (j = 0; j < length(L); j += 1) {
        printf("%d,", list->data);
        list = list->next;
    }
    printf(")\n");
}