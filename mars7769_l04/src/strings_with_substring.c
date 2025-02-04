/**
 * -------------------------------------
 * @file  strings_with_substring.c
 * Lab 4 Source Code File
 * -------------------------------------
 * @author Michael Marsillo, 169057769, mars7769@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"

void strings_with_substring(strings_array *data, char *substr) {

    // your code here
	for (int i = 0; i < data->lines; i++) {
		if (strstr(data->strings[i], substr) != NULL) {
			printf("%s\n", data->strings[i]);
		}
	}


}
