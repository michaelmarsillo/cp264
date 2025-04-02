/*
--------------------------------------------------
Project: a10q2
File:    graph.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_stack.h"
#include "graph.h"


/* create and return a new adjacent list graph of order n */
GRAPH *new_graph(int order) {
  GRAPH *gp = malloc(sizeof(GRAPH));
  gp->nodes = malloc(order * sizeof(GNODE*));

  int i;
  for (i = 0; i < order; i++) {
    gp->nodes[i] = malloc(sizeof(GNODE));
    gp->nodes[i]->nid = i;
    strcpy(gp->nodes[i]->name, "null");
    gp->nodes[i]->neighbor = NULL;
  }

  gp->order = order;
  gp->size = 0;

  return gp;
}


/* Add edge (from, to, weight) to a graph. If edge (from, to) exists, update its weight by the new weight,
 * This indicates that if (from, to) does not exist, the new edge will be added to the end of the linked list.
*/
void insert_edge_graph(GRAPH *g, int from, int to, int weight) {
	// your code
    if (g == NULL || from < 0 || from >= g->order || to < 0 || to >= g->order) {
        return;  // invalid parameters
    }

    ADJNODE *current = g->nodes[from]->neighbor;
    ADJNODE *prev = NULL;

    // check if edge already exists
    while (current != NULL) {
        if (current->nid == to) {
            // edge exists, update weight
            current->weight = weight;
            return;
        }
        prev = current;
        current = current->next;
    }

    // edge doesn't exist, create a new one
    ADJNODE *new_node = (ADJNODE *)malloc(sizeof(ADJNODE));
    new_node->nid = to;
    new_node->weight = weight;
    new_node->next = NULL;

    // add to the end of the list
    if (prev == NULL) {
        g->nodes[from]->neighbor = new_node;
    } else {
        prev->next = new_node;
    }

    g->size++;  // increment size
}

/* Delete edge (from, to)*/
void delete_edge_graph(GRAPH *g, int from, int to) {
	// your code
    if (g == NULL || from < 0 || from >= g->order || to < 0 || to >= g->order) {
        return;  // invalid parameters
    }

    ADJNODE *current = g->nodes[from]->neighbor;
    ADJNODE *prev = NULL;

    // find the edge
    while (current != NULL && current->nid != to) {
        prev = current;
        current = current->next;
    }

    // if edge found, delete it
    if (current != NULL) {
        if (prev == NULL) {
            // the edge is the first in the list
            g->nodes[from]->neighbor = current->next;
        } else {
            // the edge is in the middle or at the end
            prev->next = current->next;
        }

        free(current);
        g->size--;  // decrement size
    }
}


/* Get and return the weight of edge (from, to) if exists, otherwise return INFINITY*/
int get_edge_weight(GRAPH *g, int from, int to) {
	// your code
    if (g == NULL || from < 0 || from >= g->order || to < 0 || to >= g->order) {
        return INFINITY;  // invalid parameters
    }

    ADJNODE *current = g->nodes[from]->neighbor;

    // find the edge
    while (current != NULL) {
        if (current->nid == to) {
            return current->weight;  // edge found, return weight
        }
        current = current->next;
    }

    return INFINITY;  // edge not found
}

