/*
--------------------------------------------------
Project: a3q2
File:    myword.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

#define MAX_LINE_LEN 1000
#define MAX_WORDS 1000


/*
 * Load word data from file, and insert words a directory represented by char array.
 *
 * @param  FILE *fp -   file pointer to an opened text file
 * @param *dictionary - char pointer to a char array where dictionary words are stored.
 *                      It's up to your design on how to store words in the char array.
 * @return - the number of words added into the dictionary.
 */

int create_dictionary(FILE *fp, char *dictionary) {
// your code
	char line[1000];
	    char delimiters[] = " .,\n\t\r";
	    char *token;

	    dictionary[0] = '\0';

	    int count = 0;
	    while (fgets(line, sizeof(line), fp) != NULL) {
	        token = strtok(line, delimiters);
	        while (token != NULL) {
	            str_lower(token);
	            str_trim(token);
	            strcat(dictionary, token);
	            strcat(dictionary, ",");
	            token = strtok(NULL, delimiters);
	            count++;

	        }

	    }

	    return count;

	}
/*
 * Determine if a given word is contained in the given dictionary.
 *
 * @param *dictionary -  char pointer to a char array of given dictionary.
 * @param *word  -  pointer to a given word.
 *
 * @return - TRUE if the word is in the dictionary, FALSE otherwise.
 */

BOOLEAN contain_word(char *dictionary, char *word) {
// your code
	 if (word == NULL || *word == '\0') {
	        return 0;

	    }
	    char temp[100] = "";
	    snprintf(temp, sizeof(temp), ",%s,", word);
	    if (strstr(dictionary, temp) != NULL) {
	        return TRUE;

	    } else {
	        return FALSE;

	    }

	}

/*
 * Process text data from a file for word statistic information of line count, word count, keyword count, and frequency of keyword.
 *
 * @param *fp -  FILE pointer of input text data file. .
 * @param *words  -  WORD array for keywords and their frequencies.
 * @param *dictionary  -  stop-word/common-word dictionary.
 *
 * @return - WORDSTATS value of processed word stats information.
 */

WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
// your code
	 WORDSTATS ws = {0};
	    char line[MAX_LINE_LEN];
	    char *token;
	    char delimiters[] = " .,\n\t\r";

	    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
	        ws.line_count++;
	        str_lower(line);
	        token = strtok(line, delimiters);
	        while (token != NULL) {
	            ws.word_count++;

	            if (contain_word(dictionary, token) == FALSE) {
	                int j = 0;
	                while (j < ws.keyword_count && strcmp(token, words[j].word) != 0) {
	                    j++;
	                }

	                if (j < ws.keyword_count) {
	                    words[j].count++;
	                } else {
	                    strcpy(words[j].word, token);
	                    words[j].count = 1;
	                    ws.keyword_count++;
	                }
	            }

	            token = strtok(NULL, delimiters);
	        }
	    }

	    return ws;
	}
