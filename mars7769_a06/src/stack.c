/*
--------------------------------------------------
Project: a6q2
File:    stack.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include "stack.h"

/*
 * Push a node into a linked list stack
 * @param STACK *sp - pointer to the stack
 * @param NODE *np - pointer to the node.
*/

void push(STACK *sp, NODE *np) { // add to top of the stack
// your code
	if (!sp || !np) return; // empty stack

	np->next = sp->top; // set next pointer to the top
	sp->top = np; // set top pointer to new node
	sp->length++; // increment length
}

/*
 * Pop and return the pointer of the removed top node
 * @param STACK *sp - pointer to the stack
 * @return - the reference of the removed node and set it's next to NULL
*/

NODE *pop(STACK *sp) { // takes off top of the stack
// your code
	if (!sp || !sp->top) return NULL; // empty stack

		NODE *removed = sp->top; // get front node (top node)
		sp->top = sp->top->next; // move top to next node (one below)


		removed->next = NULL;
		sp->length--; // decrement length

		return removed; // return removed nodes

	}

void clean_stack(STACK *sp) { // clears stack
  clean(&(sp->top));
  sp->top = NULL;
  sp->length=0;
}
