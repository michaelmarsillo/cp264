/*
--------------------------------------------------
Project: a4q1
File:    mysort.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include "mysort.h"

// swap pointers
void swap(void **x, void **y) {
     void *temp = *y;
     *y = *x;
     *x = temp;
}

// a compare floating values pointed by void pointers.
int cmp(void *x, void *y) {
   float a = *(float*)x;
   float b = *(float*)y;
     if (a > b) return 1;
     else if (a < b) return -1;
     else return 0;
}

/**
 * Use selection sort algorithm to sort array of pointers such that their pointed values
 * are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 */

void select_sort(void *a[], int left, int right)
{
// your code
	for (int i = left; i < right; i++) {

		int minind = i;
		for (int j = i + 1; j <= right; j++) {
			if (cmp(a[j], a[minind]) < 0) {
				minind = j;
			}
		}
		if (minind != i) {
				swap((void**)&a[i], (void**)&a[minind]);
	}

}
}


/**
 * Use quick sort algorithm to sort array of pointers such that their pointed values
 * are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 */

void quick_sort(void *a[], int left, int right)
{
// your code
	if (left>= right) return;

	void *pivot = a[right];
	int i = left - 1;

	for (int j = left; j < right; j++) {
		if (cmp(a[j], pivot) < 0 ) {
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i + 1], &a[right]);
	int pivot_index = i + 1;

	quick_sort(a, left, pivot_index -1);
	quick_sort(a, pivot_index +1, right);
}


/**
 * Use either selection or quick sort algorithm to sort array of pointers such that their pointed values
 * are in order defined by the given comparison function
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 * @param (*cmp) - pointer to a comparison function used to compaire pointers by their pointed values.
 */

void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*) )
{
// your code
	if (left>= right) return;

		void *pivot = a[right];
		int i = left - 1;

		for (int j = left; j < right; j++) {
			if (cmp(a[j], pivot) < 0 ) {
				i++;
				swap(&a[i], &a[j]);
			}
		}
		swap(&a[i + 1], &a[right]);
		int pivot_index = i + 1;

		my_sort(a, left, pivot_index - 1, cmp);
		my_sort(a, pivot_index + 1, right, cmp);
}
