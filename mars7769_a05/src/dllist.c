/*
--------------------------------------------------
Project: a5q2
File:    dllist.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

/*
 * Create and return a new node using malloc() with passed data value and returns pointer of the node.
*/

NODE *dll_node(char data) {
// your code
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	    if (!newNode) {
	        printf("Memory allocation failed.\n");
	        return NULL;
	    }
	    newNode->data = data;
	    newNode->prev = NULL;
	    newNode->next = NULL;
	    return newNode;
}

/*
 * Insert a given node at the beginning the of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
 * @param NODE *np  -  reference of a NODE node to be inserted
*/

void dll_insert_start(DLL *dllp, NODE *np) {
// your code
	if (!dllp || !np) return;

	    np->next = dllp->start;
	    np->prev = NULL;

	    if (dllp->start) {
	        dllp->start->prev = np;
	    } else {
	        dllp->end = np;
	    }

	    dllp->start = np;
	    dllp->length++;

}

/*
 * Insert a node at the end of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
 * @param NODE *np  -  reference of a NODE node to be inserted
*/

void dll_insert_end(DLL *dllp, NODE *np) {
// your code
	 if (!dllp || !np) return;

	    np->next = NULL;
	    np->prev = dllp->end;

	    if (dllp->end) {
	        dllp->end->next = np;
	    } else {
	        dllp->start = np;
	    }

	    dllp->end = np;
	    dllp->length++;

}


/*
 * This deletes the first node of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
*/

void dll_delete_start(DLL *dllp) {
// your code
	 if (!dllp || !dllp->start) return;

	    NODE *temp = dllp->start;
	    dllp->start = dllp->start->next;

	    if (dllp->start) {
	        dllp->start->prev = NULL;
	    } else {
	        dllp->end = NULL;
	    }

	    free(temp);
	    dllp->length--;

}

/*
 * Delete the end node of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
*/

void dll_delete_end(DLL *dllp) {
// your code
	if (!dllp || !dllp->end) return;

	    NODE *temp = dllp->end;
	    dllp->end = dllp->end->prev;

	    if (dllp->end) {
	        dllp->end->next = NULL;
	    } else {
	        dllp->start = NULL;
	    }

	    free(temp);
	    dllp->length--;

}

/*
 * Clean and free the nodes of a doubly linked list and reset start and length.
 * @param DLL *dllp -  reference to input DLL variable
*/

void dll_clean(DLL *dllp) {
// your code
	 if (!dllp) return;

	    NODE *current = dllp->start;
	    while (current) {
	        NODE *temp = current;
	        current = current->next;
	        free(temp);
	    }

	    dllp->start = NULL;
	    dllp->end = NULL;
	    dllp->length = 0;

}
