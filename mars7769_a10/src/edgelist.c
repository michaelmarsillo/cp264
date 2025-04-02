/*
--------------------------------------------------
Project: a10q1
File:    edgelist.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "edgelist.h"


/* Create and return a new edge list graph*/
EDGELIST *new_edgelist() {
    EDGELIST *tp = malloc(sizeof(EDGELIST));
    tp->size = 0;
    tp->start = NULL;
    tp->end = NULL;
    return tp;
}


/* Add a new edge at the start of the linked list of edges*/
void insert_edge_end(EDGELIST *g, int from, int to, int weight) {
	// your code
    EDGENODE *new_node = malloc(sizeof(EDGENODE));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = NULL;

    if (g->end == NULL) {
        // empty list case
        g->start = new_node;
        g->end = new_node;
    } else {
        // add to the end
        g->end->next = new_node;
        g->end = new_node;
    }

    g->size++;
}


/* Add an new edge at the end of the linked list of edges */
void insert_edge_start(EDGELIST *g, int from, int to, int weight) {
	// your code
    EDGENODE *new_node = malloc(sizeof(EDGENODE));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = g->start;

    g->start = new_node;

    if (g->end == NULL) {
        // empty list case
        g->end = new_node;
    }

    g->size++;
}


/* Delete edge (from to) from the edgelist */
void delete_edge(EDGELIST *g, int from, int to) {
	// your code
    if (g == NULL || g->start == NULL) {
        return;  // empty list or NULL graph
    }

    EDGENODE *current = g->start;
    EDGENODE *previous = NULL;

    // find the edge to delete
    while (current != NULL) {
        if (current->from == from && current->to == to) {
            // found the edge to delete

            if (previous == NULL) {
                // deleting the first node
                g->start = current->next;

                // if it was also the last node, update end
                if (g->end == current) {
                    g->end = NULL;
                }
            } else {
                // deleting a middle or end node
                previous->next = current->next;

                // if deleting the last node, update end
                if (g->end == current) {
                    g->end = previous;
                }
            }

            free(current);
            g->size--;
            return;
        }

        previous = current;
        current = current->next;
    }
}


/* Get the weight of the graph */
int weight_edgelist(EDGELIST *g) {
    if (g == NULL) {
        return 0;
    }

    int total_weight = 0;
    EDGENODE *current = g->start;

    while (current != NULL) {
        total_weight += current->weight;
        current = current->next;
    }

    return total_weight;
}
void clean_edgelist(EDGELIST **gp) {
    EDGELIST *g = *gp;
    EDGENODE *temp, *p = g->start;
    while (p) {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(g);
    *gp = NULL;
}


void display_edgelist(EDGELIST *g) {
    if (g == NULL)
        return;
    printf("size %d ", g->size);
    printf("(from to weight) ");
    EDGENODE *p = g->start;
    while (p) {
        printf("(%d %d %d) ", p->from, p->to, p->weight);
        p = p->next;
    }
}
