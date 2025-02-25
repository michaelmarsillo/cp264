/*
--------------------------------------------------
Project: a6q1
File:    queue.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include "queue.h"

/*
 * Enqueue a node into a queue
 * @param *qp - pointer to the queue
 * @param NODE *np - pointer to the node.
*/
void enqueue(QUEUE *qp, NODE *np) {
// your code
	if (!qp || !np) return; // empty queue

	np->next = NULL;

	if (qp->rear) { // if it has a next node
		qp->rear->next = np; // update rear to next
	} else {
		qp->front = np; // set front to new node
	}

	qp->rear = np; // update rear pointer
	qp->length++; // increase the queue length

}


/*
 * Dequeue and return the pointer of the removed node.
 * @param *qp - pointer to the queue
 * @return - the reference of the removed node, and set it's next to NULL
*/
NODE *dequeue(QUEUE *qp) {
// your code
	if (!qp || !qp->front) return NULL; // empty queue

	NODE *removed = qp->front; // get front node
	qp->front = qp->front->next; // move front to next node

	if (!qp->front) { // if queue is empty
		qp->rear = NULL; // set rear to NULL

	}

	removed->next = NULL;
	qp->length--; // decrement length

	return removed; // return removed nodes

}


/*
 * Clean the linked list queue
 * @param *qp - pointer to the queue
*/
void clean_queue(QUEUE *qp) { // clears stack
  clean(&(qp->front));
  qp->front = NULL;
  qp->rear = NULL;
  qp->length=0;
}
