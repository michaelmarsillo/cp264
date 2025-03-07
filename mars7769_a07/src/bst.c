/*
--------------------------------------------------
Project: a7q2
File:    bst.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"



BSTNODE *bst_node(RECORD data);
BSTNODE *extract_smallest_node(BSTNODE **rootp);


/* Search the BST by search key matching with data.name
 *
 * @param root - pointer to tree root.
 * @param key - string of search key
 *
 * @return - pointer to matched node if found, otherwise NULL
 */

BSTNODE *bst_search(BSTNODE *root, char *key) {
	// your code
    if (root == NULL || strcmp(root->data.name, key) == 0)
        return root;

    if (strcmp(key, root->data.name) < 0)
        return bst_search(root->left, key);
    else
        return bst_search(root->right, key);
}


/* Insert a node of given record data into BST.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  -  record data for the new node.
 *
 */

void bst_insert(BSTNODE **rootp, RECORD data) {
	// your code
    if (*rootp == NULL) {
        *rootp = bst_node(data);
        return;
    }

    if (strcmp(data.name, (*rootp)->data.name) < 0)
        bst_insert(&((*rootp)->left), data);
    else
        bst_insert(&((*rootp)->right), data);
}

/* Delete a node of data.name matched with given key.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */

void bst_delete(BSTNODE **rootp, char *key) {
	// your code
    if (*rootp == NULL)
        return;

    if (strcmp(key, (*rootp)->data.name) < 0)
        bst_delete(&((*rootp)->left), key);
    else if (strcmp(key, (*rootp)->data.name) > 0)
        bst_delete(&((*rootp)->right), key);
    else {
        BSTNODE *temp;
        if ((*rootp)->left == NULL) {
            temp = *rootp;
            *rootp = (*rootp)->right;
            free(temp);
        } else if ((*rootp)->right == NULL) {
            temp = *rootp;
            *rootp = (*rootp)->left;
            free(temp);
        } else {
            temp = extract_smallest_node(&((*rootp)->right));
            (*rootp)->data = temp->data;
            free(temp);
        }
    }
}


BSTNODE *bst_node(RECORD data) {
    BSTNODE *np = (BSTNODE *) malloc(sizeof(BSTNODE));
    if (np) {
        memcpy(np, &data, sizeof(BSTNODE));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void bst_clean(BSTNODE **rootp) {
    BSTNODE *root = *rootp;
    if (root) {
        if (root->left)
            bst_clean(&root->left);
        if (root->right)
            bst_clean(&root->right);
        free(root);
    }
    *rootp = NULL;
}

BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    BSTNODE *p = *rootp, *parent = NULL;
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
