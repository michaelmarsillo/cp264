/*
--------------------------------------------------
Project: a9q3
File:    heap.h
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#ifndef HEAP_H
#define HEAP_H

typedef int KEYTYPE;
typedef int VALUETYPE;

typedef struct {
  KEYTYPE key;
  VALUETYPE value;
} HEAPDATA;

typedef struct heap {
  unsigned int size;
  unsigned int capacity;
  HEAPDATA *hda;
} HEAP;

HEAP *new_heap(int capacity);

void heap_insert(HEAP *heap, HEAPDATA data);

HEAPDATA heap_find_min(HEAP *heap);

HEAPDATA heap_extract_min(HEAP *heap);

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key);

int heap_search_value(HEAP *heap, VALUETYPE val);

void heap_clean(HEAP **heapp);

void heap_sort(HEAPDATA *arr, int n);

#endif
