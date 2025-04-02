/*
--------------------------------------------------
File:    heap.c
About:   implementation of heap.h
Author:  HBF  
Version: 2025-03-13
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

/* This returns -1 if a<b, 0 if a=b, 1 if a>b
 * */
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

int heapify_up(HEAPDATA *hda, int index) {
  int parent; 
  HEAPDATA temp;
  while (index > 0) {
    parent = (index - 1) >> 1;
    if (cmp(hda[parent].key, hda[index].key)<=0) break;
	else {
	  temp = hda[index];
      hda[index] = hda[parent];
	  hda[parent] = temp;
	  index = parent;
	}
  }
  return index;
}

int heapify_down(HEAPDATA *hda, int n, int index) {
  int child; 
  HEAPDATA temp;
  while (index < n) {
    child = (index << 1) + 1;
    if (child >= n) break;
    if ((child + 1 < n) && cmp(hda[child + 1].key, hda[child].key)<=0) child++;
    if (cmp(hda[index].key, hda[child].key)<=0) break;
	temp = hda[index];
	hda[index] = hda[child];
	hda[child] = temp;
	index = child;
  }
  return index;
}

void heap_insert(HEAP *heap, HEAPDATA new_node)
{
  // Double the array length if it is overflow. 
  if (heap->size == heap->capacity)
  {
    heap->capacity <<= 1;
    HEAPDATA *temp = realloc(heap->hda, sizeof(HEAPDATA) * heap->capacity);
      if (temp) {
      heap->hda = temp;
    } else {
      temp = malloc(sizeof(HEAPDATA) * heap->capacity);
      if (temp) {
        memcpy(temp, heap->hda, sizeof(HEAPDATA) * heap->size);
        free(heap->hda);
        heap->hda = temp;
      } else {
        printf("memory expansion failed\n");
        exit(1);
      }
    }
  }
  
  int index = heap->size;
  heap->hda[index] = new_node;
  heapify_up(heap->hda, index);
  heap->size++;
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

HEAPDATA heap_find_min(HEAP *heap)
{
  return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap)
{
  HEAPDATA top = heap->hda[0];
  heap->size = heap->size - 1;
  heap->hda[0] = heap->hda[heap->size];
  heapify_down(heap->hda, heap->size, 0);
  // Shrink the array to a 1/2 if size <= capacity / 4
  if ((heap->size <= (heap->capacity >> 2)) && (heap->capacity > 4)) {
    heap->capacity >>= 1;
    heap->hda = realloc(heap->hda, sizeof(HEAPDATA) * heap->capacity);
  }
  return top;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key)
{
  KEYTYPE temp_key = heap->hda[index].key;
  heap->hda[index].key = new_key;
  if ( temp_key > new_key) { 
    index = heapify_up(heap->hda, index);
  } else if ( temp_key < new_key) { 
    index = heapify_down(heap->hda, heap->size, index);
  } 
  return index;
}

int heap_search_value(HEAP *heap, VALUETYPE value) {
  int i, r = -1;
  for (i=0; i<heap->size; i++) {
    if (heap->hda[i].value == value) {r = i; break;}
  }
  return r;
}

void heap_sort(HEAPDATA *hda, int n) {
  int i; 
  for (i=n/2-1; i>=0; i--) {
     heapify_down(hda, n, i);
  }	  
  for (i=0; i<n-1; i++) {
	 HEAPDATA temp=hda[0];
     hda[0]=hda[n-1-i];
     hda[n-1-i] = temp;
	 heapify_down(hda, n-1-i, 0);
  }	  
}



