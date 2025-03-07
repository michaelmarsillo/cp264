/*
 -------------------------------------------------------
 About:    queue and stack DS implementation
 Author:   HBF
 Version:  2025-02-23
 -------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"

void enqueue(QUEUE *qp, void *data) {
	if (qp && data) {
		NODE *p = (NODE*) malloc(sizeof(NODE));
		if (p != NULL) {
			p->data = data;
			p->next = NULL;

			if (qp->front == NULL) {
				qp->front = p;
				qp->rear = p;
			} else {
				(qp->rear)->next = p;
				qp->rear = p;
			}
		}
	}
}

void *dequeue(QUEUE *qp) {
	void *r = NULL;
	if (qp && qp->front) {
		NODE *p = qp->front;
		r = p->data;
		if (qp->front == qp->rear) {
			qp->front = NULL;
			qp->rear = NULL;
		} else {
			qp->front = p->next;
		}
		free(p);
	}
	return r;
}

void clean_queue(QUEUE *qp) {
	if (qp) {
		NODE *temp, *p = qp->front;
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		qp->front = NULL;
		qp->rear = NULL;
	}
}

void push(STACK *sp, void *data) {
	if (sp && data) {
		NODE *p = (NODE*) malloc(sizeof(NODE));
		if (p) {
			p->data = data;
			p->next = NULL;
			if (sp->top == NULL) {
				sp->top = p;
			} else {
				p->next = sp->top;
				sp->top = p;
			}
		}
	}
}

void *pop(STACK *sp) {
	void *r = NULL;
	if (sp && sp->top) {
		NODE *p = sp->top;
		r = p->data;
		sp->top = p->next;
		free(p);
	}
	return r;
}

void clean_stack(STACK *sp) {
	if (sp) {
		NODE *temp, *p = sp->top;
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		sp->top = NULL;
	}
}

