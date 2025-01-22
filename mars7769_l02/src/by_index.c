/**
 * -------------------------------------
 * @file  by_index.c
 * Lab 2 Index Functions Source Code File
 * -------------------------------------
 * @ Michael Marsillo, 169057769, mars7769@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "by_index.h"

void fill_values_by_index(int values[], int size) {

    for(int i = 0; i < size; i++) {
        values[i] = i + 1;
    }
}

void fill_squares_by_index(int values[], long int squares[], int size) {

    // your code here
	for(int i = 0; i < size; i++) {
		squares[i] = values[i] * values[i];
	}


}

void print_by_index(int values[], long int squares[], int size) {

    // your code here
	printf("Value  Square\n");
	printf("-----  ----------\n");
	for(int i = 0; i < size; i ++) {
		squares[i] = values[i] * values[i];
		printf("    %d           %ld\n", values[i], squares[i]);
	}



}