/* Travere graph nodes in breadth-first-order using auxiliary queue */
void traverse_bforder(GRAPH *g, int nid) {
    if (g == NULL || nid < 0 || nid >= g->order) {
        return;  // invalid parameters
    }

    // create a queue for BFS
    QUEUE q = {NULL, NULL};

    // create array to mark visited nodes
    int *visited = (int *)calloc(g->order, sizeof(int));
    if (visited == NULL) {
        return;  // memory allocation failed
    }

    // mark the start node as visited and print it
    visited[nid] = 1;
    printf("(%d %s) ", nid, g->nodes[nid]->name);

    // convert int to void* for enqueue
    int *nid_ptr = (int *)malloc(sizeof(int));
    if (nid_ptr == NULL) {
        free(visited);
        return;  // memory allocation failed
    }
    *nid_ptr = nid;

    enqueue(&q, nid_ptr);

    // standard BFS traversal loop
    while (q.front != NULL) {
        int *current_node_ptr = (int *)dequeue(&q);
        int current_node = *current_node_ptr;
        free(current_node_ptr);  // free after use

        // visit all neighbors of the current node
        ADJNODE *neighbor = g->nodes[current_node]->neighbor;
        while (neighbor != NULL) {
            int neighbor_id = neighbor->nid;

            // if not visited, mark as visited, print, and enqueue
            if (!visited[neighbor_id]) {
                visited[neighbor_id] = 1;
                printf("(%d %s) ", neighbor_id, g->nodes[neighbor_id]->name);

                int *neighbor_ptr = (int *)malloc(sizeof(int));
                if (neighbor_ptr == NULL) {
                    free(visited);
                    clean_queue(&q);
                    return;  // memory allocation failed
                }
                *neighbor_ptr = neighbor_id;

                enqueue(&q, neighbor_ptr);
            }

            neighbor = neighbor->next;
        }
    }

    // clean up
    free(visited);
    clean_queue(&q);
}


// Use auxiliary stack data structure for the algorithm
void traverse_dforder(GRAPH *g, int nid) {
    if (g == NULL || nid < 0 || nid >= g->order) {
        return;  // invalid parameters
    }

    // create a stack for DFS
    STACK s = {NULL};

    // create array to mark visited nodes
    int *visited = (int *)calloc(g->order, sizeof(int));
    if (visited == NULL) {
        return;  // memory allocation failed
    }

    // push the start node onto the stack
    int *nid_ptr = (int *)malloc(sizeof(int));
    if (nid_ptr == NULL) {
        free(visited);
        return;  // memory allocation failed
    }
    *nid_ptr = nid;

    push(&s, nid_ptr);

    // standard DFS traversal loop
    while (s.top != NULL) {
        int *current_node_ptr = (int *)pop(&s);
        int current_node = *current_node_ptr;
        free(current_node_ptr);  // free after use

        // if not visited, visit it
        if (!visited[current_node]) {
            visited[current_node] = 1;
            printf("(%d %s) ", current_node, g->nodes[current_node]->name);

            // for DFS traversal in the correct order, we need to push neighbors in reverse order
            // first, collect all neighbors
            ADJNODE *neighbor = g->nodes[current_node]->neighbor;
            STACK temp_stack = {NULL};

            // push all unvisited neighbors to a temporary stack
            while (neighbor != NULL) {
                int neighbor_id = neighbor->nid;
                if (!visited[neighbor_id]) {
                    int *neighbor_ptr = (int *)malloc(sizeof(int));
                    if (neighbor_ptr == NULL) {
                        free(visited);
                        clean_stack(&s);
                        clean_stack(&temp_stack);
                        return;  // memory allocation failed
                    }
                    *neighbor_ptr = neighbor_id;
                    push(&temp_stack, neighbor_ptr);
                }
                neighbor = neighbor->next;
            }

            // pop from temporary stack and push to main stack
            while (temp_stack.top != NULL) {
                int *temp_ptr = (int *)pop(&temp_stack);
                push(&s, temp_ptr);
            }
        }
    }

    // clean up
    free(visited);
    clean_stack(&s);
}


/* Clean the graph by free all dynamically allocated memory*/
void clean_graph(GRAPH **gp) {
  int i;
  GRAPH *g = *gp;
  ADJNODE *temp, *ptr;
  for (i = 0; i < g->order; i++) {
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
    free(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
  *gp = NULL;
}

/* Display the graph*/
void display_graph(GRAPH *g) {
  if (g ) {
  printf("order %d ", g->order);
  printf("size %d ", g->size);
  printf("(from to weight) ");
  int i;
  ADJNODE *ptr;
  for (i = 0; i < g->order; i++) {
    //printf("\n%d:", g->nodes[i]->nid);
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      printf("(%d %d %d) ", i,  ptr->nid, ptr->weight);
      ptr = ptr->next;
    }
  }
  }
}
