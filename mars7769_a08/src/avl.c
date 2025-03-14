/*
--------------------------------------------------
Project: a8q1
File:    avl.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"


AVLNODE *avl_node(RECORD data)
{
  AVLNODE *np = (AVLNODE *)malloc(sizeof(AVLNODE));
  if (np)
  {
    np->data = data;
    np->height = 1;
    np->left = NULL;
    np->right = NULL;
  }
  return np;
}


int max(int a, int b)
{
  return (a > b)? a : b;
}


int height(AVLNODE *np) {
	// your code
  if (np == NULL) {
    return 0;
  }
  return np->height;
}

int balance_factor(AVLNODE *np) {
	// your code
  if (np == NULL) {
    return 0;
  }
  return height(np->left) - height(np->right);
}

AVLNODE *rotate_left(AVLNODE *np) {
	// your code
  AVLNODE *new_root = np->right;
  AVLNODE *temp = new_root->left;

  // perform rotation
  new_root->left = np;
  np->right = temp;

  // update heights
  np->height = max(height(np->left), height(np->right)) + 1;
  new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

  return new_root;
}

AVLNODE *rotate_right(AVLNODE *root) {
	// your code
  AVLNODE *new_root = root->left;
  AVLNODE *temp = new_root->right;

  // perform rotation
  new_root->right = root;
  root->left = temp;

  // update heights
  root->height = max(height(root->left), height(root->right)) + 1;
  new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

  return new_root;
}

AVLNODE *extract_smallest_node(AVLNODE **rootp) {
  AVLNODE *p = *rootp, *parent = NULL;
  if (p) {
    while (p->left) {
      parent = p;
      p = p->left;
    }
    if (parent == NULL)
      *rootp = p->right;
    else
      parent->left = p->right;

    p->left = NULL;
    p->right = NULL;
  }
  return p;
}

void avl_insert(AVLNODE **rootp, RECORD data) {
  // 1. Perform the normal BST insertion
  if (*rootp == NULL) {
    *rootp = avl_node(data);
  } else {
    if (strcmp(data.name, (*rootp)->data.name) < 0) {
      avl_insert(&(*rootp)->left, data);
    } else if (strcmp(data.name, (*rootp)->data.name) > 0) {
      avl_insert(&(*rootp)->right, data);
    }
  }

  // 2. Update height of the current node
  (*rootp)->height = max(height((*rootp)->left), height((*rootp)->right)) + 1;

  // 3. Get the balance factor of this node
  int balance = balance_factor(*rootp);

  // 4. Rebalance the tree if needed

  // left heavy case
  if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) < 0) {
    *rootp = rotate_right(*rootp);
  }
  // right heavy case
  else if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) > 0) {
    *rootp = rotate_left(*rootp);
  }
  // left right case
  else if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) > 0) {
    (*rootp)->left = rotate_left((*rootp)->left);
    *rootp = rotate_right(*rootp);
  }
  // right left case
  else if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) < 0) {
    (*rootp)->right = rotate_right((*rootp)->right);
    *rootp = rotate_left(*rootp);
  }
}

void avl_delete(AVLNODE **rootp, char *name) {
  AVLNODE *root = *rootp;
  AVLNODE *np;

  if (root == NULL) return;

  // 1. Perform the normal BST deletion
  if (strcmp(name, root->data.name) == 0) {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      *rootp = NULL;
    } else if (root->left != NULL && root->right == NULL) {
      np = root->left;
      free(root);
      *rootp = np;
    } else if (root->left == NULL && root->right != NULL) {
      np = root->right;
      free(root);
      *rootp = np;
    } else if (root->left != NULL && root->right != NULL) {
      np = extract_smallest_node(&root->right);
      np->left = root->left;
      np->right = root->right;
      free(root);
      *rootp = np;
    }
  } else {
    if (strcmp(name, root->data.name) < 0) {
      avl_delete(&root->left, name);
    } else {
      avl_delete(&root->right, name);
    }
  }

  // If the tree had only one node, return
  if (*rootp == NULL) return;

  // 2. Update height of the current node
  root = *rootp;
  root->height = max(height(root->left), height(root->right)) + 1;

  // 3. Get the balance factor of this node
  int balance = balance_factor(root);

  // 4. Rebalance the tree if needed
  // Left heavy case
  if (balance > 1 && balance_factor(root->left) >= 0) {
    *rootp = rotate_right(root);
  }
  // right heavy case
  else if (balance < -1 && balance_factor(root->right) <= 0) {
    *rootp = rotate_left(root);
  }
  // left right case
  else if (balance > 1 && balance_factor(root->left) < 0) {
    root->left = rotate_left(root->left);
    *rootp = rotate_right(root);
  }
  // right left case
  else if (balance < -1 && balance_factor(root->right) > 0) {
    root->right = rotate_right(root->right);
    *rootp = rotate_left(root);
  }
}

AVLNODE *avl_search(AVLNODE *root, char *name) {
	// your code
  if (root == NULL || strcmp(root->data.name, name) == 0) {
    return root;
  }

  if (strcmp(name, root->data.name) < 0) {
    return avl_search(root->left, name);
  } else {
    return avl_search(root->right, name);
  }
}


void avl_clean(AVLNODE **rootp) {
  AVLNODE *root = *rootp;
  if (root) {
    if (root->left)
      avl_clean(&root->left);
    if (root->right)
      avl_clean(&root->right);
    free(root);
  }
  *rootp = NULL;
}
