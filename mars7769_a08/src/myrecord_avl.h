/*
--------------------------------------------------
Project: a8q3
File:    set_avl.h
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#ifndef MYRECORD_AVL_H
#define MYRECORD_AVL_H

#include "avl.h"

/*  This structure holds the root pointer of AVL tree data structure,
 *  and count, mean and stddev of the data.score in the AVL tree.
 */

typedef struct {
    AVLNODE *root;
    int count;
    float mean;
    float stddev;
} AVLDS;


void avl_merge(AVLNODE **dest_rootp, AVLNODE **source_rootp);

void avlds_merge(AVLDS *dest, AVLDS *source);

void avlds_clean(AVLDS *ds);

void add_record(AVLDS *ds, RECORD data);

void remove_record(AVLDS *ds, char *name);


#endif
