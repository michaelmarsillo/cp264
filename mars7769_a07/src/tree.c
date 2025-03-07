/*
--------------------------------------------------
Project: a7q1
File:    tree.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"

/* Compute and return the TPROPS value of a tree.
 * @param root - pointer to the root of a tree
 * @return - number of nodes and height in TPROPS type.
 */

TPROPS tree_property(TNODE *root) {
	// your code
    if (root == NULL) {
        return (TPROPS){0, -1}; // Empty tree has height -1
    }

    TPROPS left = tree_property(root->left);
    TPROPS right = tree_property(root->right);

    TPROPS result;
    result.order = 1 + left.order + right.order; // Total nodes
    result.height = 1 + (left.height > right.height ? left.height : right.height); // Max height

    return result;
}


/* Display the node data of the tree in pre-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */

void preorder(TNODE *root) {
	// your code
    if (root) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

/* Display the node data of the tree in in-order and format "%c".
 *
 *  @param root - pointer to the root of a tree
 */

void inorder(TNODE *root) {
	// your code
    if (root) {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

/* Display the node data of the tree in post-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */

void postorder(TNODE *root) {
	// your code
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

/* Display the node data of the tree in breadth-first-order and format "%c ".
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 */

void bforder(TNODE *root) {
	// your code
    if (root == NULL) return;

    QUEUE queue = {0};
    enqueue(&queue, root);

    while (queue.front) {
        TNODE *current = dequeue(&queue);
        printf("%c ", current->data);

        if (current->left) enqueue(&queue, current->left);
        if (current->right) enqueue(&queue, current->right);
    }
}

/* Search by key using breadth-first-search algorithm
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */

TNODE *bfs(TNODE *root, char val) {
	// your code
    if (root == NULL) return NULL;

    QUEUE queue = {0};
    enqueue(&queue, root);

    while (queue.front) {
        TNODE *current = dequeue(&queue);
        if (current->data == val) return current;

        if (current->left) enqueue(&queue, current->left);
        if (current->right) enqueue(&queue, current->right);
    }
    return NULL;
}

/* Search by key using depth-first-search algorithm.
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */

TNODE *dfs(TNODE *root, char val) {
	// your code
    if (root == NULL) return NULL;

    STACK stack = {0};
    push(&stack, root);

    while (stack.top) {
        TNODE *current = pop(&stack);
        if (current->data == val) return current;

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
    return NULL;
}


// the following functions are given, need to add to your program.

TNODE *tree_node(char val) {
    TNODE *np = (TNODE *) malloc(sizeof(TNODE));
    if (np != NULL) {
        np->data = val;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void clean_tree(TNODE **rootp) {
    TNODE *p = *rootp;
    if (p) {
        if (p->left)
            clean_tree(&p->left);
        if (p->right)
            clean_tree(&p->right);
        free(p);
    }
    *rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
    if (*rootp == NULL) {
        *rootp = tree_node(val);
    } else {
        QUEUE queue = { 0 };
        TNODE *p;
        enqueue(&queue, *rootp);
        while (queue.front) {
            p = dequeue(&queue);
            if (p->left == NULL) {
                p->left = tree_node(val);
                break;
            } else {
                enqueue(&queue, p->left);
            }

            if (p->right == NULL) {
                p->right = tree_node(val);
                break;
            } else {
                enqueue(&queue, p->right);
            }
        }
    }
}
