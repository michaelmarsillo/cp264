/*
--------------------------------------------------
Project: a9q3
File:    heap.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int cmp(KEYTYPE a, KEYTYPE b) {
  int r = 0;
  if (a < b) r = -1;
  else if (a > b) r = 1;
  return r;
}

HEAP *new_heap(int capacity)
{
  HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
  if (hp == NULL) return NULL;
  hp->hda = (HEAPDATA *) malloc(sizeof(HEAPDATA) * capacity);
  if ( hp->hda == NULL) { free(hp); return NULL; };
  hp->capacity = capacity;
  hp->size = 0;
  return hp;
}

// you may add this function to be used other functions.
int heapify_up(HEAPDATA *hda, int index) {
	// your code
    if (index <= 0) return index;

    int parent = (index - 1) / 2;

    if (hda[index].key < hda[parent].key) {
        // swap the nodes
        HEAPDATA temp = hda[index];
        hda[index] = hda[parent];
        hda[parent] = temp;

        // continue heapifying up
        return heapify_up(hda, parent);
    }

    return index;
}

// you may add this function to be used other functions.
int heapify_down(HEAPDATA *hda, int n, int index) {
	// your code
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // find the smallest among index, left child and right child
    if (left < n && hda[left].key < hda[smallest].key)
        smallest = left;

    if (right < n && hda[right].key < hda[smallest].key)
        smallest = right;

    // if the smallest is not the current index, swap and continue heapifying down
    if (smallest != index) {
        HEAPDATA temp = hda[index];
        hda[index] = hda[smallest];
        hda[smallest] = temp;

        // continue heapifying down
        return heapify_down(hda, n, smallest);
    }

    return index;
}

/* Insert the given HEAPDADA data into a heap. When the heap size is equal to the capacity,
 * expand data array by doubling its length and copy the data of old array to the new array in case of need,
 * then insert the data into the heap array.
 * @param heap - pointer to the heap.
 * @param data - data to be inserted.
 */

void heap_insert(HEAP *heap, HEAPDATA new_node) {
	// your code
    // check if we need to expand the heap
    if (heap->size == heap->capacity) {
        // double the capacity
        int new_capacity = heap->capacity * 2;
        HEAPDATA *new_array = (HEAPDATA *) malloc(sizeof(HEAPDATA) * new_capacity);

        if (new_array == NULL) return; // memory allocation failed

        // copy the old data to the new array
        for (int i = 0; i < heap->size; i++) {
            new_array[i] = heap->hda[i];
        }

        // free the old array and update heap properties
        free(heap->hda);
        heap->hda = new_array;
        heap->capacity = new_capacity;
    }

    // insert the new node at the end of the heap
    heap->hda[heap->size] = new_node;
    heap->size++;

    // restore the heap property by heapifying up
    heapify_up(heap->hda, heap->size - 1);
}


/* Get the HEAPDADA data of minimum key.
 * @param heap - pointer to the heap.
 * @return - the minimum key HEAPDATA
 */

HEAPDATA heap_find_min(HEAP *heap) {
	// your code
    // The minimum element is always at the root (index 0)
    if (heap->size > 0) {
        return heap->hda[0];
    } else {
        // Return an empty HEAPDATA if the heap is empty
        HEAPDATA empty = {0, 0};
        return empty;
    }
}

/* Get the minimum key HEAPDADA data and delete it from the heap.
 * When the heap->size <= (heap->capacity)/4 and heap->capacity>4, shrink the HEAPDATA array by half.
 * @param heap - pointer to the heap.
 * @return - the minimum key HEAPDATA
 */

