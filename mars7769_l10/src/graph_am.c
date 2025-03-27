/**
 * -------------------------------------
 * @file  graph_am.c
 * Adjacency Matrix Graph Code File
 * -------------------------------------
 * @author Michael Marsillo, 169057769, mars7769@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "graph_am.h"

// Initializes an adjacency matrix graph.
graph_am* graph_am_initialize(int size) {
    graph_am *source = malloc(sizeof *source);
    source->size = size;
    // Initialize values to zeroes.
    source->values = calloc(size * size, sizeof *source->values);
    return source;
}

void graph_am_free(graph_am **source) {
    // Free up the data array.
    free((*source)->values);
    (*source)->values = NULL;
    free(*source);
    *source = NULL;
    return;
}

int graph_am_add_vertice(graph_am *source, const graph_am_pair *pair) {
	int added = 0;

	// your code here
	// check if the pair values are within the valid range.
	if (pair->row >= 0 && pair->row < source->size && pair->col >= 0
			&& pair->col < source->size) {
		// check if the pair represents a loop.
		if (pair->row == pair->col) {
			*(source->values + pair->row * source->size + pair->col) = 2;
		} else {
			*(source->values + pair->row * source->size + pair->col) = 1;
			*(source->values + pair->col * source->size + pair->row) = 1;
		}
		added = 1;
	}
	return added;
}

int graph_am_remove_vertice(graph_am *source, const graph_am_pair *pair) {
	int removed = 0;

	// your code here
	// check if the pair values are within the valid range.
	if (pair->row >= 0 && pair->row < source->size && pair->col >= 0
			&& pair->col < source->size) {
		*(source->values + pair->row * source->size + pair->col) = 0;
		*(source->values + pair->col * source->size + pair->row) = 0;
		removed = 1;
	}
	return removed;
}

graph_am* graph_am_create(int size, const graph_am_pair pairs[], int count) {
	graph_am *source = graph_am_initialize(size);

	// your code here
	// add each pair to the graph.
	for (int i = 0; i < count; i++) {
		graph_am_add_vertice(source, &pairs[i]);
	}
	return source;
}

void graph_am_neighbours(const graph_am *source, int vertex, int vertices[],
		int *count) {

	// your code here
	*count = 0;
	// iterate through the adjacency matrix row for the given vertex.
	for (int i = 0; i < source->size; i++) {
		if (*(source->values + vertex * source->size + i) > 0) {
			vertices[(*count)++] = i;
		}
	}
}

int graph_am_degree(const graph_am *source, int vertex) {
	int connected = 0;

	// your code here
	// count the number of connections in the adjacency matrix row for the given vertex.
	for (int i = 0; i < source->size; i++) {
		connected += *(source->values + vertex * source->size + i);
	}
	return connected;
}

void graph_am_breadth_traversal(const graph_am *source, int vertex,
		int vertices[], int *count) {

	// your code here
	int visited[source->size];
	// initialize all vertices as not visited.
	for (int i = 0; i < source->size; i++) {
		visited[i] = 0;
	}
	int queue[source->size];
	int front = 0, rear = 0;
	queue[rear++] = vertex;
	visited[vertex] = 1;
	*count = 0;
	// process the queue until it is empty.
	while (front < rear) {
		int current = queue[front++];
		vertices[(*count)++] = current;
		// add all unvisited neighbours to the queue.
		for (int i = 0; i < source->size; i++) {
			if (*(source->values + current * source->size + i) > 0
					&& !visited[i]) {
				queue[rear++] = i;
				visited[i] = 1;
			}
		}
	}
}

void graph_am_depth_traversal(const graph_am *source, int vertex,
		int vertices[], int *count) {

	// your code here
	int visited[source->size];
	// initialize all vertices as not visited.
	for (int i = 0; i < source->size; i++) {
		visited[i] = 0;
	}
	int stack[source->size];
	int top = -1;
	stack[++top] = vertex;
	*count = 0;
	// process the stack until it is empty.
	while (top >= 0) {
		int current = stack[top--];
		if (!visited[current]) {
			vertices[(*count)++] = current;
			visited[current] = 1;
			// add all unvisited neighbours to the stack in reverse order.
			for (int i = 0; i < source->size; i++) {
				if (*(source->values + current * source->size + i) > 0
						&& !visited[i]) {
					stack[++top] = i;
				}
			}
		}
	}
}

// Prints the contents of an adjacency matrix graph.
void graph_am_print(const graph_am *source) {
    // Print the column numbers.
    printf("    ");

    for(int i = 0; i < source->size; i++)
        printf("%3d", i);
    printf("\n");
    printf("    ");
    for(int i = 0; i < source->size; i++)
        printf("---");
    printf("\n");

    // Print the row numbers and rows.
    for(int i = 0; i < source->size; i++) {
        printf("%3d|", i);

        for(int j = 0; j < source->size; j++) {
            // find item using offsets
            printf("%3d", *(source->values + i * source->size + j));
        }
        printf("\n");
    }
}
