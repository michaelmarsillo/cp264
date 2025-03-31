/*
--------------------------------------------------
Project: a9q1
File:    hash.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


/* Search the hash table and return the pointer of found hnode
 * @param ht - pointer to a HASHTABLE
 * @param name - key to search
 * @return - pointer to the found HNODE, otherwise NULL
 */

HNODE *hashtable_search(HASHTABLE *ht, char *name) {
	// your code
    // calculate the hash index
    int index = hash(name, ht->size);

    // start at the beginning of the linked list at the calculated index
    HNODE *current = ht->hna[index];

    // traverse the linked list to find the node with matching name
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            // found a match, return the node
            return current;
        }
        current = current->next;
    }

    // no match found
    return NULL;
}


/* Insert key value data into HASHTABLE.
 * @param ht - pointer to a HASHTABLE
 * @param data - data to insert
 * #return - when keyed data exists, update its value and return 0;
 *           otherwise insert into the hash table and return 1
 */

int hashtable_insert(HASHTABLE *ht, DATA data) {
	// your code
    // search if the key already exists
    HNODE *existing = hashtable_search(ht, data.name);

    if (existing != NULL) {
        // key already exists, update the value
        existing->data.value = data.value;
        return 0;  // return 0 to indicate update
    } else {
        // key doesn't exist, create a new node
        HNODE *new_node = (HNODE *)malloc(sizeof(HNODE));
        if (new_node == NULL) {
            // handle memory allocation failure
            return -1;
        }

        // copy data to the new node
        new_node->data = data;

        // calculate the hash index
        int index = hash(data.name, ht->size);

        // insert at the beginning of the linked list (prepend)
        new_node->next = ht->hna[index];
        ht->hna[index] = new_node;

        // update the count of elements in the hash table
        ht->count++;

        return 1;  // return 1 to indicate insertion
    }
}

/* Delete hashnode by key.
 * @param ht - pointer to a HASHTABLE
 * @param name - name key for deletion
 * @return - if the named data exists, delete it and return 1; otherwise return 0.
 */

int hashtable_delete(HASHTABLE *ht, char *name) {
	// your code
    // calculate the hash index
    int index = hash(name, ht->size);

    // get the head of the linked list at the calculated index
    HNODE *current = ht->hna[index];
    HNODE *previous = NULL;

    // traverse the linked list to find the node with matching name
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            // found the node to delete

            if (previous == NULL) {
                // the node to delete is the head of the list
                ht->hna[index] = current->next;
            } else {
                // the node to delete is in the middle or end of the list
                previous->next = current->next;
            }

            // free the memory of the deleted node
            free(current);

            // update the count of elements in the hash table
            ht->count--;

            return 1;  // return 1 to indicate successful deletion
        }

        // move to the next node
        previous = current;
        current = current->next;
    }

    // no matching node found
    return 0;  // return 0 to indicate no deletion
}


int hash(char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash += *key++;
    }
    return hash % size;
}

HASHTABLE *new_hashtable(int size) {
    HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    ht->hna = (HNODE**) malloc(sizeof(HNODE**) * size);
    int i;
    for (i = 0; i < size; i++)
        *(ht->hna + i) = NULL;

    ht->size = size;
    ht->count = 0;
    return ht;
}


void hashtable_clean(HASHTABLE **htp) {
    if (*htp == NULL)
        return;
    HASHTABLE *ht = *htp;
    HNODE *p, *temp;
    int i;
    for (i = 0; i < ht->size; i++) {
        p = ht->hna[i];
        while (p) {
            temp = p;
            p = p->next;
            free(temp);
        }
        ht->hna[i] = NULL;
    }
    free(ht->hna);
    ht->hna = NULL;
    *htp = NULL;
}
