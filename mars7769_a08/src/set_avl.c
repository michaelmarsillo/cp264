/*
--------------------------------------------------
Project: a8q2
File:    set_avl.h
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/


#include "string.h"
#include "avl.h"
#include "set_avl.h"

/**
 * returns the number of elements in the set
 */
int set_size(SET *s) {
    return s->size;
}

/**
 * Returns 1 if set s contains element e; otherwise 0.
 */
int set_contain(SET *s, char *e) {
    AVLNODE *node = avl_search(s->root, e);
    return node != NULL ? 1 : 0;
}

/**
 * Add element e into set s.
 */
void set_add(SET *s, char *e) {
    if (set_contain(s, e)) return;  // Do nothing if the element already exists

    RECORD new_data;

    strncpy(new_data.name, e, sizeof(new_data.name) - 1);
    new_data.name[sizeof(new_data.name) - 1] = '\0';
    new_data.score = 0.0;

    avl_insert(&s->root, new_data);
    s->size++;
}

/**
 * Remove element e from set s.
 */
void set_remove(SET *s, char *e) {
    if (!set_contain(s, e)) return;
    avl_delete(&s->root, e);
    s->size--;
}

/**
 * Clear the set, clearing the underlying AVL tree, and reset fields of s.
 */
void set_clean(SET *s) {
    avl_clean(&s->root);
    s->size = 0;
}
