/*
--------------------------------------------------
Project: a3q1
File:    mystring.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/
#include "mystring.h"


/**
 * Count the number words of given simple string. A word starts with an English charactor end with a charactor of space, tab, comma, or period.
 *
 * @param s - char pointer to a string
 * @return - return the number of words.
 */

int str_words(char *s) {
// your code
	if (s == 0) {
		return -1;
	}
	int count = 0;
	// set the pointer p to point to s
	char *p = s;
	while (*p) {
		// check if we are currently at a letter
		if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			// check if we are at the first character getting passed through (p == s)
			// or the previous character is the end of a word to count it as a new word
			if (p == s || *(p - 1) == ' ' || *(p - 1) == '\t' || *(p - 1) == ',' || *(p - 1) == '.') {
				count++;
			}
		}
		p++;
	}
	return count;

}


/**
 * Change every upper case English letter to its lower case of string passed by s
 *
 * @param s - char pointer to a string
 * @return - return the number of actual flips.
 */

int str_lower(char *s) {
// your code
	if (s==0){
		return -1;
	}
	int count = 0 ;
	// set the pointer p to point to s
	char *p = s;
	while (*p) {
		// check if we have an upper case letter in the string passed
		if (*p >= 'A' && *p <= 'Z') {
			// use ASC values to convert to lower case
			*p = *p + 32;
			count++;

		}
		p++;
	}
	return count;


}

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a string
 */

void str_trim(char *s) {
// your code
	// read pointer
	char *p = s;
	// write pointer
	char *dp = s;

	while (*p) {
		// if *p is not a space add it to our *dp
		// if p has moved passed the first character of s
		// and the previous character is not a space, add it as well
		if (*p != ' ' || (p > s && *(p-1) != ' ')) {
			*dp = *p;
			dp++;
		}
		p++;
	}
	// if the last character is a space add '\0' to the end to remove trailing spaces
	if (dp > s && *(dp-1) == ' ') {
		*(dp -1) = '\0';
	} else {
		*dp = '\0';
	}


}