HEAPDATA heap_extract_min(HEAP *heap) {
	// your code
    // save the minimum element
    HEAPDATA min = heap_find_min(heap);

    if (heap->size == 0) {
        return min;
    }

    // replace the root with the last element
    heap->hda[0] = heap->hda[heap->size - 1];
    heap->size--;

    // restore the heap property
    if (heap->size > 0) {
        heapify_down(heap->hda, heap->size, 0);
    }

    // check if we need to shrink the array
    if (heap->size <= (heap->capacity / 4) && heap->capacity > 4) {
        // shrink the array by half
        int new_capacity = heap->capacity / 2;
        HEAPDATA *new_array = (HEAPDATA *) malloc(sizeof(HEAPDATA) * new_capacity);

        if (new_array == NULL) return min; // Memory allocation failed

        // copy the data to the new array
        for (int i = 0; i < heap->size; i++) {
            new_array[i] = heap->hda[i];
        }

        // free the old array and update heap properties
        free(heap->hda);
        heap->hda = new_array;
        heap->capacity = new_capacity;
    }

    return min;
}

/* Changes heap->hda[index].key to new_key, heapify, return the index of new position of the new_key element.
 * @param heap - pointer to the heap.
 * @param index - index of HEAPDATA for key changing.
 * @param new_kay - key value to to be changed.
 * @return - position index of the new_key element.
 */

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
	// your code
    if (index < 0 || index >= heap->size) {
        return -1; // invalid index
    }

    KEYTYPE old_key = heap->hda[index].key;
    heap->hda[index].key = new_key;

    int new_index;

    // if the new key is smaller, heapify up
    if (new_key < old_key) {
        new_index = heapify_up(heap->hda, index);
    } else if (new_key > old_key) {
        // if the new key is larger, heapify down
        new_index = heapify_down(heap->hda, heap->size, index);
    } else {
        new_index = index; // key didn't change
    }

    return new_index;
}

/* Find and return the index of the first HEAPDATA data such that data.value == val.
 * @param heap - pointer to the heap.
 * @param val -  match value for search.
 * @return - position index of HEAPDATA data if found, otherwise -1.
 */

int heap_search_value(HEAP *heap, VALUETYPE val) {
	// your code
    // linear search through the heap array to find the value
    for (int i = 0; i < heap->size; i++) {
        if (heap->hda[i].value == val) {
            return i;
        }
    }

    return -1; // value not found
}

/* Sort HEAPDATA array in place in decreasig order of HEAPDATA key.
 * @param *arr - array pointer of HEAPDATA array
 * @param n - length of the input array.
 */

void heap_sort(HEAPDATA *arr, int n){
	// your code
    for (int i = n / 2 - 1; i >= 0; i--) {
        // use a modified heapify_down for max heap
        int largest = i;
        int done = 0;

        while (!done) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            largest = i;

            // find the largest among i, left child and right child
            if (left < n && arr[left].key > arr[largest].key)
                largest = left;

            if (right < n && arr[right].key > arr[largest].key)
                largest = right;

            // if largest is not i, swap and continue
            if (largest != i) {
                HEAPDATA temp = arr[i];
                arr[i] = arr[largest];
                arr[largest] = temp;

                i = largest; // continue heapifying down
            } else {
                done = 1; // done with this subtree
            }
        }
    }

    // extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // move current root (max element) to the end
        HEAPDATA temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // call max heapify on the reduced heap
        int largest = 0;
        int j = 0;
        int done = 0;

        while (!done) {
            int left = 2 * j + 1;
            int right = 2 * j + 2;
            largest = j;

            if (left < i && arr[left].key > arr[largest].key)
                largest = left;

            if (right < i && arr[right].key > arr[largest].key)
                largest = right;

            if (largest != j) {
                temp = arr[j];
                arr[j] = arr[largest];
                arr[largest] = temp;

                j = largest;
            } else {
                done = 1;
            }
        }
    }
}

void heap_clean(HEAP **heapp) {
  if (heapp) {
    HEAP *heap = *heapp;
    if (heap->capacity > 0) {
      heap->capacity = 0;
      heap->size = 0;
      free(heap->hda);
      free(heap);
    }
    *heapp = NULL;
  }
}
