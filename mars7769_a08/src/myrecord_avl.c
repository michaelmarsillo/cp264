/*
--------------------------------------------------
Project: a8q3
File:    set_avl.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "avl.h"
#include "myrecord_avl.h"


/*  Merge source AVL tree into destination AVL tree. No change to source tree.
 *  @parame rootp_dest   - pointer to pointer of root of destination tree
 *  @parame rootp_source - pointer to pointer of root of source tree
 */

void avl_merge(AVLNODE **dest_rootp, AVLNODE **source_rootp) {
	// your code
    if (*source_rootp != NULL) {
        avl_merge(dest_rootp, &(*source_rootp)->left);
        avl_insert(dest_rootp, (*source_rootp)->data);
        avl_merge(dest_rootp, &(*source_rootp)->right);
    }
}


/*  Merge source AVLDS to destination AVLDS, use aggregation algorithm to
 *  compute the stats info, can clean source AVLDS.
 *  @parame source - pointer to the source AVLDS
 *  @parame dest - pointer to the destination AVLDS
 */
void avlds_merge(AVLDS *dest, AVLDS *source) {
	// your code
    avl_merge(&(dest->root), &(source->root));

    int new_count = dest->count + source->count;
    float new_mean = ((dest->mean * dest->count) + (source->mean * source->count)) / new_count;

    float new_stddev = sqrt(((dest->stddev * dest->stddev + dest->mean * dest->mean) * dest->count +
                             (source->stddev * source->stddev + source->mean * source->mean) * source->count) / new_count -
                            new_mean * new_mean);

    dest->count = new_count;
    dest->mean = new_mean;
    dest->stddev = new_stddev;

    avlds_clean(source);
}


/*  Clean its AVL tree and set count=0, mean=0, stddev=0
 *  @parame ds - pointer to the AVLDS
 */

void avlds_clean(AVLDS *ds) {
    avl_clean(&ds->root);
    ds->count = 0;
    ds->mean = 0;
    ds->stddev = 0;
}

// the following functions are adapted from a7q3
void add_record(AVLDS *tree, RECORD data) {
  if (avl_search(tree->root, data.name) == NULL) {
    avl_insert(&(tree->root), data);
    int count = tree->count;
    float mean = tree->mean;
    float stddev = tree->stddev;
    tree->count = count + 1;
    tree->mean =  (mean*count + data.score) / (count+1.0);
    tree->stddev = sqrt(data.score*data.score/(count+1.0) + (stddev * stddev + mean * mean) * (count/(count+1.0)) - tree->mean * tree->mean );
  } else {
    printf("record exits");
  }
}

void remove_record(AVLDS *tree, char *name) {
  AVLNODE *np = NULL;
  if ( (np = avl_search(tree->root, name)) != NULL) {
    float score = np->data.score;
    avl_delete(&(tree->root), name);
    float count = tree->count;
    float mean = tree->mean;
    float stddev = tree->stddev;
    tree->count = count - 1;
    if (count >= 3) {
      tree->mean =  (mean*count - score) / (count-1.0);
      tree->stddev = sqrt( (stddev * stddev + mean * mean) * (count/(count-1.0)) - score*score/(count-1.0) - tree->mean * tree->mean );
    }
    else if (count == 2) {
        tree->mean = mean*count - score;
        tree->stddev = 0;
   }
   else {
        tree->mean = 0;
        tree->stddev = 0;
    }
  } else {
    printf("record does not exit");
  }
}
