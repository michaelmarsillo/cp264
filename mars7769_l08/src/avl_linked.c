/**
 * -------------------------------------
 * @file  avl_linked.c
 * Linked AVL Source Code File
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 * @author Michael Marsillo, 169057769, mars7769@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
// Includes
#include <stdio.h>
#include <stdlib.h>

#include "avl_linked.h"

// Local Functions

/**
 * Initializes a new AVL node with a copy of item.
 *
 * @param item
 * @return
 */
static avl_node* avl_node_initialize(const data_ptr item) {
	// Base case: add a new node containing a copy of item.
	avl_node *node = malloc(sizeof *node);
	node->item = malloc(sizeof *node->item);
	data_copy(node->item, item);
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/**
 * Helper function to determine the height of node - handles empty node.
 *
 * @param node - The node to process.
 * @return -  The height of the current node.
 */
static int avl_node_height(const avl_node *node) {
	int height = 0;

	if (node != NULL) {
		height = node->height;
	}
	return (height);
}

/**
 * Updates the height of a node. Its height is the max of the heights of its
 * child nodes, plus 1.
 *
 * @param node - The node to process.
 */
static void avl_update_height(avl_node *node) {
	int left_height = avl_node_height(node->left);
	int right_height = avl_node_height(node->right);

	if (left_height >= right_height) {
		node->height = left_height + 1;
	} else {
		node->height = right_height + 1;
	}
	return;
}

/**
 * Frees a node and its children.
 *
 * @param node - The node to process
 */
static void avl_free_aux(avl_node **node) {

	if (*node != NULL) {
		avl_free_aux(&(*node)->left);
		avl_free_aux(&(*node)->right);
		data_free(&(*node)->item);
		(*node)->item = NULL;
		free(*node);
		*node = NULL;
	}
	return;
}

/**
 * Determines whether the AVL is balanced.
 *
 * @param node - The node to process.
 * @return - difference in height of children of node.
 */
static int avl_balance(const avl_node *node) {
	return (avl_node_height(node->left) - avl_node_height(node->right));
}

/**
 * Performs a left rotation around node.
 *
 * @param node - the node to process
 * @return - pointer to new root of subtree
 */
static avl_node* avl_rotate_left(avl_node *node) {
    // set new root to right child
    avl_node *new_root = node->right;

    // move left subtree of new root to be the right subtree of old root
    node->right = new_root->left;

    // old root becomes left subtree of new root
    new_root->left = node;

    // update heights
    avl_update_height(node);
    avl_update_height(new_root);

    // return the new root
    return new_root;
}

/**
 * Performs a right rotation around node.
 *
 * @param node - the node to process
 * @return - pointer to new root of subtree
 */
static avl_node* avl_rotate_right(avl_node *node) {
    // left child becomes new root
    avl_node *new_root = node->left;

    // move the right subtree of new root to be the left subtree of the old root
    node->left = new_root->right;

    // old root becomes the right child of new root
    new_root->right = node;

    // update heights
    avl_update_height(node);
    avl_update_height(new_root);

    // return the new root of the subtree
    return new_root;
}

/**
 * Rebalances a node according to AVL rules.
 *
 * @param node - the node to process
 */
static void avl_rebalance(avl_node **node) {
    // calculate the balance factor of the node
    int balance = avl_balance(*node);

    // left heavy subtree (balance > 1)
    if (balance > 1) {
        // left-right case: double rotation needed
        if (avl_balance((*node)->left) < 0) {
            (*node)->left = avl_rotate_left((*node)->left);
        }
        // perform right rotation
        *node = avl_rotate_right(*node);
    }
    // right heavy subtree (balance < -1)
    else if (balance < -1) {
        // right-left case: double rotation needed
        if (avl_balance((*node)->right) > 0) {
            (*node)->right = avl_rotate_right((*node)->right);
        }
        // perform left rotation
        *node = avl_rotate_left(*node);
    }
    else {
        // tree is balanced, just update height
        avl_update_height(*node);
    }

    return;
}

/**
 * Inserts item into a AVL. Insertion must preserve the AVL definition.
 * Only one of item may be in source.
 *
 * @param source - pointer to a AVL.
 * @param node - node to process.
 * @param item - pointer to item to insert.
 * @return - true if the item is inserted, false otherwise.
 */
static bool avl_insert_aux(avl_linked *source, avl_node **node,
        const data_ptr item) {
    bool inserted = false;

    if (*node == NULL) {
        // base case: insert the new node here
        *node = avl_node_initialize(item);
        source->count++;
        inserted = true;
    } else {
        int comp = data_compare(item, (*node)->item);

        if (comp < 0) {
            // insert in the left subtree
            inserted = avl_insert_aux(source, &(*node)->left, item);
        } else if (comp > 0) {
            // insert in the right subtree
            inserted = avl_insert_aux(source, &(*node)->right, item);
        }

        if (inserted) {
            // update height before rebalancing
            avl_update_height(*node);
            // rebalance the node if necessary
            avl_rebalance(node);
        }
    }

    return inserted;
}
/**
 * Attempts to find a item matching key in a AVL node. Deletes the node
 * if found.
 *
 * @param source - pointer to a AVL.
 * @param node - node to process.
 * @param key - key to look for.
 * @param item - if key is found, the item being removed.
 * @return - true if key is found and item removed, false otherwise.
 */
static bool avl_remove_aux(avl_linked *source, avl_node **node,
		const data_ptr key, data_ptr item) {

	// your code here

	return false;
}

/**
 * Copies source_node to target_node.
 *
 * @param target_node - pointer to an AVL node
 * @param source_node - pointer to an AVL node
 */
static void avl_copy_aux(avl_node **target_node, const avl_node *source_node) {

	// your code here

	return;
}

/**
 * Copies the contents of a node to an array location.
 *
 * @param source - - pointer to a AVL
 * @param items - array of items
 * @param node - pointer to a node
 * @param index - current index in array
 * @return - the updated index
 */
static int avl_inorder_aux(const avl_linked *source, data_ptr *items,
		const avl_node *node, int index) {

	if (node != NULL) {
		index = avl_inorder_aux(source, items, node->left, index);
		items[index] = node->item;
		index++;
		index = avl_inorder_aux(source, items, node->right, index);
	}
	return index;
}

/**
 * Copies the contents of a node to an array location.
 *
 * @param source - - pointer to a AVL
 * @param items - array of items
 * @param node - pointer to a node
 * @param index - current index in array
 * @return - the updated index
 */
static int avl_preorder_aux(const avl_linked *source, data_ptr *items,
		const avl_node *node, int index) {

	if (node != NULL) {
		items[index] = node->item;
		index++;
		index = avl_preorder_aux(source, items, node->left, index);
		index = avl_preorder_aux(source, items, node->right, index);
	}
	return index;
}

/**
 * Copies the contents of a node to an array location.
 *
 * @param source - - pointer to a AVL
 * @param items - array of items
 * @param node - pointer to a node
 * @param index - current index in array
 * @return - the updated index
 */
static int avl_postorder_aux(const avl_linked *source, data_ptr *items,
		const avl_node *node, int index) {

	if (node != NULL) {
		index = avl_postorder_aux(source, items, node->left, index);
		index = avl_postorder_aux(source, items, node->right, index);
		items[index] = node->item;
		index++;
	}
	return index;
}

/**
 * Returns the number of leaves (nodes with no children) in node.
 *
 * @param node - The node to process.
 * @return - number of leaves for node and its children.
 */
static int avl_leaf_count_aux(const avl_node *node) {

	// your code here

	return 0;
}

/**
 * Returns the number of one child nodes in a AVL node.
 *
 * @param node - The node to process.
 * @return - number of one child nodes for node and its children.
 */
static int avl_one_child_count_aux(const avl_node *node) {

	// your code here

	return 0;
}

/**
 * Returns the number of types of nodes in a AVL node.
 *
 * @param node - The node to process.
 * @return - number of two children nodes for node and its children.
 */
static int avl_two_child_count_aux(const avl_node *node) {

	// your code here

	return 0;
}

/**
 * Determines the number of zero, one, and two children nodes in a source.
 *
 * @param node - node to process.
 * @param zero - number of zero children nodes for node and its children.
 * @param one - number of one child nodes for node and its children.
 * @param two - number of two children nodes for node and its children.
 */
static void avl_node_counts_aux(const avl_node *node, int *zero, int *one,
		int *two) {

	// your code here

	return;
}

/**
 * Determines if a source is a valid AVL.
 *
 * @param node - The node to process.
 * @return - AVL_ERROR code.
 */
static AVL_ERROR avl_valid_aux(const avl_node *node) {
	AVL_ERROR valid = AVL_VALID; // default base case

	if (node != NULL) {
		if ((node->left != NULL
				&& data_compare(node->left->item, node->item) >= 0)
				|| (node->right != NULL
						&& data_compare(node->right->item, node->item) <= 0)) {
			// Base case: child items are incorrect
			valid = AVL_BAD_CHILDREN;
		} else if (abs(
				avl_node_height(node->left) - avl_node_height(node->right))
				> 1) {
			// Base case: height violation - child heights not balanced
			valid = AVL_NOT_BALANCED;
		} else if (node->height < (avl_node_height(node->left) + 1)
				|| node->height < (avl_node_height(node->right) + 1)) {
			// Base case: height violation - current node height incorrect
			valid = AVL_HEIGHT_VIOLATION;
		} else {
			valid = avl_valid_aux(node->left) && avl_valid_aux(node->right);
		}
	}
	return (valid);
}

/**
 * Determines if two AVL subtrees are equal.
 *
 * @param compare - item comparison function
 * @param target_node - pointer to an AVL node
 * @param source_node - pointer to an AVL node
 * @return - true if subtree is equal, false otherwise
 */
static bool avl_equals_aux(const avl_node *target_node,
		const avl_node *source_node) {

	// your code here

	return false;
}

//--------------------------------------------------------------------
// Functions

avl_linked* avl_initialize() {
	avl_linked *source = malloc(sizeof *source);
	source->root = NULL;
	source->count = 0;
	return source;
}

// frees an AVL.
void avl_free(avl_linked **source) {
	avl_free_aux(&(*source)->root);
	free(*source);
	*source = NULL;
	return;
}

bool avl_empty(const avl_linked *source) {
	return (source->root == NULL);
}

bool avl_full(const avl_linked *source) {
	return false;
}

int avl_count(const avl_linked *source) {
	return source->count;
}

// Copies the contents of a AVL to an array in inorder.
void avl_inorder(const avl_linked *source, data_ptr *items) {
	avl_inorder_aux(source, items, source->root, 0);
	return;
}

// Copies the contents of a AVL to an array in preorder.
void avl_preorder(const avl_linked *source, data_ptr *items) {
	avl_preorder_aux(source, items, source->root, 0);
	return;
}

// Copies the contents of a AVL to an array in postorder.
void avl_postorder(const avl_linked *source, data_ptr *items) {
	avl_postorder_aux(source, items, source->root, 0);
	return;
}

bool avl_insert(avl_linked *source, data_ptr item) {
    return (avl_insert_aux(source, &(source->root), item));
}

bool avl_retrieve(const avl_linked *source, data_ptr key, data_ptr item) {
	bool retrieved = false;
	avl_node *node = source->root;

	while ((node != NULL) && (retrieved == false)) {
		int comp = data_compare(key, node->item);

		if (comp < 0) {
			node = node->left;
		} else if (comp > 0) {
			node = node->right;
		} else {
			data_copy(item, node->item);
			retrieved = true;
		}
	}
	return retrieved;
}

bool avl_remove(avl_linked *source, const data_ptr key, data_ptr item) {
	return (avl_remove_aux(source, &(source->root), key, item));
}

// Copies source to target.
void avl_copy(avl_linked **target, const avl_linked *source) {
	*target = avl_initialize();
	avl_copy_aux(&(*target)->root, source->root);
	(*target)->count = source->count;
}

// Finds the maximum item in a AVL.
bool avl_max(const avl_linked *source, data_ptr item) {
	bool found = false;

	if (source->root != NULL) {
		// Find the node containing the largest data.
		// (It is the right-most node.)
		avl_node *node = source->root;

		while (node->right != NULL) {
			node = node->right;
		}
		data_copy(item, node->item);
		found = true;
	}
	return found;
}

// Finds the minimum item in a AVL.
bool avl_min(const avl_linked *source, data_ptr item) {
	bool found = false;

	if (source->root != NULL) {
		// Find the node containing the largest data.
		// (It is the right-most node.)
		avl_node *node = source->root;

		while (node->left != NULL) {
			node = node->left;
		}
		data_copy(item, node->item);
		found = true;
	}
	return found;
}

void avl_node_counts(const avl_linked *source, int *zero, int *one, int *two) {
	*zero = *one = *two = 0;
	avl_node_counts_aux(source->root, zero, one, two);
	return;
}

int avl_leaf_count(const avl_linked *source) {
	return (avl_leaf_count_aux(source->root));
}

int avl_one_child_count(const avl_linked *source) {
	return (avl_one_child_count_aux(source->root));
}

int avl_two_child_count(const avl_linked *source) {
	return (avl_two_child_count_aux(source->root));
}

AVL_ERROR avl_valid(const avl_linked *source) {
	return (avl_valid_aux(source->root));
}

bool avl_equals(const avl_linked *target, const avl_linked *source) {
	return (avl_equals_aux(target->root, source->root));
}

/**
 * Private helper function to print contents of BS in preorder.
 *
 * @param to_string - function to print data_ptr
 * @param node - pointer to avl_node
 */
static void avl_print_aux(avl_node *node) {
	char string[DATA_STRING_SIZE];

	if (node != NULL) {
		printf("%s\n", data_string(string, DATA_STRING_SIZE, node->item));
		avl_print_aux(node->left);
		avl_print_aux(node->right);
	}
	return;
}

// Returns a string version of an AVL error.
char* avl_error_string(char *string, size_t size, AVL_ERROR error) {

	switch (error) {
	case AVL_BAD_CHILDREN:
		strncpy(string, "AVL_BAD_CHILDREN", size);
		break;
	case AVL_HEIGHT_VIOLATION:
		strncpy(string, "AVL_HEIGHT_VIOLATION", size);
		break;
	case AVL_NOT_BALANCED:
		strncpy(string, "AVL_NOT_BALANCED", size);
		break;
	default:
		strncpy(string, "AVL_VALID", size);
	}
	return string;
}

// Prints the items in a AVL in preorder.
void avl_print(const avl_linked *source) {
	printf("  count: %d, height: %d, items:\n", source->count,
			source->root->height);
	avl_print_aux(source->root);
	printf("\n");
	return;
}
