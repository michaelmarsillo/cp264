/*
--------------------------------------------------
Project: a8q1
File:    avl.h
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#ifndef AVL_H
#define AVL_H

typedef struct record {
  char name[20];
  float score;
} RECORD;

typedef struct avlnode AVLNODE;

struct avlnode {
  RECORD data;
  int height;
  AVLNODE *left;
  AVLNODE *right;
};

AVLNODE *avl_node(RECORD data);

void avl_insert(AVLNODE **rootp, RECORD data);

void avl_delete(AVLNODE **rootp, char *key);

AVLNODE *avl_search(AVLNODE *root, char *key);

void avl_clean(AVLNODE **rootp);

int height(AVLNODE *root);

int balance_factor(AVLNODE *np);

AVLNODE *rotate_left(AVLNODE *np);

AVLNODE *rotate_right(AVLNODE *root);

#endif
